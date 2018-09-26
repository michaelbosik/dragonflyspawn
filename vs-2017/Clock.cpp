//
//Clock.cpp
//

#include "Clock.h"
#include "Windows.h"

// Sets previous_time to current time.
df::Clock::Clock() {
	SYSTEMTIME sysTime;
	GetSystemTime(&sysTime);
	m_previous_time = (sysTime.wMinute * 6000) + (sysTime.wSecond * 1000) + sysTime.wMilliseconds;
}

// Return time elapsed since delta() was called, -1 if error.
// Resets clock time.
// Units are microseconds.
long int df::Clock::delta() {
	SYSTEMTIME sysTime;
	GetSystemTime(&sysTime);
	long int preTime = m_previous_time;
	long int postTime = (sysTime.wMinute * 6000) + (sysTime.wSecond * 1000) + sysTime.wMilliseconds;
	long int elapsedTime = postTime - preTime;
	m_previous_time = postTime;
	return elapsedTime;
}

// Return time elapsed since delta() was called, -1 if error.
// Does not reset clock time.
// Units are microseconds.
long int df::Clock::split() const{
	SYSTEMTIME sysTime;
	GetSystemTime(&sysTime);
	long int preTime = m_previous_time;
	long int postTime = (sysTime.wMinute * 6000) + (sysTime.wSecond * 1000) + sysTime.wMilliseconds;
	long int elapsedTime = postTime - preTime;
	return elapsedTime;
}