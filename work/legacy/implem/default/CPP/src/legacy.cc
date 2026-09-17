// C++ body file for function Legacy. Maintained source, not generated glue.
#include "legacy.h"
#include "legacy_state.h"
#include "../../../../../asw_pus_rtems_5_0_leon3/asw/components/cctcmanager/include/public/cctcmanager_iface_v1.h"
#include "../../../../../asw_pus_rtems_5_0_leon3/service_libraries/serialize/include/public/serialize.h"
#include "../../../../../asw_pus_rtems_5_0_leon3/service_libraries/crc/include/public/crc.h"
#include <cstring>
#include <chrono>
#include "public/emu_gss_v1.h"
#include "public/emu_hw_timecode_drv_v1.h"
#include "public/tc_queue_drv.h"
#include "public/tc_rate_ctrl.h"

legacy_state ctxt_legacy;

namespace {
std::chrono::steady_clock::time_point next_gss_second;
bool gss_ready = false;
bool ValidPacket(const uint8_t *bytes, size_t size)
{
    // The legacy parser uses the header length to locate the CRC. Check it
    // before parsing so malformed input cannot cause an out-of-bounds read.
    return bytes && size >= UAH_PUS_TC_APP_DATA_OFFSET + 2 &&
        size <= UAH_PUS_TC_MAX_NUM_OF_BYTES &&
        size == static_cast<size_t>(deserialize_uint16(bytes + 4)) + 7;
}
}

LegacyTCHandler::~LegacyTCHandler() { Reset(); }

void LegacyTCHandler::Reset()
{
    // Legacy execution/rejection frees the buffer and zeroes its length,
    // but leaves a dangling pointer. Do not free that pointer a second time.
    if (mTCHandler.raw_tc_mem_descriptor.tc_num_bytes)
        tmtc_pool_free(mTCHandler.raw_tc_mem_descriptor.p_tc_bytes);
    mTCHandler = {};
}

bool LegacyTCHandler::Load(const asn1SccRawTC &packet)
{
    Reset();
    if (packet.nCount < 0 || !ValidPacket(packet.arr, packet.nCount))
        return false;
    auto *bytes = tmtc_pool_alloc();
    if (!bytes) return false;
    std::memcpy(bytes, packet.arr, packet.nCount);
    tc_mem_descriptor_t descriptor{bytes, static_cast<uint16_t>(packet.nCount)};
    tc_handler_build_from_descriptor(&mTCHandler, descriptor);
    return true;
}

bool LegacyTCHandler::ExtractEventAction()
{
    Reset();
    if (!pus_service19_pending_ev_actions()) return false;
    auto *bytes = tmtc_pool_alloc();
    if (!bytes) return false;
    mTCHandler.raw_tc_mem_descriptor.p_tc_bytes = bytes;
    const auto error = pus_service19_extract_next_ev_action(&mTCHandler);
    const auto descriptor = mTCHandler.raw_tc_mem_descriptor;
    if (error || descriptor.p_tc_bytes != bytes ||
        !ValidPacket(bytes, descriptor.tc_num_bytes)) {
        tmtc_pool_free(bytes);
        mTCHandler = {};
        return false;
    }
    tc_handler_build_from_descriptor(&mTCHandler, descriptor);
    return true;
}

void LegacyTCHandler::CopyPacket(asn1SccRawTC &packet) const
{
    packet = {};
    const auto &descriptor = mTCHandler.raw_tc_mem_descriptor;
    if (!ValidPacket(descriptor.p_tc_bytes, descriptor.tc_num_bytes)) return;
    packet.nCount = descriptor.tc_num_bytes;
    std::memcpy(packet.arr, descriptor.p_tc_bytes, packet.nCount);
}

void legacy_startup(void) {}

extern "C" void FInit(void)
{
#ifdef GENERIC_LINUX_TARGET
    pus_services_startup(nullptr);
    extern void TasteGSS_InitSchedule();
    TasteGSS_InitSchedule();
    next_gss_second = std::chrono::steady_clock::now() + std::chrono::seconds(1);
    gss_ready = true;
#else
    CCTCManager::RxTC.MaskIRQ();
    CCTCManager::RxTC.InstallHandler();
    pus_services_startup(&CCTCManager::RxTC);
    CCTCManager::RxTC.UnMaskIRQ();
#endif
}

