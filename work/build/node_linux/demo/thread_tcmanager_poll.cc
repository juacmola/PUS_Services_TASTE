#include "thread_tcmanager_poll.h"

#include <Timer.h>
#include <Queue.h>
#include <Request.h>
#include <StartBarrier.h>

#include "transport.h"
#include "demo_interface.h"
#include "routing.h"

void tcmanager_poll_job()
{
    // synchronize with other threads
    taste::StartBarrier::wait();

    using namespace std::chrono_literals;
    taste::Timer::run( 1000ms, 100ms, [] () -> void
    {
        static taste::Request<TCMANAGER_POLL_REQUEST_SIZE> request;
        call_tcmanager_poll((const char*)request.data(), request.length());
    });
}

