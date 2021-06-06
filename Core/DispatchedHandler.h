//=====================
// DispatchedHandler.h
//=====================

#pragma once


//=======
// Using
//=======

#include <functional>
#include "Handle.h"
#include "TypeHelper.h"


//===========
// Namespace
//===========

namespace Core {


//====================
// Dispatched-Handler
//====================

class DispatchedHandler
{
public:
	// Con-/Destructors
	virtual ~DispatchedHandler() {}

	// Common
	virtual VOID Run()=0;

protected:
	// Con-/Destructors
	DispatchedHandler() {}
};


//==========================
// Dispatched-Handler Typed
//==========================

template <class _owner_t, class... _args_t>
class DispatchedHandlerTyped: public DispatchedHandler
{
public:
	// Handler
	typedef VOID (_owner_t::*_proc_t)(_args_t...);

	// Con-/Destructors
	DispatchedHandlerTyped(_owner_t* Owner, _proc_t Procedure, _args_t... Arguments):
		cProcedure([Owner, Procedure, Arguments...]() { (Owner->*Procedure)(Arguments...); }),
		hOwner(Owner)
		{}

	// Common
	VOID Run()override { cProcedure(); }

private:
	// Common
	std::function<VOID()> cProcedure;
	Handle<_owner_t> hOwner;
};

}