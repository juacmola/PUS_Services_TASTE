/*
 * \file	edroombp.cpp created for edroombp project
 * \brief
 *
 * \author	Alberto Carrasco Gallardo, <acarrasco@srg.aut.uah.es>
 *
 * \internal
 * Created: 	23-mar-2011
 * Compiler: 	gcc/g++
 * Company:  Space Research Group, Universidad de Alcal�.
 * Copyright: Copryright (c) 2011, Alberto Carrasco Gallardo
 *
 * For further information, please visit http://srg.aut.uah.es
 *
 * This software is provided under the terms of the GNU General Public v2
 * Licence. A full copy of the GNU GPL is provided in the file COPYING
 * found in the development root of ERCOS-RT project.
 *
 * \note
 * This port of the API is intended for SPARC architecture only, since
 * lowlevel IRQ related functions used, such as LEON_Mask_Interrupt and
 * LEON_Unmask_Interrupt, are obviously defined only for SPARC architecture.
 */

#include "../../../include/edroombp_swr/rtemsapi_5_1/rtems_5_1/edroombp.h"
#include "../../../include/edroombp_swr/rtemsapi_5_1/rtems_5_1/leon3/leon3_hw_irqs.h"
#include <stdlib.h>	//necesaria para "exit(1);"

#include <stdio.h>

#include "../../../../../../llsw/rtems_osswr/include/rtems_config.h"
#include "../../../../../../llsw/config/include/public/config.h"

//------------------------------------------------------------------------------


/*	Nombres RTEMS	*/

#define NEXT_RESOURCE_NAME(c1, c2, c3, c4)  \
                 if (c4 == '9') {       \
                   if (c3 == '9') {     \
                     if (c2 == 'z') {   \
                       if (c1 == 'z') { \
                    	   printf("not enough letters for names !!!\n");\
                         exit(1);	\
                       } else           \
                         c1++;          \
                       c2 = 'a';        \
                     } else             \
                      c2++;             \
                     c3 = '0';          \
                   } else               \
                     c3++;              \
                   c4 = '0';            \
                 }                      \
                 else                   \
                   c4++                 \


#define USECS_PER_SEC 1000000

//: in edroombp for rtems 4.6 this USECS_PER_TICK is 1000, here is 10000
#define CLICKS_PER_SEC	(USECS_PER_SEC/CONFIG_PLATFORM_RTEMS_USECS_PER_TICK)

#define USEC_PER_TICK	(CONFIG_PLATFORM_RTEMS_USECS_PER_TICK)

//#define USEC_PER_TICK	(10000)

typedef uint64_t OS_Time_t;

/* this macro transform ticks to a timespec struct. */
#define _EDROOMBP_ticks_to_timespec(_timespec, _ticks) \
		do { \
			_timespec->tv_sec = _ticks / (CLICKS_PER_SEC * 1); \
			_ticks -= _timespec->tv_sec * (CLICKS_PER_SEC * 1); \
			_timespec->tv_usec = _ticks  * 1000000 / (CLICKS_PER_SEC); \
		}while(0) \


/* convenience functions */
#define _EDROOMBP_timespec_normalize(t) {\
		if ((t)->tv_usec >= USECS_PER_SEC) { \
			(t)->tv_usec -= USECS_PER_SEC; \
			(t)->tv_sec++; \
		}\
		}
/*	Macro for adding two timespec structs	*/
#define _EDROOMBP_timespec_add(t1, t2) do { \
		(t1)->tv_usec += (t2)->tv_usec;  \
		(t1)->tv_sec += (t2)->tv_sec; \
		_EDROOMBP_timespec_normalize(t1);\
} while (0)

#define _EDROOMBP_timespec_add_ns(t,n) do { \
		(t)->tv_usec += (n);  \
		_EDROOMBP_timespec_normalize(t); \
} while (0)

#define _EDROOMBP_timespec_nz(t) ((t)->tv_sec != 0 || (t)->tv_usec != 0)

