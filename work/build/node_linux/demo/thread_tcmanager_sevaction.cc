#include "thread_tcmanager_sevaction.h"

#include <Timer.h>
#include <Queue.h>
#include <Request.h>
#include <StartBarrier.h>

#include "transport.h"
#include "demo_interface.h"
#include "routing.h"

void tcmanager_sevaction_job()
{
    // synchronize with other threads
    taste::StartBarrier::wait();

    using namespace std::chrono_literals;
    extern taste::Queue<TCMANAGER_SEVACTION_REQUEST_SIZE> tcmanager_SEvAction_Global_Queue;

    while(true)
    {
        static taste::Request<TCMANAGER_SEVACTION_REQUEST_SIZE> request;
        tcmanager_SEvAction_Global_Queue.get(request);

        tcmanager_sevaction_sender_pid = request.sender_pid();
        call_tcmanager_sevaction((const char*)request.data(), request.length());
    }
}

