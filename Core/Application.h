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
	// Common
	static Handle<Application> Current;
	inline Handle<DispatchedHandler> Dispatch(VOID (*Procedure)())
		{
		DispatchedHandler* handler=new Details::DispatchedProcedure(Procedure);
		DispatchHandler(handler);
		return handler;
		}
	template <class _owner_t, class... _args_t> inline Handle<DispatchedHandler> Dispatch(_owner_t* Owner, VOID (_owner_t::*Procedure)())
		{
		DispatchedHandler* handler=new Details::DispatchedMemberProcedure<_owner_t>(Owner, Procedure);
		DispatchHandler(handler);
		return handler;
		}
	template <class _owner_t, class _lambda_t> inline Handle<DispatchedHandler> Dispatch(_owner_t* Owner, _lambda_t&& Lambda)
		{
		DispatchedHandler* handler=new Details::DispatchedLambda<_owner_t, _lambda_t>(Owner, std::forward<_lambda_t>(Lambda));
		DispatchHandler(handler);
		return handler;
		}
	template <class _owner_t, class _lambda_t> inline Handle<DispatchedHandler> Dispatch(Handle<_owner_t> Owner, _lambda_t&& Lambda)
		{
		DispatchedHandler* handler=new Details::DispatchedLambda<_owner_t, _lambda_t>(Owner, std::forward<_lambda_t>(Lambda));
		DispatchHandler(handler);
		return handler;
		}
	virtual VOID DispatchHandler(DispatchedHandler* Handler);
	LPCSTR Name;
	virtual INT Run();
	volatile BOOL Running;
	virtual VOID Quit();
	LPCSTR Version;

protected:
	// Using
	using DispatchedHandler=Core::DispatchedHandler;

	// Con-/Destructors
	Application(LPCSTR Name, LPCSTR Version="1.0");

	// Common
	Concurrency::Signal m_Dispatched;
	Handle<DispatchedHandler> m_DispatchedHandler;
	Concurrency::Mutex m_Mutex;
};

}
