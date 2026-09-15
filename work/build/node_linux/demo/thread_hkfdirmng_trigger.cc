#include "thread_hkfdirmng_trigger.h"

#include <Timer.h>
#include <Queue.h>
#include <Request.h>
#include <StartBarrier.h>

#include "transport.h"
#include "demo_interface.h"
#include "routing.h"

void hkfdirmng_trigger_job()
{
    // synchronize with other threads
    taste::StartBarrier::wait();

    using namespace std::chrono_literals;
    taste::Timer::run( 1000ms, 1000ms, [] () -> void
    {
        static taste::Request<HKFDIRMNG_TRIGGER_REQUEST_SIZE> request;
        call_hkfdirmng_trigger((const char*)request.data(), request.length());
    });
}

