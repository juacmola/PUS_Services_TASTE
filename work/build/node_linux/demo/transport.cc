#include "transport.h"

#include <cstring>

#include <Queue.h>
#include <Request.h>

extern "C"
{
#include <Broker.h>
}

// sporadic required

// sporadic provided


void deliver_to_bkgtcexec_sbkgtc(const asn1SccPID sender_pid, const uint8_t* const data, const size_t length)
{
    extern taste::Queue<BKGTCEXEC_SBKGTC_REQUEST_SIZE> bkgtcexec_SBKGTC_Global_Queue;
    bkgtcexec_SBKGTC_Global_Queue.put(sender_pid, data, length);
}



void deliver_to_hkfdirmng_shkfdirtc(const asn1SccPID sender_pid, const uint8_t* const data, const size_t length)
{
    extern taste::Queue<HKFDIRMNG_SHKFDIRTC_REQUEST_SIZE> hkfdirmng_SHKFDIRTC_Global_Queue;
    hkfdirmng_SHKFDIRTC_Global_Queue.put(sender_pid, data, length);
}





void deliver_to_tcmanager_sevaction(const asn1SccPID sender_pid, const uint8_t* const data, const size_t length)
{
    extern taste::Queue<TCMANAGER_SEVACTION_REQUEST_SIZE> tcmanager_SEvAction_Global_Queue;
    tcmanager_SEvAction_Global_Queue.put(sender_pid, data, length);
}



void initialize_transport()
{
}