#define _EDROOMBP_timespec_lt(t1, t2) ((t1)->tv_sec < (t2)->tv_sec || \
		(		\
				(t1)->tv_sec == (t2)->tv_sec && \
				(t1)->tv_usec < (t2)->tv_usec)	\
)

#define _EDROOMBP_timespec_gt(t1, t2) (_EDROOMBP_timespec_lt(t2, t1))

#define _EDROOMBP_timespec_ge(t1, t2) (!_EDROOMBP_timespec_lt(t1, t2))

#define _EDROOMBP_timespec_le(t1, t2) (!_EDROOMBP_timespec_gt(t1, t2))

#define _EDROOMBP_timespec_eq(t1, t2) ((t1)->tv_sec == (t2)->tv_sec && \
		(t1)->tv_usec == (t2)->tv_usec)

//------------------------------------------------------------------------------
/*	Nombres semaforos y tareas	*/
static int8_t nsem_name[] = "0000";
static int8_t ntask_name[] = "0000";
/*	Starting timestamp storage	*/
static EDROOMTimeSpec start_time;
/*	this variable stores the number of ticks per second	*/
static rtems_interval TICKS_PER_SECOND = 0;

#define YEAR    2000
#define MONTH   1
#define DAY     1

/** Establsh the time of day    */
rtems_time_of_day system_tod =
/* YEAR     MONTH   DAY HOUR    MINUTE  SECOND  */
{ YEAR, MONTH, DAY, 0, 0, 0 };

__thread Pr_Task * pPr_Task;

//******************************************************
//****************  Pr_Kernel **************************
//******************************************************

Pr_Kernel::Pr_Kernel()
{
	rtems_time_of_day time_buffer;
//	EDROOMTimeSpec time;

	TICKS_PER_SECOND = rtems_clock_get_ticks_per_second();

	//ASSERT(status == RTEMS_SUCCESSFUL);

	/*  Set the local time  */
	time_buffer.year = system_tod.year;
	time_buffer.month = system_tod.month;
	time_buffer.day = system_tod.day;
	time_buffer.hour = system_tod.hour;
	time_buffer.minute = system_tod.minute;
	time_buffer.second = system_tod.second;
	time_buffer.ticks = 0;

	rtems_clock_set(&time_buffer);
	//ASSERT(status == RTEMS_SUCCESSFUL);

	rtems_clock_get_tod_timeval(&start_time);
	//ASSERT(status == RTEMS_SUCCESSFUL);

//	start_time.tv_sec = time.tv_sec;
//	start_time.tv_usec = time.tv_usec;
}

void Pr_Kernel::Start()
{

#ifdef _EDROOM_IS_DEBUG_
	Pr_SemaphoreBin StartSem("SSem", 0);
#else
	Pr_SemaphoreBin StartSem(0);
#endif

	StartSem.Wait();
}

//******************************************************
//****************  Pr_Task ****************************
//******************************************************


//****************  CONSTRUCTORS ***********************

#ifdef _EDROOM_IS_DEBUG_

