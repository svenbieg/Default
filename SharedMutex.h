//===============
// SharedMutex.h
//===============

#pragma once


//=======
// Using
//=======

#include <shared_mutex>


//==============
// Shared Mutex
//==============

class SharedMutex
{
public:
	// Friends
	friend class SharedLock;
	friend class UniqueLock;

	// Con-/Destructors
	SharedMutex() {}

	// Common
	inline VOID Lock() { cMutex.lock(); }
	inline VOID LockShared() { cMutex.lock_shared(); }
	inline VOID Unlock() { cMutex.unlock(); }
	inline VOID UnlockShared() { cMutex.unlock_shared(); }

private:
	// Common
	std::shared_mutex cMutex;
};


//=============
// Shared Lock
//=============

class SharedLock
{
public:
	// Con-/Destructors
	SharedLock(SharedMutex& Mutex): cLock(Mutex.cMutex) {}

	// Common
	inline VOID Lock() { cLock.lock(); }
	inline VOID Release() { cLock.release(); }
	inline VOID Unlock() { cLock.unlock(); }

private:
	// Common
	std::shared_lock<std::shared_mutex> cLock;
};


//=============
// Unique Lock
//=============

class UniqueLock
{
public:
	// Con-/Destructors
	UniqueLock(SharedMutex& Mutex): cLock(Mutex.cMutex) {}

	// Common
	inline VOID Lock() { cLock.lock(); }
	inline VOID Release() { cLock.release(); }
	inline VOID Unlock() { cLock.unlock(); }

private:
	// Common
	std::unique_lock<std::shared_mutex> cLock;
};

