//=========
// Index.h
//=========

#pragma once


//=======
// Using
//=======

#include "IndexIterator.h"


//===========
// Namespace
//===========

namespace Collections {


//=======
// Index
//=======

template <class _id_t, UINT _group_size=10>
class Index: public virtual Object
{
public:
	// Types
	typedef IndexIterator<_id_t, _group_size> Iterator;

	// Friends
	friend Iterator;

	// Con-/Destructors
	Index() {}

	// Access
	Handle<Iterator> At(SIZE_T Position) { return new Iterator(this, Position); }
	Handle<Iterator> Find(_id_t const& Id) { return new Iterator(this, 0, Id); }
	Handle<Iterator> First() { return new Iterator(this, 0); }
	_id_t GetAt(SIZE_T Position)
		{
		ScopedLock lock(cCriticalSection);
		return cList.get_at(Position);
		}
	SIZE_T GetCount()
		{
		ScopedLock lock(cCriticalSection);
		return cList.get_count();
		}
	Handle<Iterator> Last()
		{
		Handle<Iterator> hit=new Iterator(this);
		hit->Last();
		return hit;
		}

	// Modification
	BOOL Add(_id_t const& Id)
		{
			{
			ScopedLock lock(cCriticalSection);
			cList.set(Id);
			}
		Changed(this);
		return true;
		}
	Event<Index> Changed;
	BOOL Remove(_id_t const& Id)
		{
		BOOL b=false;
			{
			ScopedLock lock(cCriticalSection);
			b=cList.remove(Id);
			}
		if(b)
			{
			Changed(this);
			return true;
			}
		return false;
		}

private:
	// Common
	CriticalSection cCriticalSection;
	Clusters::slist<_id_t, VOID, _group_size> cList;
};

}