//==============
// Dispatcher.h
//==============

#pragma once


//=======
// Using
//=======

#include "Clusters/list.hpp"
#include "DispatchedHandler.h"
#include "ScopedLock.h"


//===========
// Namespace
//===========

namespace Core {


//============
// Dispatcher
//============

class Dispatcher
{
private:
	// Using
	using HandlerList=Clusters::list<DispatchedHandler*>;

public:
	// Con-/Destructors
	Dispatcher();

	template <class _owner_t, class... _args_t> VOID Dispatch(_owner_t* Owner, VOID (_owner_t::*Procedure)(_args_t...), _args_t... Arguments)
		{
		ScopedLock lock(cCriticalSection);
		cHandlerList.append(new DispatchedHandlerTyped<_owner_t, _args_t...>(Owner, Procedure, Arguments...));
		}
	VOID Run();

private:
	// Common
	CriticalSection cCriticalSection;
	HandlerList cHandlerList;
};

}