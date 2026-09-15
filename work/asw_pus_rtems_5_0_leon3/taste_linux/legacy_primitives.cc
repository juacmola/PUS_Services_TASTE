// Time arithmetic adapted from the EDROOM RTEMS implementation in
// service_libraries/edroomsl/edroombp/src/rtemsapi_5_1/rtems_5_1/edroombp.cc.
// Copyright (c) 2011 Alberto Carrasco Gallardo, Universidad de Alcala.
// Distributed under GNU GPL v2, as is the original implementation.
// Linux primitives used by the PUS library. TASTE owns tasks and dispatch.
#ifdef GENERIC_LINUX_TARGET
#include "../service_libraries/edroomsl/edroombp/include/public/edroombp.h"
#include <chrono>
#include <thread>

namespace {
const std::chrono::steady_clock::time_point& epoch() {
    static const auto start = std::chrono::steady_clock::now();
    return start;
}
}

Pr_Semaphore::Pr_Semaphore(uint32_t) {}
Pr_SemaphoreRec::Pr_SemaphoreRec() : prio_type(0), prio_ceiling(255) {}
Pr_SemaphoreRec::Pr_SemaphoreRec(int32_t ceiling)
    : prio_type(0), prio_ceiling(ceiling) {}
Pr_SemaphoreRec::~Pr_SemaphoreRec() = default;
void Pr_SemaphoreRec::Wait() { mutex.lock(); }
void Pr_SemaphoreRec::Signal() { mutex.unlock(); }
int32_t Pr_SemaphoreRec::WaitCond() { return mutex.try_lock(); }

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

void Pr_Time::GetTime() {
    const auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(
        std::chrono::steady_clock::now() - epoch()).count();
    time.tv_sec = elapsed / 1000000;
    time.tv_usec = elapsed % 1000000;
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



void Pr_DelayIn(const Pr_Time& interval) {
    std::this_thread::sleep_for(std::chrono::seconds(interval.time.tv_sec)
        + std::chrono::microseconds(interval.time.tv_usec));
}
void Pr_DelayAt(const Pr_Time& deadline) {
    std::this_thread::sleep_until(epoch() + std::chrono::seconds(deadline.time.tv_sec)
        + std::chrono::microseconds(deadline.time.tv_usec));
}
#endif
