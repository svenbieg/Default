//===============
// Application.h
//===============

#pragma once


//=======
// Using
//=======

#include "Dispatcher.h"


//===========
// Namespace
//===========

namespace Core {


//=============
// Application
//=============

class Application: public Object
{
public:
	// Common
	static Handle<Application> Current;
	template <class _owner_t, class... _args_t> VOID Dispatch(_owner_t* Owner, VOID (_owner_t::*Procedure)(_args_t...), _args_t... Arguments)
		{
		cDispatcher.Dispatch(Owner, Procedure, Arguments...);
		}
	Event<Application> Loop;
	static Handle<String> Name;
	static Handle<String> Version;

protected:
	// Con-/Destructors
	Application(Handle<String> Name);

	// Common
	VOID OnLoop();
	Dispatcher cDispatcher;
};

}