#include "thread_hkfdirmng_shkfdirtc.h"

#include <Timer.h>
#include <Queue.h>
#include <Request.h>
#include <StartBarrier.h>

#include "transport.h"
#include "demo_interface.h"
#include "routing.h"

void hkfdirmng_shkfdirtc_job()
{
    // synchronize with other threads
    taste::StartBarrier::wait();

    using namespace std::chrono_literals;
    extern taste::Queue<HKFDIRMNG_SHKFDIRTC_REQUEST_SIZE> hkfdirmng_SHKFDIRTC_Global_Queue;

    while(true)
    {
        static taste::Request<HKFDIRMNG_SHKFDIRTC_REQUEST_SIZE> request;
        hkfdirmng_SHKFDIRTC_Global_Queue.get(request);

        hkfdirmng_shkfdirtc_sender_pid = request.sender_pid();
        call_hkfdirmng_shkfdirtc((const char*)request.data(), request.length());
    }
}

