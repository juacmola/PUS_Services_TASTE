#include "thread_irq_poll.h"

#include <Timer.h>
#include <Queue.h>
#include <Request.h>
#include <StartBarrier.h>

#include "transport.h"
#include "demo_interface.h"
#include "routing.h"

void irq_poll_job()
{
    // synchronize with other threads
    //taste::StartBarrier::wait();

    //using namespace std::chrono_literals;
    //taste::Timer::run( 0ms, 10ms, [] () -> void
    //{
    //    static taste::Request<IRQ_POLL_REQUEST_SIZE> request;
    //    call_irq_poll((const char*)request.data(), request.length());
    //});
}