void legacy_PI_Init(void) { FInit(); }

void legacy_PI_DoHousekeeping(void)
{
    // The cyclic HKFDIRMng caller and TC executors share Legacy's protection.
    // Do not access the pool before TCManager has initialized the services.
#ifdef GENERIC_LINUX_TARGET
    if (!gss_ready) return;
#endif
    pus_services_update_params();
    pus_service3_do_HK();
    pus_services_do_FDIR();
}


extern "C" void FTCExecCtrl() {
    ctxt_legacy.VTCExecCtrl = ctxt_legacy.VCurrentTC.GetExecCtrl();
}
extern "C" bool GToReboot() { return ctxt_legacy.VTCExecCtrl.IsRebootTC(); }
extern "C" bool GFwdToHK_FDIR() { return ctxt_legacy.VTCExecCtrl.IsHK_FDIRTC(); }
extern "C" bool GFwdToBKG() { return ctxt_legacy.VTCExecCtrl.IsBKGTC(); }
extern "C" void FExecRebootTC() { ctxt_legacy.VCurrentTC.ExecRebootTC(); }
extern "C" void FExecPrioTC() { ctxt_legacy.VCurrentTC.ExecPrioTC(); }

extern "C" void FFwdHK_FDIRTC(asn1SccRawTC *packet)
{
    // TCManager owns SHKFDIRTC: its SDL output sends this value to HKFDIRMng.
    // Returning a CDTCHandler pointer would retain a shared pool buffer.
    ctxt_legacy.VCurrentTC.CopyPacket(*packet);
}

extern "C" void FFwdBKGTC(asn1SccRawTC *packet)
{
    // TCManager's SBKGTC output sends this value to BKGTCExec.
    ctxt_legacy.VCurrentTC.CopyPacket(*packet);
}

void legacy_PI_HandleTC(asn1SccFwdCommand *route, asn1SccRawTC *packet)
{
    *route = asn1SccFwdCommand_exec_prio_tc;
    *packet = {};
    if (!ctxt_legacy.has_accepted_tc) return;
    FTCExecCtrl();
    if (GFwdToHK_FDIR()) {
        FFwdHK_FDIRTC(packet);
        *route = asn1SccFwdCommand_fwdhk_fdir_tc;
    } else if (GFwdToBKG()) {
        FFwdBKGTC(packet);
        *route = asn1SccFwdCommand_fwdbkgtc;
    } else if (GToReboot()) {
        FExecRebootTC();
        *route = asn1SccFwdCommand_to_reboot;
    } else {
        FExecPrioTC();
    }
    ctxt_legacy.VCurrentTC.Reset();
    ctxt_legacy.has_accepted_tc = false;
}

extern "C" bool FGetEvAction()
{
    // SEvAction is a notification; there is no EDROOM Msg in TASTE.
    return ctxt_legacy.VCurrentTC.ExtractEventAction();
}

void legacy_PI_NewEvAction(asn1SccRxTC *accepted)
{
    *accepted = asn1SccRxTC_not_accepted;
    if (ctxt_legacy.has_accepted_tc) return;
    ctxt_legacy.has_accepted_tc = FGetEvAction();
    // Event actions were accepted when their definitions were installed.
    if (ctxt_legacy.has_accepted_tc) *accepted = asn1SccRxTC_accepted;
}

extern "C" void FReboot() { pus_services_mng_reboot(); }
void legacy_PI_Reboot(void) { FReboot(); }