Pr_Task::Pr_Task(Pr_TaskRV_t(*_taskCode)(Pr_TaskP_t ignored), /*  Task IP */
const char *_p_name, /*  Task name   */
TEDROOMPriority _priority, /*  task priority   */
unsigned _stackSize) :
	name(_p_name), /*  stack size  */
	semSend("TaskSem Send", 0), semReceive("TaskSem recv", 0)
{
#else

	Pr_Task::Pr_Task(Pr_TaskRV_t (*_taskCode)(Pr_TaskP_t ignored), /*  Task IP */
			TEDROOMPriority _priority, /*  task priority   */
			unsigned _stackSize): /*  stack size  */
		p_data(NULL), semSend(0), semReceive(0)
	{

#endif

	rtems_name r_name;
	rtems_mode r_mode;
	rtems_attribute r_attributes;

	//ASSERT(_taskCode != NULL);
	//ASSERT(_priority <= CONFIG_EDROOMBP_SWR_EDROOM_MAX_PRIORITY);
	//ASSERT(_priority >= CONFIG_EDROOMBP_SWR_EDROOM_MIN_PRIORITY);
	//	ASSERT(_stackSize >= CONFIG_EDROOMBP_SWR_EDROOM_MIN_STACK_SIZE);

	/*  Stablish the task instruction pointer   */
	this->TaskIP = _taskCode;

	/*  Init the task priorities  */
	priorityMsg = priorityTmp = _priority;
	// these are class attributes now. Initialize 'em
	//	stacksize = _stackSize;

	/*
	 * Do we have to build a name for the task? rtems_name IS a uint32_t
	 */
	NEXT_RESOURCE_NAME(ntask_name[0],ntask_name[1],ntask_name[2],ntask_name[3]);
	r_name = rtems_build_name(ntask_name[0], ntask_name[1], ntask_name[2],
			ntask_name[3]);

	r_mode = RTEMS_PREEMPT | RTEMS_NO_ASR | RTEMS_NO_TIMESLICE
			| RTEMS_INTERRUPT_LEVEL(0);

#ifndef CONFIG_EDROOMBP_SWR_FP_ENABLED
	r_attributes = RTEMS_LOCAL;
#else
	r_attributes = RTEMS_FLOATING_POINT | RTEMS_LOCAL;
#endif

	rtems_task_create(r_name, priorityTmp, _stackSize, r_mode,
			r_attributes, &taskID);
	//ASSERT(status == RTEMS_SUCCESSFUL);

	this->TaskIP = _taskCode;

	/* will place the task in 'ready for scheduling' state */
	rtems_task_start(taskID, TaskFunction, (rtems_task_argument) (this));
	//ASSERT(status == RTEMS_SUCCESSFUL);
}



Pr_TaskRV_t Pr_Task::TaskFunction(Pr_TaskP_t arg)
{
	Pr_Task *mythis = (Pr_Task*) arg;
	pPr_Task = mythis;

//	status = rtems_task_variable_add(RTEMS_SELF, (void **)&pPr_Task, NULL);
	//ASSERT(status == RTEMS_SUCCESSFUL);
//	DEBUG("%p", pPr_Task);
	mythis->TaskIP(0);

//	DEBUG("we are about to delete task %d", mythis->taskID);
	//are we finished? lets delete the task and its TCB.
	rtems_task_delete(mythis->taskID);
}

void Pr_Task::SetPriority(TEDROOMPriority _priority)
{
	//ASSERT(_priority >= CONFIG_EDROOMBP_SWR_EDROOM_MIN_PRIORITY);
	//ASSERT(_priority <= CONFIG_EDROOMBP_SWR_EDROOM_MAX_PRIORITY);

	priorityMsg = _priority;

	if (priorityTmp != priorityMsg)
	{
		priorityTmp = priorityMsg;
		ChangePriority(_priority);
	}
}

void Pr_Task::SetMaxPrioTmp(TEDROOMPriority _priority)
{
	//ASSERT(_priority >= CONFIG_EDROOMBP_SWR_EDROOM_MIN_PRIORITY);
	//ASSERT(_priority <= CONFIG_EDROOMBP_SWR_EDROOM_MAX_PRIORITY);
    /*
     * We only change the priority if the new priority is greater than
     * (less value) the priorityTmp value
     */
	if (_priority < priorityTmp)
	{
		priorityTmp = _priority;
		ChangePriority(_priority);
	}
}

void Pr_Task::SetMaxPrioMsg(TEDROOMPriority _priority)
{
	//ASSERT(_priority >= CONFIG_EDROOMBP_SWR_EDROOM_MIN_PRIORITY);
	//ASSERT(_priority <= CONFIG_EDROOMBP_SWR_EDROOM_MAX_PRIORITY);

	if (_priority < priorityMsg)
	{
		priorityMsg = _priority;

		if (priorityMsg < priorityTmp)
		{
			priorityTmp = priorityMsg;
			ChangePriority(_priority);
		}
	}

}

void Pr_Task::RestorePrioMsg(void)
{
	if (priorityTmp != priorityMsg)
	{
		priorityTmp = priorityMsg;
		ChangePriority(priorityMsg);
	}

}

TEDROOMPriority Pr_Task::GetTaskPrio()
{
	return priorityMsg;
}

void Pr_Task::ChangePriority(TEDROOMPriority _priority)
{
	rtems_task_priority old_prio; /*	NOT used further than the call */

	//ASSERT(_priority >= CONFIG_EDROOMBP_SWR_EDROOM_MIN_PRIORITY);
	//ASSERT(_priority <= CONFIG_EDROOMBP_SWR_EDROOM_MAX_PRIORITY);

	rtems_task_set_priority(taskID, (uint32_t) _priority, &old_prio);
	//ASSERT(status == RTEMS_SUCCESSFUL);

}

//******************************************************
//****************  Pr_Time ****************************
//******************************************************

//****************  CONSTRUCTORS ***********************

Pr_Time::Pr_Time()
{
	time.tv_sec = 0;
	time.tv_usec = 0;
}

Pr_Time::Pr_Time(const Pr_Time &_time)
{
	time.tv_usec = _time.time.tv_usec;
	time.tv_sec = _time.time.tv_sec;
}

Pr_Time::Pr_Time(EDROOMTimeSpec _time)
{
	//init the local object with the values given as parameter.
	time.tv_sec = _time.tv_sec;

	time.tv_usec = _time.tv_usec;
}

Pr_Time::Pr_Time(uint32_t _secs, uint32_t _usecs)
{
	//init the local object with the values given as parameter.
	time.tv_sec = _secs;
	time.tv_usec = _usecs;
}

//**************** MODIFIYING METHODS **********************

void edroombp_get_time(void * time_val)
{
	rtems_clock_get_tod_timeval((EDROOMTimeSpec *)time_val);
//	CHECK_RTEMS_STATUS(status);

}

void Pr_Time::GetTime(void)
{
	EDROOMTimeSpec local_time;
	Pr_Time aux;
	//Get the current time to the local_time object.
	edroombp_get_time((void*) &local_time);

	aux = Pr_Time(local_time);
	//substract the start_time values
	aux -= Pr_Time(start_time);
	//object now is the difference between current and start time.
	*this = aux;
}

EDROOMClockTicksType Pr_Time::GetTicks()
{
	Pr_Time aux;
	//Get the current time
	aux.GetTime();
	//return the ticks.
	return aux.Ticks();
}

void Pr_Time::RoudMicrosToTicks(){

	int32_t ticksFromMicroseconds;
	int32_t microsecondsFromTicks;

	ticksFromMicroseconds=time.tv_usec/USEC_PER_TICK;
	microsecondsFromTicks=ticksFromMicroseconds*USEC_PER_TICK;

	if(time.tv_usec!=microsecondsFromTicks){
		microsecondsFromTicks+=USEC_PER_TICK/2;
		if(microsecondsFromTicks <= time.tv_usec){
			time.tv_usec+=USEC_PER_TICK;
			_EDROOMBP_timespec_normalize(&time);
		}
	}
}

//**********   OPERATORS OVERLOAD  *********************

Pr_Time& Pr_Time::operator+=(const Pr_Time &_time)
{

	_EDROOMBP_timespec_add(&time, &(_time.time));

	return *this;
}

Pr_Time& Pr_Time::operator-=(const Pr_Time &_time)
{
	//Check if the left operand tv_sec is higher than the right operand's
	if (_time.time.tv_sec <= time.tv_sec)
	{
		//substract the tv_sec.
		time.tv_sec -= _time.time.tv_sec;
		//Check the tv_usec in the left operand against the right operand's
		if (_time.time.tv_usec > time.tv_usec)
		{
			//tv_usec in left operand is less than in the right operand.
			if (time.tv_sec > 0)
			{
				//decrement tv_sec
				time.tv_sec--;
				//put the correct tv_usec.
				time.tv_usec += USECS_PER_SEC - _time.time.tv_usec;
			} else
			{
				//time is zero.
				time.tv_sec = time.tv_usec = 0;

			}
		} else
		{
			//substract the tv_usec.
			time.tv_usec -= _time.time.tv_usec;
		}
	} else
	{
		//left operand tv_sec is lower than the right operands, so zero is the result.
		time.tv_sec = time.tv_usec = 0;
	}

	return *this;
}

Pr_Time& Pr_Time::operator=(const Pr_Time &_time)
{
	//assign the values in the right operand to the local object.
	time.tv_usec = _time.time.tv_usec;
	time.tv_sec = _time.time.tv_sec;

	return *this;
}

int Pr_Time::operator==(const Pr_Time &_time)
{
	//return if the objects are equal.
	return (_EDROOMBP_timespec_eq(&time, &(_time.time)));

}

int Pr_Time::operator!=(const Pr_Time &_time)
{
	//return if the objects are NOT equal.
	return (!_EDROOMBP_timespec_eq(&time, &(_time.time)));

}

int Pr_Time::operator>(const Pr_Time &_time)
{
	//return if the left operand values are higher than the right operand's values
	return (_EDROOMBP_timespec_gt(&time, &(_time.time)));
}

int Pr_Time::operator<(const Pr_Time &_time)
{
	//return if the left operand values are lower than the right operand's values
	return (_EDROOMBP_timespec_lt(&time, &(_time.time)));
}

int Pr_Time::operator>=(const Pr_Time &_time)
{
	//return if the left operand values are higher or equal than the right operand's values
	return (_EDROOMBP_timespec_ge(&time, &(_time.time)));
}

int Pr_Time::operator<=(const Pr_Time &_time)
{
	//return if the left operand values are lower or equal than the right operand's values
	return (_EDROOMBP_timespec_le(&time, &(_time.time)));
}

//*******   CONVERSION METHODS TO STANDARD UNITS   ******

uint32_t Pr_Time::Ticks() const
{
	uint32_t TimeInTicks;
	//convert tv_sec and tv_usec to ticks.
	TimeInTicks = (uint32_t) ((time.tv_sec * CLICKS_PER_SEC)
	+ (time.tv_usec / USEC_PER_TICK));
	return TimeInTicks;
}


void Pr_DelayIn(const Pr_Time &_interval)
{
	rtems_interval ticks;

	ticks = (rtems_interval) _interval.Ticks();

	rtems_task_wake_after(ticks);

	//ASSERT(status == RTEMS_SUCCESSFUL);

}

void Pr_DelayAt(const Pr_Time &_time)
{
	EDROOMTimeSpec time;

	float sec1, sec2;
	rtems_interval intervalo;

	rtems_clock_get_tod_timeval(&time);
	//ASSERT(status == RTEMS_SUCCESSFUL);

	time.tv_sec -= start_time.tv_sec;
	time.tv_usec -= start_time.tv_usec;

	sec1 = time.tv_sec + (float) (time.tv_usec / USECS_PER_SEC);
	sec2 = _time.time.tv_sec + (float) (_time.time.tv_usec
			/ USECS_PER_SEC);

	if (sec2 > sec1)
	{
		sec2 -= sec1;

		time.tv_sec = (uint32_t) sec2;
		time.tv_usec = (uint32_t) ((sec2 - time.tv_sec)
				* USECS_PER_SEC);
	} else {

#ifdef PRINTF_LOGS

		printf("too late!");
#endif
		return; // zero delay
	}

	intervalo = (time.tv_sec * USECS_PER_SEC) + time.tv_usec;

	rtems_task_wake_after(
			intervalo / CONFIG_PLATFORM_RTEMS_USECS_PER_TICK);
	//ASSERT(status == RTEMS_SUCCESSFUL);

}

//********************************************************
//********************  Pr_Semaphore  ********************
//********************************************************

Pr_Semaphore::Pr_Semaphore(uint32_t _value)
{
}

//********************************************************
//********************  Pr_SemaphoreBin  *****************
//********************************************************


#ifdef _EDROOM_IS_DEBUG_
Pr_SemaphoreBin::Pr_SemaphoreBin(char *p_name, uint32_t _value) :
	Pr_Semaphore(_value), name(p_name)

#else
Pr_SemaphoreBin::Pr_SemaphoreBin(uint32_t _value) : Pr_Semaphore(_value)
#endif

{
	rtems_name r_name;
	rtems_attribute attributes;

	/*
	 * Build de name of the semaphore
	 */
	NEXT_RESOURCE_NAME(nsem_name[0],nsem_name[1],nsem_name[2],nsem_name[3]);
	r_name = rtems_build_name(nsem_name[0], nsem_name[1], nsem_name[2],
			nsem_name[3]);
	/*	Create the semaphore	*/
	attributes = RTEMS_DEFAULT_ATTRIBUTES;
	rtems_semaphore_create(r_name, _value, attributes,
			0, &sem);

	//ASSERT(status == RTEMS_SUCCESSFUL);
}

void Pr_SemaphoreBin::Signal()
{
	rtems_semaphore_release(sem);
}

void Pr_SemaphoreBin::Wait()
{
	rtems_semaphore_obtain(sem, RTEMS_WAIT, RTEMS_NO_TIMEOUT);
}

int32_t Pr_SemaphoreBin::WaitCond()
{
	rtems_status_code status;

	status = rtems_semaphore_obtain(sem, RTEMS_NO_WAIT, RTEMS_NO_TIMEOUT);

	return (status == RTEMS_SUCCESSFUL);
}

bool Pr_SemaphoreBin::WaitTimed(const Pr_Time &_waittime)
{
	rtems_status_code status;
	rtems_interval TimeInTicks;

	TimeInTicks = (rtems_interval) ((_waittime.time.tv_sec * CLICKS_PER_SEC)
							+ (_waittime.time.tv_usec * CLICKS_PER_SEC)/1000000);
	
	if(TimeInTicks == 0)
	{
		status = rtems_semaphore_obtain(sem, RTEMS_NO_WAIT, RTEMS_NO_TIMEOUT);
	}
	else
	{
		/*	Must be RTEMS_WAIT, otherwise Timeout is ignored	*/
		status = rtems_semaphore_obtain(sem, RTEMS_WAIT, TimeInTicks);
	}


	return (status == RTEMS_SUCCESSFUL);
}

Pr_SemaphoreBin::~Pr_SemaphoreBin()
{
	/* we must make sure the semaphore is given  to delete it */
	rtems_semaphore_release(sem);
	/*check if everything was ok with the deletion? 	*/
	rtems_semaphore_delete(sem);
}

//********************************************************
//********************  Pr_SemaphoreRec  *****************
//********************************************************
#define MUTEX_ATTS      \
        (  RTEMS_PRIORITY                       \
         | RTEMS_BINARY_SEMAPHORE       \
         | RTEMS_INHERIT_PRIORITY)

#ifdef _EDROOM_IS_DEBUG_
Pr_SemaphoreRec::Pr_SemaphoreRec(const char *p_name) : name(p_name)
#else
Pr_SemaphoreRec::Pr_SemaphoreRec() : prio_ceiling(255)
#endif
{
	rtems_id possible_semid;
	rtems_name r_name;

	prio_type = RTEMS_PRIORITY | RTEMS_BINARY_SEMAPHORE  | RTEMS_INHERIT_PRIORITY;

	NEXT_RESOURCE_NAME(nsem_name[0],nsem_name[1],nsem_name[2],nsem_name[3]);
	r_name = rtems_build_name(nsem_name[0], nsem_name[1], nsem_name[2],
																nsem_name[3]);

	rtems_semaphore_create(r_name, 1, (rtems_attribute)prio_type,
			RTEMS_NO_PRIORITY , &possible_semid);
	//ASSERT(status == RTEMS_SUCCESSFUL);

	mutex = possible_semid;
}

#ifdef _EDROOM_IS_DEBUG_
Pr_SemaphoreRec::Pr_SemaphoreRec(const char *p_name, int prioceiling) : name(p_name)
#else
Pr_SemaphoreRec::Pr_SemaphoreRec(int32_t prioceiling)
#endif
{
	rtems_id possible_semid;
	rtems_name r_name;
	int priority_ceiling;

	prio_type = RTEMS_PRIORITY | RTEMS_BINARY_SEMAPHORE |
										RTEMS_PRIORITY_CEILING | RTEMS_LOCAL;

	priority_ceiling = prioceiling;
	priority_ceiling = (priority_ceiling < 1) ? 1 : priority_ceiling;

	prio_ceiling = priority_ceiling;

	NEXT_RESOURCE_NAME(nsem_name[0],nsem_name[1],nsem_name[2],nsem_name[3]);
	r_name = rtems_build_name(nsem_name[0], nsem_name[1], nsem_name[2],
																nsem_name[3]);

	rtems_semaphore_create(r_name, 1, (rtems_attribute)prio_type,
											prio_ceiling, &possible_semid);
	//ASSERT(status == RTEMS_SUCCESSFUL);

	mutex = possible_semid;
}

void Pr_SemaphoreRec::Signal()
{
	rtems_semaphore_release(mutex);
}

void Pr_SemaphoreRec::Wait()
{
	rtems_semaphore_obtain(mutex, RTEMS_WAIT, RTEMS_NO_TIMEOUT);
	//ASSERT(status == RTEMS_SUCCESSFUL);
}

int32_t Pr_SemaphoreRec::WaitCond()
{
	rtems_status_code status;

	status = rtems_semaphore_obtain(mutex, RTEMS_NO_WAIT, RTEMS_NO_TIMEOUT);

	return (status == RTEMS_SUCCESSFUL);
}

Pr_SemaphoreRec::~Pr_SemaphoreRec()
{
	/* we must make sure the semaphore is given  to delete it */
	rtems_semaphore_release(mutex);
	/*check if everything was ok with the deletion? 	*/
	rtems_semaphore_delete(mutex);
}

void Pr_Send(Pr_Task &_task, void *_p_data)
{
	_task.p_data = _p_data;
	_task.semReceive.Signal();
	_task.semSend.Wait();
}

void Pr_Receive(void * _p_data, unsigned _datalength)
{
	Pr_Task *receiver;

	receiver = pPr_Task;
//	DEBUG("%p",pPr_Task);
	receiver->semReceive.Wait();

	uint8_t *p_dataAux, *p_dataAuxReceiver;

	p_dataAux = (uint8_t *) _p_data;
	p_dataAuxReceiver = (uint8_t *) (receiver->p_data);

	for (unsigned int i = 0; i < _datalength; ++i)
		*(p_dataAux + i) = *(p_dataAuxReceiver + i);

	receiver->semSend.Signal();

}

//********************************************************
//********************  Pr_IRQManager ********************
//********************************************************


void Pr_IRQManager::DisableAllIRQs(void)
{
	rtems_interrupt_level rtems_level;

	rtems_interrupt_disable(rtems_level);
}

void Pr_IRQManager::EnableAllIRQs(void)
{
	rtems_interrupt_enable(0);
}

void Pr_IRQManager::ApplyCurrentIRQMask(void)
{
	//rtems_interrupt_enable(0);
}

#define RTEMS_INTERRUPT	1
#define RAW_INTERRUPT	0

void Pr_IRQManager::InstallIRQHandler(Pr_IRQHandler handler,
		uint8_t IRQLevel, uint8_t IRQVectorNumber)
{
	rtems_isr_entry old_handler; /*NOT used further than the call's return*/

#ifdef CONFIG_ARCH_SPARC
	old_handler = set_vector((rtems_isr_entry) handler,
			(rtems_vector_number) IRQVectorNumber, RTEMS_INTERRUPT);
#else
#error "no es arquitectura SPARC! metodo InstallIRQHandler no implementado"
#endif

}

void Pr_IRQManager::DeinstallIRQHandler(uint8_t IRQLevel,
		uint8_t IRQVectorNumber)
{

}

void Pr_IRQManager::MaskIRQ(uint32_t IRQVectorNumber)
{
	//ASSERT(IRQVectorNumber>=0x10);
	//ASSERT(IRQVectorNumber<0x20);

#ifdef CONFIG_MP_ERC32
	ERC32_Mask_interrupt(IRQVectorNumber-0x10);
#else
	leon3_mask_irq(IRQVectorNumber-0x10);
#endif
}

void Pr_IRQManager::UnMaskIRQ(uint32_t IRQVectorNumber)
{
	//ASSERT(IRQVectorNumber>=0x10);
	//ASSERT(IRQVectorNumber<0x20);

#ifdef CONFIG_MP_ERC32
	ERC32_Unmask_interrupt(IRQVectorNumber-0x10);
#else
	leon3_unmask_irq(IRQVectorNumber-0x10);
#endif
}

//********************************************************
//********************  Pr_IRQEvent ********************
//********************************************************

#ifdef _EDROOM_IS_DEBUG_

Pr_IRQEvent::Pr_IRQEvent(const char * pname, unsigned char IRQ) :
	irq_event(0), //event
			name(pname) // the Event name
{
	//ASSERT(IRQ < 32); /*	0..15 exceptions(�?) - 16...31 irqs	*/

	irq_event = (1 << IRQ);
	caller_task_id = 0;

}

#else

Pr_IRQEvent::Pr_IRQEvent(uint8_t IRQ) : irq_event(0)
{

	//ASSERT(IRQ < 32);

	irq_event = (1 << IRQ);
	caller_task_id = 0;
	//	DEBUG("irq_event = 0x%x", irq_event);
}

#endif

void Pr_IRQEvent::Signal()
{

	//ASSERT(irq_event != 0);
	//ASSERT(caller_task_id != 0);

	rtems_event_send(caller_task_id, irq_event);

	//ASSERT(status == RTEMS_SUCCESSFUL);
}

void Pr_IRQEvent::Wait()
{
	rtems_event_set event_out;

	//ASSERT(irq_event != 0);
	//store the rtems_id of the caller task.
	rtems_task_ident(RTEMS_SELF, RTEMS_SEARCH_ALL_NODES, &caller_task_id);

	//ASSERT(status == RTEMS_SUCCESSFUL);
	//wait for the event to happen.
	rtems_event_receive(irq_event, RTEMS_WAIT, RTEMS_NO_TIMEOUT,
			&event_out);

	//ASSERT((status == RTEMS_SUCCESSFUL) && (event_out == irq_event));

}

bool Pr_IRQEvent::WaitTimed(Pr_Time _time)
{
	rtems_interval TimeInTicks;
	rtems_event_set event_out;

	//ASSERT(irq_event != 0);

	rtems_task_ident( RTEMS_SELF, RTEMS_SEARCH_ALL_NODES,
															&caller_task_id );

	//ASSERT(status == RTEMS_SUCCESSFUL);

	TimeInTicks = (uint32_t) _time.Ticks();
	/*	Must be RTEMS_WAIT, otherwise Timeout is ignored	*/
	rtems_event_receive(irq_event, RTEMS_WAIT, TimeInTicks,
					&event_out);

//	ASSERT(status == RTEMS_SUCCESSFUL);

	return (event_out == irq_event);
}

bool Pr_IRQEvent::WaitCond()
{
	rtems_event_set event_out;

	//ASSERT(irq_event != 0);
	//ASSERT(caller_task_id == 0);

	rtems_task_ident( RTEMS_SELF, RTEMS_SEARCH_ALL_NODES,
															&caller_task_id );

	//ASSERT(status == RTEMS_SUCCESSFUL);

	rtems_event_receive(irq_event, RTEMS_NO_WAIT, RTEMS_NO_TIMEOUT,
			&event_out);

	return (irq_event == event_out);

}

