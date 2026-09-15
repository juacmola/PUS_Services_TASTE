#ifndef GENERIC_LINUX_TRANSPORT_H
#define GENERIC_LINUX_TRANSPORT_H

#include <cstdint>

#include <system_spec.h>

#include <Request.h>
#include <request_size.h>
#include <dataview-uniq.h>

extern "C"
{
#include <Broker.h>
}

void initialize_transport();

// Sporadic required

// sporadic provided
void deliver_to_bkgtcexec_sbkgtc(const asn1SccPID sender_pid, const uint8_t* const data, const size_t length);
void deliver_to_hkfdirmng_shkfdirtc(const asn1SccPID sender_pid, const uint8_t* const data, const size_t length);
void deliver_to_hkfdirmng_trigger(const asn1SccPID sender_pid, const uint8_t* const data, const size_t length);
void deliver_to_tcmanager_poll(const asn1SccPID sender_pid, const uint8_t* const data, const size_t length);
void deliver_to_tcmanager_sevaction(const asn1SccPID sender_pid, const uint8_t* const data, const size_t length);

extern driver_send_function bus_to_driver_send_function[SYSTEM_BUSES_NUMBER];
extern void* bus_to_driver_private_data[SYSTEM_BUSES_NUMBER];
extern deliver_function interface_to_deliver_function[INTERFACE_MAX_ID];

#ifndef COMMUNICATION_DEVICE_MAX_THREAD_COUNT
#define COMMUNICATION_DEVICE_MAX_THREAD_COUNT 16
#endif

#endif