extern "C" bool FGetTC(const asn1SccTelecommand *tc)
{
    ctxt_legacy.VAcceptReport = CDTCAcceptReport();
    if (!tc || tc->service_type > 255 || tc->subservice_type > 255)
        return false;
    // The GUI supplies service/subservice and three application bytes, not a
    // wire packet. Construct the missing mission headers and CRC explicitly.
    asn1SccRawTC packet{};
    packet.nCount = UAH_PUS_TC_APP_DATA_OFFSET + sizeof(tc->param.arr) + 2;
    serialize_uint16(0x1800 | UAH_APID, packet.arr);
    serialize_uint16(0xc000 | (ctxt_legacy.sequence_count++ & 0x3fff), packet.arr + 2);
    serialize_uint16(packet.nCount - 7, packet.arr + 4);
    packet.arr[6] = 0x2f; // PUS version 2, all verification acknowledgements.
    packet.arr[7] = tc->service_type;
    packet.arr[8] = tc->subservice_type;
    serialize_uint16(UAH_SOURCE_ID, packet.arr + 9);
    std::memcpy(packet.arr + UAH_PUS_TC_APP_DATA_OFFSET, tc->param.arr, sizeof(tc->param.arr));
    serialize_uint16(cal_crc_16(packet.arr, packet.nCount - 2), packet.arr + packet.nCount - 2);
    if (!ctxt_legacy.VCurrentTC.Load(packet)) return false;
    ctxt_legacy.VAcceptReport = ctxt_legacy.VCurrentTC.DoAcceptation();
    return true;
}

extern "C" bool GAcceptTC() { return ctxt_legacy.VAcceptReport.IsAccepted(); }
extern "C" void FMngTCAcceptation() { ctxt_legacy.VCurrentTC.MngTCAcceptation(); }
extern "C" void FMngTCRejection() {
    ctxt_legacy.VCurrentTC.MngTCRejection(ctxt_legacy.VAcceptReport);
    ctxt_legacy.VCurrentTC.Reset();
}

void legacy_PI_NewRxTC(const asn1SccTelecommand *tc, asn1SccRxTC *accepted)
{
    *accepted = asn1SccRxTC_not_accepted;
    if (ctxt_legacy.has_accepted_tc || !FGetTC(tc)) return;
    if (GAcceptTC()) {
        FMngTCAcceptation();
        ctxt_legacy.has_accepted_tc = true;
        *accepted = asn1SccRxTC_accepted;
    } else {
        FMngTCRejection();
    }
}

void legacy_PI_ExecHKFDIRTC(const asn1SccRawTC *packet)
{
    LegacyTCHandler tc;
    if (packet && tc.Load(*packet) && tc.GetExecCtrl().IsHK_FDIRTC())
        tc.ExecHK_FDIRTC();
}

void legacy_PI_ExecBKGTC(const asn1SccRawTC *packet)
{
    LegacyTCHandler tc;
    if (packet && tc.Load(*packet) && tc.GetExecCtrl().IsBKGTC())
        tc.ExecBKGTC();
}

// Called only through the protected Legacy interface, in TCManager's task.
// Receive one command per dispatch to pace asynchronous executor delivery.
void legacy_PI_PollTC(asn1SccRxTC *accepted)
{
    *accepted = asn1SccRxTC_not_accepted;
#ifdef GENERIC_LINUX_TARGET
    if (!gss_ready || ctxt_legacy.has_accepted_tc) return;
    const auto now = std::chrono::steady_clock::now();
    while (now >= next_gss_second) {
        EmuHwTimeCodePassSecond();
        next_gss_second += std::chrono::seconds(1);
    }
    // Retry due programs after a full queue has made room, even within a second.
    EmuGSS_SendProgrammedTCs();
    if (TCQueue_IsEmpty()) return;
    uint16_t size = 0;
    const auto *bytes = TCQueue_GetHeadTCMemory(size);
    if (!ValidPacket(bytes, size)) {
        TCQueue_HeadTCExtracted();
        return;
    }
    asn1SccRawTC packet{};
    packet.nCount = size;
    std::memcpy(packet.arr, bytes, size);
    // Leave the queue entry pending if the packet pool is exhausted.
    if (!ctxt_legacy.VCurrentTC.Load(packet)) return;
#ifdef TC_RATE_CTRL
    // Legacy is protected and shared with housekeeping: never sleep here.
    // Count received packets before acceptance, including rejected commands.
    if (!RxTC_TryRateCtrl()) {
        ctxt_legacy.VCurrentTC.Reset();
        return;
    }
#endif
    TCQueue_HeadTCExtracted();
    ctxt_legacy.VAcceptReport = ctxt_legacy.VCurrentTC.DoAcceptation();
    if (GAcceptTC()) {
        FMngTCAcceptation();
        ctxt_legacy.has_accepted_tc = true;
        *accepted = asn1SccRxTC_accepted;
    } else {
        FMngTCRejection();
    }
#endif
}
