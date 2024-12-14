//=====================
// DispatchedQueue.cpp
//=====================

#include "pch.h"


//=======
// Using
//=======

#include "DispatchedQueue.h"


//===========
// Namespace
//===========

namespace Concurrency {


//========
// Common
//========

VOID DispatchedQueue::Append(DispatchedHandler* handler)
{
assert(handler->m_Next==nullptr);
ScopedLock lock(s_Mutex);
if(!s_Last)
	{
	s_First=handler;
	s_Last=handler;
	return;
	}
s_Last->m_Next=handler;
s_Last=handler;
s_Signal.Trigger();
}

VOID DispatchedQueue::Begin()
{
ScopedLock lock(s_Mutex);
while(s_Signal.Wait(lock))
	Run();
}

VOID DispatchedQueue::Exit()
{
s_Signal.Cancel();
}

VOID DispatchedQueue::Run()
{
ScopedLock lock(s_Mutex);
auto handler=s_First;
s_First=nullptr;
s_Last=nullptr;
lock.Unlock();
while(handler)
	{
	handler->Run();
	auto next=handler->m_Next;
	delete handler;
	handler=next;
	}
}


//================
// Common Private
//================

DispatchedHandler* DispatchedQueue::s_First=nullptr;
DispatchedHandler* DispatchedQueue::s_Last=nullptr;
Mutex DispatchedQueue::s_Mutex;
Signal DispatchedQueue::s_Signal;

}