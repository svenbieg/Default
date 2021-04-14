//================
// Dispatcher.cpp
//================

#include "pch.h"


//=======
// Using
//=======

#include "Dispatcher.h"


//===========
// Namespace
//===========

namespace Core {


//==================
// Con-/Destructors
//==================

Dispatcher::Dispatcher()
{}


//========
// Common
//========

VOID Dispatcher::Run()
{
while(1)
	{
	cCriticalSection.Lock();
	auto handler=cHandlerList.get_at(0);
	if(handler)
		cHandlerList.remove_at(0);
	cCriticalSection.Unlock();
	if(!handler)
		return;
	handler->Run();
	delete handler;
	}
}

}