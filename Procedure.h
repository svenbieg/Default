//=============
// Procedure.h
//=============

#pragma once


//=======
// Using
//=======

#include "Handle.h"
#include "Object.h"


//===========
// Procedure
//===========

class Procedure
{
public:
	// Con-/Destructors
	Procedure() {}
	Procedure(Procedure const& Procedure):
		hCallable(Procedure.hCallable)
		{}
	template <class _proc_t> Procedure(_proc_t Procedure)
		{
		hCallable=new CallableTyped<_proc_t>(Procedure);
		}

	// Assignment
	Procedure& operator=(Procedure const& Procedure)
		{
		hCallable=Procedure.hCallable;
		return *this;
		}
	template <class _proc_t> Procedure& operator=(_proc_t Procedure)
		{
		hCallable=new CallableTyped<_proc_t>(Procedure);
		return *this;
		}

	// Common
	VOID operator()()const
		{
		if(hCallable)
			hCallable->Run();
		}

private:
	// Callable
	class Callable: public Object
		{
		public:
			virtual VOID Run()=0;
		};

	// Callable Typed
	template <class _proc_t>
	class CallableTyped: public Callable
		{
		public:
			CallableTyped(_proc_t Procedure): tProcedure(Procedure) {}
			VOID Run()override { tProcedure(); }

		private:
			_proc_t tProcedure;
		};

	// Common
	Handle<Callable> hCallable;
};
