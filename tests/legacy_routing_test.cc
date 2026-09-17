#include "legacy.h"
#include "legacy_state.h"
#include "service_libraries/serialize/include/public/serialize.h"
#include "service_libraries/crc/include/public/crc.h"
#include "service_libraries/pus_services/pus_service19/include/pus_service19/aux_pus_service19_utils.h"
#include <cassert>
#include <cstring>
#include <vector>
#include <memory>
#include <cstdio>
#include "service_libraries/edroomsl/edroombp/include/public/edroombp.h"
#include "public/tc_rate_ctrl.h"

// Override only the limiter's monotonic clock; the GSS schedule keeps real time.
// This lets the queue-wrap regression cover 205 commands without a 102 s wait.
static uint64_t rate_time_us = 0;
extern "C" void __wrap__ZN7Pr_Time7GetTimeEv(Pr_Time *time) {
    *time = Pr_Time(rate_time_us / 1000000, rate_time_us % 1000000);
}
#include "public/emu_gss_v1.h"
#include "public/emu_hw_timecode_drv_v1.h"
#include "public/tc_queue_drv.h"

asn1SccTelecommand command(unsigned service, unsigned subtype) {
    asn1SccTelecommand tc{};
    tc.service_type = service;
    tc.subservice_type = subtype;
    tc.param.arr[0] = 1;
    tc.param.arr[1] = 0;
    tc.param.arr[2] = 0;
    return tc;
}

