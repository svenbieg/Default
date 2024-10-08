//===============
// Application.h
//===============

#pragma once


//=======
// Using
//=======

#include "DispatchedHandler.h"


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
	// Friends
	friend class Timer;

	// Common
	static Handle<Application> Current;
	inline VOID Dispatch(VOID (*Procedure)())
		{
		DispatchedHandler* handler=new Details::DispatchedProcedure(Procedure);
		Dispatch(handler);
		}
	template <class... _args_t> inline VOID Dispatch(VOID (*Procedure)(_args_t...), _args_t... Arguments)
		{
		DispatchedHandler* handler=new Details::DispatchedProcedureWithArgs<_args_t...>(Procedure, Arguments...);
		Dispatch(handler);
		}
	template <class _owner_t> inline VOID Dispatch(_owner_t* Owner, Function<VOID()> Function)
		{
		DispatchedHandler* handler=new Details::DispatchedFunction<_owner_t>(Owner, Function);
		Dispatch(handler);
		}
	template <class _owner_t, class _lambda_t, class... _args_t> inline VOID Dispatch(_owner_t* Owner, _lambda_t Lambda, _args_t... Arguments)
		{
		DispatchedHandler* handler=new Details::DispatchedFunction<_owner_t, _args_t...>(Owner, Lambda, Arguments...);
		Dispatch(handler);
		}
	template <class _owner_t, class... _args_t> inline VOID Dispatch(_owner_t* Owner, VOID (_owner_t::*Procedure)(_args_t...), _args_t... Arguments)
		{
		DispatchedHandler* handler=new Details::DispatchedMemberFunction<_owner_t, _args_t...>(Owner, Procedure, Arguments...);
		Dispatch(handler);
		}
	template <class _owner_t, class... _args_t> inline VOID Dispatch(Handle<_owner_t> Owner, VOID (_owner_t::*Procedure)(_args_t...), _args_t... Arguments)
		{
		DispatchedHandler* handler=new Details::DispatchedMemberFunction<_owner_t, _args_t...>(Owner, Procedure, Arguments...);
		Dispatch(handler);
		}
	VOID HandleDispatched();
	LPCSTR Name;
	volatile BOOL Running;
	VOID Quit();
	LPCSTR Version;

protected:
	// Con-/Destructors
	Application(LPCSTR Name, LPCSTR Version="1.0");

	// Common
	virtual VOID OnDispatched() {}

private:
	// Common
	VOID Dispatch(DispatchedHandler* Handler);
	Handle<DispatchedHandler> hDispatched;
};

}
