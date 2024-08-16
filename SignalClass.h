//===============
// SignalClass.h
//===============

#pragma once


//=======
// Using
//=======

#include <condition_variable>
#include "MutexClass.h"


//========
// Signal
//========

class Signal
{
public:
	// Con-/Destructors
	Signal() {}

	// Common
	inline VOID Broadcast() { cCondition.notify_all(); }
	inline VOID Wait(ScopedLock& Lock) { cCondition.wait(Lock.cLock); }
	inline BOOL Wait(ScopedLock& Lock, UINT Timeout)
		{
		auto status=cCondition.wait_for(Lock.cLock, std::chrono::milliseconds(Timeout));
		if(status==std::cv_status::timeout)
			return false;
		return true;
		}

private:
	// Common
	std::condition_variable cCondition;
};
