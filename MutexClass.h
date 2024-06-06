//==============
// MutexClass.h
//==============

#pragma once


//=======
// Using
//=======

#include <mutex>


//=======
// Mutex
//=======

class Mutex
{
public:
	// Friends
	friend class ScopedLock;

	// Con-/Destructors
	Mutex() {}

	// Common
	inline VOID Lock() { cMutex.lock(); }
	inline BOOL TryLock() { return cMutex.try_lock(); }
	inline VOID Unlock() { cMutex.unlock(); }

private:
	// Common
	std::mutex cMutex;
};


//=============
// Scoped Lock
//=============

class ScopedLock
{
public:
	// Friends
	friend class Signal;

	// Con-/Destructors
	ScopedLock(Mutex& Mutex): cLock(Mutex.cMutex) {}

	// Common
	inline VOID Lock() { cLock.lock(); }
	inline VOID Release() { cLock.release(); }
	inline VOID Unlock() { cLock.unlock(); }

private:
	// Common
	std::unique_lock<std::mutex> cLock;
};
