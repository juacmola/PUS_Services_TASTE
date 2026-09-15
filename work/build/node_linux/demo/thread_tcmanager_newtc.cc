#include "thread_tcmanager_newtc.h"

#include <Timer.h>
#include <Queue.h>
#include <Request.h>
#include <StartBarrier.h>

#include "transport.h"
#include "demo_interface.h"
#include "routing.h"

void tcmanager_newtc_job()
{
    // synchronize with other threads
    //taste::StartBarrier::wait();

    //using namespace std::chrono_literals;
    //extern taste::Queue<TCMANAGER_NEWTC_REQUEST_SIZE> tcmanager_newTC_Global_Queue;

    //while(true)
    //{
    //    static taste::Request<TCMANAGER_NEWTC_REQUEST_SIZE> request;
    //    tcmanager_newTC_Global_Queue.get(request);

    //    tcmanager_newtc_sender_pid = request.sender_pid();
    //    call_tcmanager_newtc((const char*)request.data(), request.length());
    //}
}

