#include "thread_bkgtcexec_sbkgtc.h"

#include <Timer.h>
#include <Queue.h>
#include <Request.h>
#include <StartBarrier.h>

#include "transport.h"
#include "demo_interface.h"
#include "routing.h"

void bkgtcexec_sbkgtc_job()
{
    // synchronize with other threads
    taste::StartBarrier::wait();

    using namespace std::chrono_literals;
    extern taste::Queue<BKGTCEXEC_SBKGTC_REQUEST_SIZE> bkgtcexec_SBKGTC_Global_Queue;

    while(true)
    {
        static taste::Request<BKGTCEXEC_SBKGTC_REQUEST_SIZE> request;
        bkgtcexec_SBKGTC_Global_Queue.get(request);

        bkgtcexec_sbkgtc_sender_pid = request.sender_pid();
        call_bkgtcexec_sbkgtc((const char*)request.data(), request.length());
    }
}

