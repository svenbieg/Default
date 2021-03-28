//==================
// VariableHandle.h
//==================

#pragma once


//=======
// Using
//=======

#include "Event.h"
#include "Handle.h"


//=================
// Variable Handle
//=================

template <class _owner_t, class _obj_t>
class VariableHandle
{
public:
	// Con-/Destructors
	VariableHandle(_owner_t* Owner): pObject(nullptr), pOwner(Owner) {}
	VariableHandle(_owner_t* Owner, _obj_t* Object): pOwner(Owner) { HandleCreate(&pObject, Object); }
	VariableHandle(VariableHandle const& Handle): pOwner(Handle.pOwner) { HandleCreate(&pObject, Handle.pObject); }
	VariableHandle(VariableHandle&& Handle): pObject(Handle.pObject), pOwner(Handle.pOwner) { Handle.pObject=nullptr; }

	// Access
	operator _obj_t*()const { return pObject; }
	operator Handle<_obj_t>() { return pObject; }
	_obj_t* operator->()const { return pObject; }

	// Modification
	VariableHandle& operator=(_obj_t* Object)
		{
		if(pObject==Object)
			return *this;
		HandleAssign(&pObject, Object);
		Changed(pOwner, pObject);
		return *this;
		}
	VariableHandle& operator=(VariableHandle const& Handle) { return operator=(Handle.pObject); }
	Event<_owner_t, Handle<_obj_t>> Changed;
	VOID SetInternal(Handle<_obj_t> Object) { HandleAssign(&pObject, Object); }

private:
	// Common
	_owner_t* pOwner;
	_obj_t* pObject;
};


//===============================
// Variable Handle without Owner
//===============================

template <class _obj_t>
class VariableHandle<VOID, _obj_t>
{
public:
	// Con-/Destructors
	VariableHandle(): pObject(nullptr) {}
	VariableHandle(_obj_t* Object) { HandleCreate(&pObject, Object); }
	VariableHandle(VariableHandle const& Handle) { HandleCreate(&pObject, Handle.pObject); }
	VariableHandle(VariableHandle&& Handle): pObject(Handle.pObject) { Handle.pObject=nullptr; }

	// Access
	operator _obj_t*()const { return pObject; }
	operator Handle<_obj_t>() { return pObject; }
	_obj_t* operator->()const { return pObject; }

	// Modification
	VariableHandle& operator=(_obj_t* Object)
		{
		if(pObject==Object)
			return *this;
		HandleAssign(&pObject, Object);
		Changed(pObject);
		return *this;
		}
	VariableHandle& operator=(VariableHandle const& Handle) { return operator=(Handle.pObject); }
	Event<VOID, Handle<_obj_t>> Changed;

private:
	// Common
	_obj_t* pObject;
};
