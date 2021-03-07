//================
// HandleHelper.h
//================

#pragma once


//==================
// Con-/Destructors
//==================

template <class _obj_t, class _convert_t> VOID HandleAssign(_obj_t** Object, _convert_t* Assign)
{
auto pobj=*Object;
_obj_t* assign=static_cast<_obj_t*>(Assign);
if(pobj==assign)
	return;
if(pobj)
	pobj->Release();
*Object=assign;
if(assign)
	assign->AddReference();
}

template <class _obj_t> VOID HandleClear(_obj_t** Object)
{
auto pobj=*Object;
if(pobj)
	{
	pobj->Release();
	*Object=nullptr;
	}
}

template <class _obj_t, class _convert_t> VOID HandleCreate(_obj_t** Object, _convert_t* Create)
{
*Object=Create;
if(Create)
	Create->AddReference();
}

template <class _obj_t> VOID HandleDestroy(_obj_t* Object)
{
if(Object)
	Object->Release();
}


//============
// Assignment
//============

template <class _obj_t> VOID HandleAssign(_obj_t** Object, _obj_t* Assign)
{
auto pobj=*Object;
if(pobj)
	pobj->Release();
*Object=Assign;
if(Assign)
	Assign->AddReference();
}
