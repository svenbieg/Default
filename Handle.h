//==========
// Handle.h
//==========

#pragma once


//=======
// Using
//=======

#include "HandleHelper.h"


//========
// Handle
//========

template <class _obj_t>
class Handle
{
public:
	// Friends
	template <class _friend_t> friend class Handle;

	// Con-/Destructors
	Handle(): pObject(nullptr) {}
	Handle(_obj_t* Object) { HandleCreate(&pObject, Object); }
	Handle(Handle<_obj_t> const& Handle) { HandleCreate(&pObject, Handle.pObject); }
	Handle(Handle<_obj_t>&& Handle)noexcept: pObject(Handle.pObject) { Handle.pObject=nullptr; }
	template <class _convert_t> Handle(Handle<_convert_t> const& Handle) { HandleCreate(&pObject, Handle.pObject); }
	~Handle() { HandleDestroy(pObject); }

	// Access
	operator _obj_t*()const { return pObject; }
	_obj_t* operator->()const { return pObject; }
	#ifndef ESP8266
	template <class _convert_t> Handle<_convert_t> As()const { return dynamic_cast<_convert_t*>(pObject); }
	#endif

	// Comparison
	BOOL operator==(_obj_t* Object)const { return pObject==Object; }
	BOOL operator==(decltype(nullptr))const { return pObject==nullptr; }
	template <class _convert_t> BOOL operator==(Handle<_convert_t> Object)const { return pObject==(_convert_t*)Object; }
	BOOL operator!=(_obj_t* Object)const { return pObject!=Object; }
	BOOL operator!=(decltype(nullptr))const { return pObject!=nullptr; }
	template <class _convert_t> BOOL operator!=(Handle<_convert_t> Object)const { return pObject!=(_convert_t*)Object; }

	// Assignment
	Handle& operator=(_obj_t* Object) { HandleAssign(&pObject, Object); return *this; }
	Handle& operator=(Handle<_obj_t> const& Handle) { HandleAssign(&pObject, Handle.pObject); return *this; }
	template <class _convert_t> Handle& operator=(_convert_t* Object) { HandleAssign(&pObject, Object); return *this; }
	template <class _convert_t> Handle& operator=(Handle<_convert_t> const& Handle) { HandleAssign(&pObject, Handle.pObject); return *this; }

private:
	// Common
	_obj_t* pObject;
};
