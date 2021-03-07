//===========
// Aligned.h
//===========

#pragma once


//===========
// Namespace
//===========

namespace Storage {


//=========
// Aligned
//=========

template <class _obj_t, UINT _align>
class Aligned: public Object
{
public:
	// Con-/Destructors
	Aligned() { pObject=AlignedAlloc(sizeof(_obj_t), _align); }
	~Aligned() { AlignedFree(pObject); }

	// Common
	_obj_t* operator->()const { return pObject; }
	_obj_t* Get()const { return pObject; }

private:
	// Common
	_obj_t* pObject;
};

}