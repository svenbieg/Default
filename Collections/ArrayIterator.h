//=================
// ArrayIterator.h
//=================

#pragma once


//===========
// Namespace
//===========

namespace Collections {


//======================
// Forward-Declarations
//======================

template <class _item_t> class Array;


//================
// Array-Iterator
//================

template <class _item_t>
class ArrayIterator: public Object
{
private:
	// Using
	using _array_t=Array<_item_t>;

public:
	// Con-/Destructors
	ArrayIterator(Handle<_array_t> Array, SIZE_T Position=0): hArray(Array), uPosition(Position)
		{
		hArray->cCriticalSection.Lock();
		}
	~ArrayIterator()
		{
		if(hArray)
			hArray->cCriticalSection.Unlock();
		}

	// Access
	_item_t GetCurrent()const
		{
		if(!HasCurrent())
			return nullptr;
		return hArray->pItems[uPosition];
		}
	inline BOOL HasCurrent()const { return uPosition < hArray->uCount; }
	BOOL MoveNext()
		{
		uPosition++;
		return HasCurrent();
		}
	BOOL MovePrevious()
		{
		if(uPosition==0)
			{
			uPosition=hArray->uCount;
			return false;
			}
		uPosition--;
		return true;
		}

private:
	// Common
	Handle<_array_t> hArray;
	SIZE_T uPosition;
};

}