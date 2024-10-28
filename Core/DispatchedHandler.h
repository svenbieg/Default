//=====================
// DispatchedHandler.h
//=====================

#pragma once


//=======
// Using
//=======

#include <utility>
#include "Function.h"


//===========
// Namespace
//===========

namespace Core {


//====================
// Dispatched-Handler
//====================

class DispatchedHandler: public Object
{
public:
	// Con-/Destructors
	virtual ~DispatchedHandler() {}

	// Common
	static VOID Append(Handle<DispatchedHandler>& Dispatched, DispatchedHandler* Handler);
	static Handle<DispatchedHandler> Remove(Handle<DispatchedHandler>& Dispatched)
		{
		Handle<DispatchedHandler> dispatched=Dispatched;
		if(dispatched)
			Dispatched=dispatched->m_Next;
		return dispatched;
		}
	static VOID Remove(Handle<DispatchedHandler>& Dispatched, DispatchedHandler* Handler);
	virtual VOID Run()=0;
	virtual VOID Wait()=0;

protected:
	// Con-/Destructors
	DispatchedHandler() {}

	// Common
	Concurrency::Signal m_Done;
	Concurrency::Mutex m_Mutex;
	Handle<DispatchedHandler> m_Next;
};


//===========
// Procedure
//===========

namespace Details {

class DispatchedProcedure: public DispatchedHandler
{
public:
	// Using
	typedef VOID (*_proc_t)();

	// Con-/Destructors
	DispatchedProcedure(_proc_t Procedure): m_Procedure(Procedure) {}

	// Common
	VOID Run()override
		{
		Concurrency::ScopedLock lock(m_Mutex);
		(*m_Procedure)();
		m_Procedure=nullptr;
		m_Done.Trigger();
		}
	VOID Wait()override
		{
		Concurrency::ScopedLock lock(m_Mutex);
		if(m_Procedure)
			m_Done.Wait(lock);
		}

private:
	// Common
	_proc_t m_Procedure;
};}


//==================
// Member-Procedure
//==================

namespace Details {

template <class _owner_t>
class DispatchedMemberProcedure: public DispatchedHandler
{
public:
	// Procedure
	typedef VOID (_owner_t::*_proc_t)();

	// Con-/Destructors
	DispatchedMemberProcedure(_owner_t* Owner, _proc_t Procedure):
		m_Owner(Owner),
		m_Procedure(Procedure)
		{}

	// Common
	VOID Run()override
		{
		Concurrency::ScopedLock lock(m_Mutex);
		(m_Owner->*m_Procedure)();
		m_Procedure=nullptr;
		m_Done.Trigger();
		}
	VOID Wait()override
		{
		Concurrency::ScopedLock lock(m_Mutex);
		if(m_Procedure)
			m_Done.Wait(lock);
		}

private:
	// Common
	_proc_t m_Procedure;
	Handle<_owner_t> m_Owner;
};}


//========
// Lambda
//========

namespace Details {

template <class _owner_t, class _lambda_t>
class DispatchedLambda: public DispatchedHandler
{
public:
	// Con-/Destructors
	DispatchedLambda(_owner_t* Owner, _lambda_t&& Lambda):
		m_Lambda(std::move(Lambda)),
		m_Owner(Owner) {}

	// Common
	inline VOID Run()override
		{
		Concurrency::ScopedLock lock(m_Mutex);
		m_Lambda();
		m_Owner=nullptr;
		m_Done.Trigger();
		}
	VOID Wait()override
		{
		Concurrency::ScopedLock lock(m_Mutex);
		if(m_Owner)
			m_Done.Wait(lock);
		}

private:
	// Common
	_lambda_t m_Lambda;
	Handle<_owner_t> m_Owner;
};}

}