int main() {
    legacy_PI_Init();
    asn1SccRxTC accepted;
    asn1SccFwdCommand route;
    asn1SccRawTC hk{}, bkg{}, empty{};
    legacy_PI_NewEvAction(&accepted);
    assert(accepted == asn1SccRxTC_not_accepted);
    legacy_PI_HandleTC(&route, &empty);
    assert(empty.nCount == 0);

    // Ten connection tests: two at a time, with no dequeue while rate limited.
    std::vector<std::unique_ptr<EmuGSS_TCProgram17_1>> burst;
    for (int i = 0; i < 10; ++i)
        burst.emplace_back(new EmuGSS_TCProgram17_1(
            EmuHwTimeCodeGetCurrentOBT(), "rate test"));
    std::puts("RATE_BURST_BEGIN");
    for (int pair = 0; pair < 5; ++pair) {
        rate_time_us = pair * 1000000;
        for (int j = 0; j < 2; ++j) {
            legacy_PI_PollTC(&accepted);
            assert(accepted == asn1SccRxTC_accepted);
            legacy_PI_HandleTC(&route, &empty);
            assert(route == asn1SccFwdCommand_exec_prio_tc);
        }
        if (pair < 4) {
            for (int attempt = 0; attempt < 3; ++attempt) {
                if (attempt == 2) rate_time_us += 999999;
                legacy_PI_PollTC(&accepted);
                assert(accepted == asn1SccRxTC_not_accepted);
                assert(!TCQueue_IsEmpty());
            }
            assert(RxTC_TCRateExceeded());
            assert(!RxTC_TCRateExceeded());
            // Housekeeping remains callable while incoming commands wait.
            legacy_PI_DoHousekeeping();
        }
    }
    assert(TCQueue_IsEmpty());
    std::puts("RATE_BURST_END");

    // More than two queue capacities: full queues defer programs and wrap safely.
    std::vector<std::unique_ptr<EmuGSS_TCProgram3_5>> programs;
    for (int i = 0; i < 205; ++i)
        programs.emplace_back(new EmuGSS_TCProgram3_5(
            EmuHwTimeCodeGetCurrentOBT(), "burst HK", 0));
    for (int i = 0; i < 205; ++i) {
        rate_time_us = 5000000 + (i / 2) * 1000000;
        legacy_PI_PollTC(&accepted);
        assert(accepted == asn1SccRxTC_accepted);
        legacy_PI_HandleTC(&route, &hk);
        assert(route == asn1SccFwdCommand_fwdhk_fdir_tc);
        assert(hk.arr[7] == 3 && hk.arr[8] == 5);
        assert(deserialize_uint16(hk.arr) == (0x1800 | UAH_APID));
        assert(hk.arr[6] == 0x2f);
        assert(deserialize_uint16(hk.arr + hk.nCount - 2) ==
               cal_crc_16(hk.arr, hk.nCount - 2));
        legacy_PI_ExecHKFDIRTC(&hk);
    }
    assert(TCQueue_IsEmpty());
    auto tc = command(3, 5);
    legacy_PI_NewRxTC(&tc, &accepted);
    assert(accepted == asn1SccRxTC_accepted);
    // A second arrival must not overwrite the accepted command.
    auto next = command(20, 1);
    legacy_PI_NewRxTC(&next, &accepted);
    assert(accepted == asn1SccRxTC_not_accepted);
    legacy_PI_HandleTC(&route, &hk);
    assert(route == asn1SccFwdCommand_fwdhk_fdir_tc);
    assert(hk.nCount == 16 && hk.arr[7] == 3 && hk.arr[8] == 5);
    assert(std::memcmp(hk.arr + 11, tc.param.arr, 3) == 0);
    assert(deserialize_uint16(hk.arr) == (0x1800 | UAH_APID));
    assert(deserialize_uint16(hk.arr + 14) == cal_crc_16(hk.arr, 14));
    const auto saved = hk;
    legacy_PI_NewRxTC(&next, &accepted);
    assert(accepted == asn1SccRxTC_accepted);
    legacy_PI_HandleTC(&route, &bkg);
    assert(route == asn1SccFwdCommand_fwdbkgtc && bkg.arr[7] == 20);
    assert(std::memcmp(&saved, &hk, sizeof(hk)) == 0);
    // Simulate delayed delivery after current TC storage was reused.
    legacy_PI_ExecBKGTC(&bkg);
    legacy_PI_ExecHKFDIRTC(&hk);
    legacy_PI_HandleTC(&route, &empty);
    assert(empty.nCount == 0); // no duplicate execution or forwarding

    tc = command(255, 1);
    legacy_PI_NewRxTC(&tc, &accepted);
    assert(accepted == asn1SccRxTC_not_accepted);
    legacy_PI_HandleTC(&route, &empty);
    assert(empty.nCount == 0);
    tc = command(17, 1);
    legacy_PI_NewRxTC(&tc, &accepted);
    assert(accepted == asn1SccRxTC_accepted);
    legacy_PI_HandleTC(&route, &empty);
    assert(route == asn1SccFwdCommand_exec_prio_tc && empty.nCount == 0);

    LegacyTCHandler handler;
    auto malformed = hk;
    malformed.nCount = 1;
    assert(!handler.Load(malformed));
    malformed = hk;
    malformed.arr[4] = 255;
    assert(!handler.Load(malformed));
    malformed.nCount = 257;
    assert(!handler.Load(malformed));
    legacy_PI_ExecHKFDIRTC(&malformed);
    legacy_PI_NewRxTC(nullptr, &accepted);
    assert(accepted == asn1SccRxTC_not_accepted);

    // Exercise the low-level severity-2 queue using its synthetic event 0.
    // The mission currently defines no user severity-2 events.
    ev_action_id_t action_id;
    assert(pus_service19_get_free_ev_action_id(&action_id) == 0);
    pus_service19_set_ev_action(0x2000, action_id, hk.arr, hk.nCount);
    assert(pus_service19_add_ev_action_to_queue(0x2000, action_id) == 0);
    assert(pus_service19_pending_ev_5_2_actions() == 1);
    legacy_PI_NewEvAction(&accepted);
    assert(accepted == asn1SccRxTC_accepted);
    legacy_PI_HandleTC(&route, &empty);
    assert(route == asn1SccFwdCommand_fwdhk_fdir_tc);
    assert(empty.nCount == hk.nCount && std::memcmp(empty.arr, hk.arr, hk.nCount) == 0);
    legacy_PI_ExecHKFDIRTC(&empty);
    assert(pus_service19_pending_ev_5_2_actions() == 0);
    legacy_PI_NewEvAction(&accepted);
    assert(accepted == asn1SccRxTC_not_accepted);

    // Releasing twice must not free a block already reassigned to another TC.
    tc_handler_t released{};
    released.raw_tc_mem_descriptor = {tmtc_pool_alloc(), 16};
    auto *old_buffer = released.raw_tc_mem_descriptor.p_tc_bytes;
    assert(tc_handler_free_memory(&released) == 0);
    auto *new_owner = tmtc_pool_alloc();
    assert(new_owner == old_buffer);
    assert(tc_handler_free_memory(&released) != 0);
    auto *other = tmtc_pool_alloc();
    assert(other != new_owner);
    tmtc_pool_free(other);
    tmtc_pool_free(new_owner);
    assert(tc_handler_free_memory(nullptr) != 0);

    // Every consumed/rejected/forwarded packet must have released its buffer.
    std::vector<uint8_t *> blocks;
    while (auto *p = tmtc_pool_alloc()) blocks.push_back(p);
    assert(blocks.size() == 50);
    assert(!handler.Load(hk));
    legacy_PI_NewRxTC(&tc, &accepted);
    assert(accepted == asn1SccRxTC_not_accepted);
    for (auto *p : blocks) tmtc_pool_free(p);
}
