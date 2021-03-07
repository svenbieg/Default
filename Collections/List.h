//========
// List.h
//========

#pragma once


//=======
// Using
//=======

#include "ListHelper.h"
#include "ListItem.h"
#include "ListIterator.h"


//===========
// Namespace
//===========

namespace Collections {


//======
// List
//======

template <class _item_t>
class List: public virtual Object
{
public:
	// Using
	using Iterator=ListIterator<_item_t>;

	// Con-/Destructors
	List(): uLength(0) {}
	~List() { Clear(); }

	// Access
	Handle<Iterator> First()
		{
		Handle<Iterator> hit=new Iterator(this);
		hit->First();
		return hit;
		}
	Handle<_item_t> GetFirst()
		{
		ScopedLock lock(cCriticalSection);
		return hFirst;
		}
	Handle<_item_t> GetLast()
		{
		ScopedLock lock(cCriticalSection);
		return hLast;
		}
	UINT GetLength()
		{
		ScopedLock lock(cCriticalSection);
		return uLength;
		}
	BOOL HasItems()
		{
		ScopedLock lock(cCriticalSection);
		return hFirst!=nullptr;
		}
	BOOL IsEmpty()
		{
		ScopedLock lock(cCriticalSection);
		return hFirst==nullptr;
		}
	Handle<Iterator> Last()
		{
		Handle<Iterator> hit=new Iterator(this);
		hit->Last();
		return hit;
		}

	// Modification
	VOID Append(Handle<_item_t> Item)
		{
		ScopedLock lock(cCriticalSection);
		ListAppend<_item_t>(&hFirst, &hLast, Item);
		uLength++;
		}
	virtual VOID Clear()
		{
		ScopedLock lock(cCriticalSection);
		ListClear<_item_t>(&hFirst, &hLast);
		uLength=0;
		}
	BOOL Remove(Handle<_item_t> Item)
		{
		ScopedLock lock(cCriticalSection);
		if(ListRemove(&hFirst, &hLast, Item))
			{
			uLength--;
			return true;
			}
		return false;
		}

protected:
	// Common
	CriticalSection cCriticalSection;
	Handle<_item_t> hFirst;
	Handle<_item_t> hLast;
	UINT uLength;
};

}
