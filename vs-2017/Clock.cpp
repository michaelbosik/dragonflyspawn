//
//Clock.cpp
//

#include "clock.h";
#include <Windows.h>;

// Constructor
// Sets previous_time to current time.
df::Clock::Clock() {
	SYSTEMTIME time;
	GetSystemTime(&time);
	m_previous_time = (time.wMinute * 6000) +
		(time.wSecond * 1000) +
		(time.wMilliseconds);
}

// Return time elapsed since delta() was called, -1 if error.
// Resets clock time.
// Units are microseconds.
long int df::Clock::delta() {
	SYSTEMTIME currentTime;
	GetSystemTime(&currentTime);
	long int beforeCall = m_previous_time;
	long int afterCall = (currentTime.wMinute * 6000) + 
		(currentTime.wSecond * 1000) +
		(currentTime.wMilliseconds);
	long int elapsedTime = afterCall - beforeCall;
	m_previous_time = afterCall;
	return elapsedTime;

}

// Return time elapsed since delta() was called, -1 if error.
// Does not reset clock time.
// Units are microseconds.
long int df::Clock::split() const {
	SYSTEMTIME currentTime;
	GetSystemTime(&currentTime);
	long int beforeCall = m_previous_time;
	long int afterCall = (currentTime.wMinute * 6000) +
		(currentTime.wSecond * 1000) +
		(currentTime.wMilliseconds);
	long int elapsedTime = afterCall - beforeCall;
	return elapsedTime;
}