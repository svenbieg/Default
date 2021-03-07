//============
// Function.h
//============

#pragma once


//=======
// Using
//=======

#include "Handle.h"
#include "Object.h"


//==========
// Function
//==========

template <class _ret_t, class... _args_t>
class Function
{
public:
	// Common
	template <class _func_t> Function(_func_t Function)
		{
		hCallable=new CallableTyped<_func_t>(Function);
		}
	_ret_t operator()(_args_t... Arguments) { return hCallable->operator()(Arguments...); }

private:
	// Callable
	class Callable: public Object
		{
		public:
			virtual _ret_t operator()(_args_t... Arguments)=0;
		};

	// Callable Typed
	template <class _func_t>
	class CallableTyped: public Callable
		{
		public:
			CallableTyped(_func_t Function): tFunction(Function) {}
			_ret_t operator()(_args_t... Arguments)override { return tFunction(Arguments...); }

		private:
			_func_t tFunction;
		};

	// Common
	Handle<Callable> hCallable;
};
