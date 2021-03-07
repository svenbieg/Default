//=========
// Array.h
//=========

#pragma once


//=======
// Using
//=======

#include "ArrayHelper.h"
#include "ArrayIterator.h"


//===========
// Namespace
//===========

namespace Collections {


//=======
// Array
//=======

template <class _item_t>
class Array: public virtual Object
{
private:
	// Using
	using _array_t=Array<_item_t>;
	using _array_helper_t=ArrayHelper<_item_t, SIZE_T>;
	using _array_it_t=ArrayIterator<_item_t>;

public:
	// Friends
	friend _array_it_t;

	// Types
	typedef _array_it_t Iterator;

	// Con-/Destructors
	Array(): pItems(nullptr), uCount(0) {}

	// Access
	Handle<Iterator> At(SIZE_T Position) { return new Iterator(this, Position); }
	Handle<Iterator> First() { return new Iterator(this); }
	_item_t& GetAt(SIZE_T Position)
		{
		ScopedLock lock(cCriticalSection);
		return *_array_helper_t::GetAt(pItems, uCount, Position);
		}
	_item_t const& GetAt(SIZE_T Position)const
		{
		ScopedLock lock(cCriticalSection);
		return *_array_helper_t::GetAt(pItems, uCount, Position);
		}
	SIZE_T GetCount()const
		{
		ScopedLock lock(cCriticalSection);
		return uCount;
		}
	Handle<Iterator> Last() { return new Iterator(this, GetCount()-1); }

	// Modification
	SIZE_T Append(_item_t const& Item)
		{
		ScopedLock lock(cCriticalSection);
		auto ucount=_array_helper_t::Append(&pItems, nullptr, &uCount, 1, &Item, 1);
		lock.Release();
		Changed(this);
		return ucount;
		}
	Event<_array_t> Changed;
	VOID Clear()
		{
		ScopedLock lock(cCriticalSection);
		if(!pItems)
			return;
		SIZE_T ucount=uCount;
		_array_helper_t::Clear(&pItems, nullptr, &uCount);
		if(!ucount)
			return;
		lock.Release();
		Changed(this);
		}
	SIZE_T InsertAt(SIZE_T Position, _item_t const& Item)
		{
		ScopedLock lock(cCriticalSection);
		auto ucount=_array_helper_t::InsertAt(&pItems, nullptr, &uCount, 1, Position, &Item, 1);
		lock.Release();
		Changed(this);
		return ucount;
		}
	SIZE_T RemoveAt(SIZE_T Position)
		{
		ScopedLock lock(cCriticalSection);
		if(Position>=uCount)
			return uCount;
		auto ucount=_array_helper_t::RemoveAt(&pItems, nullptr, &uCount, 1, Position);
		lock.Release();
		Changed(this);
		return ucount;
		}

private:
	// Common
	CriticalSection cCriticalSection;
	_item_t* pItems;
	SIZE_T uCount;
};

}