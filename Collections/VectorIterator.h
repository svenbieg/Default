//==================
// VectorIterator.h
//==================

#pragma once


//===========
// Namespace
//===========

namespace Collections {


//======================
// Forward-Declarations
//======================

template <class _item_t> class Vector;


//=================
// Vector-Iterator
//=================

template <class _item_t>
class VectorIterator: public Object
{
private:
	// Using
	using _vector_t=Vector<_item_t>;

public:
	// Con-/Destructors
	VectorIterator(Handle<_vector_t> Vector, SIZE_T Position): hVector(Vector), uPosition(Position) {}

	// Access
	_item_t GetCurrent()const
		{
		if(!HasCurrent())
			return _item_t();
		return hVector->GetAt(uPosition);
		}
	inline BOOL HasCurrent()const { return uPosition<hVector->GetCount(); }
	BOOL MoveNext()
		{
		uPosition++;
		return HasCurrent();
		}
	BOOL MovePrevious()
		{
		if(uPosition==0)
			{
			uPosition=hVector->GetCount();
			return false;
			}
		uPosition--;
		return true;
		}

private:
	Handle<_vector_t> hVector;
	SIZE_T uPosition;
};

}