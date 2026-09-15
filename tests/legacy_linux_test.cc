#include "llsw/rtems_osswr/include/public/basic_types.h"
#include "llsw/config/include/public/basic_types.h"
#include "service_libraries/serialize/include/public/serialize.h"
#include "service_libraries/edroomsl/edroombp/include/public/edroombp.h"
#include <cassert>
#include <chrono>
#include <cstring>
#include <thread>

int main() {
    static_assert(sizeof(word64_t) == 8);
    static_assert(sizeof(error_code_t) == sizeof(int));
    uint8_t bytes[8]{};
    const uint8_t wire16[] = {0x12, 0x34};
    const uint8_t wire32[] = {0x12, 0x34, 0x56, 0x78};
    const uint8_t wire64[] = {1, 2, 3, 4, 5, 6, 7, 8};
    const uint8_t wirefloat[] = {0x3f, 0x80, 0, 0};
    serialize_uint16(0x1234, bytes);
    assert(std::memcmp(bytes, wire16, 2) == 0);
    assert(deserialize_uint16(wire16) == 0x1234);
    serialize_uint32(0x12345678, bytes);
    assert(std::memcmp(bytes, wire32, 4) == 0);
    assert(deserialize_uint32(wire32) == 0x12345678);
    serialize_uint64(UINT64_C(0x0102030405060708), bytes);
    assert(std::memcmp(bytes, wire64, 8) == 0);
    assert(deserialize_uint64(wire64) == UINT64_C(0x0102030405060708));
    serialize_float(1.0f, bytes);
    assert(std::memcmp(bytes, wirefloat, 4) == 0);
    assert(deserialize_float(wirefloat) == 1.0f);
    serialize_int32(-2, bytes);
    const uint8_t negative[] = {0xff, 0xff, 0xff, 0xfe};
    assert(std::memcmp(bytes, negative, 4) == 0);
    assert(deserialize_int32(negative) == -2);

    Pr_Mutex mutex;
    mutex.Wait();
    assert(mutex.WaitCond()); // Recursive acquisition by the owner.
    mutex.Signal();
    bool acquired = true;
    std::thread contender([&] {
        acquired = mutex.WaitCond();
        if (acquired) mutex.Signal();
    });
    contender.join();
    assert(!acquired);
    mutex.Signal();
    std::thread next([&] {
        acquired = mutex.WaitCond();
        if (acquired) mutex.Signal();
    });
    next.join();
    assert(acquired);

    Pr_Time now;
    now.GetTime();
    Pr_Time deadline = now;
    deadline += Pr_Time(0, 25000);
    auto before = std::chrono::steady_clock::now();
    Pr_DelayAt(deadline);
    now.GetTime();
    assert(now >= deadline);
    assert(std::chrono::steady_clock::now() - before >= std::chrono::milliseconds(20));
    Pr_Time difference(1, 100);
    difference -= Pr_Time(0, 200);
    assert(difference == Pr_Time(0, 999900));
    difference -= Pr_Time(2, 0);
    assert(difference == Pr_Time(0, 0));
}
