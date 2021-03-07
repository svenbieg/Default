//=======
// Map.h
//=======

#pragma once


//=======
// Using
//=======

#include "MapIterator.h"


//===========
// Namespace
//===========

namespace Collections {


//=====
// Map
//=====

template <class _id_t, class _item_t=VOID, UINT _group_size=10>
class Map: public virtual Object
{
public:
	// Types
	typedef MapIterator<_id_t, _item_t, _group_size> Iterator;

	// Friends
	friend Iterator;

	// Con-/Destructors
	Map() {}

	// Access
	BOOL Contains(_id_t const& Id)
		{
		ScopedLock lock(cCriticalSection);
		return cList.contains(Id);
		}
	Handle<Iterator> Find(_id_t const& Id) { return new Iterator(this, 0, Id); }
	Handle<Iterator> First() { return new Iterator(this, 0); }
	_item_t Get(_id_t const& Id)
		{
		ScopedLock lock(cCriticalSection);
		return cList.get(Id);
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
	BOOL TryGet(_id_t const& Id, _item_t* Item)
		{
		ScopedLock lock(cCriticalSection);
		return cList.try_get(Id, Item);
		}

	// Modification
	BOOL Add(_id_t const& Id, _item_t const& Item)
		{
		BOOL badded=false;
			{
			ScopedLock lock(cCriticalSection);
			badded=cList.add(Id, Item);
			}
		if(badded)
			{
			Added(this, Id, Item);
			Changed(this);
			return true;
			}
		return false;
		}
	Event<Map, _id_t, _item_t> Added;
	Event<Map> Changed;
	VOID Clear()
		{
			{
			ScopedLock lock(cCriticalSection);
			if(cList.get_count()==0)
				return;
			cList.clear();
			}
		Changed(this);
		}
	BOOL Remove(_id_t const& Id)
		{
		BOOL bremoved=false;
			{
			ScopedLock lock(cCriticalSection);
			bremoved=cList.remove(Id);
			}
		if(bremoved)
			{
			Removed(this);
			Changed(this);
			return true;
			}
		return false;
		}
	BOOL RemoveAt(UINT64 Position)
		{
		BOOL bremoved=false;
			{
			ScopedLock lock(cCriticalSection);
			bremoved=cList.remove_at(Position);
			}
		if(bremoved)
			{
			Removed(this);
			Changed(this);
			return true;
			}
		return false;
		}
	Event<Map> Removed;
	VOID Set(_id_t const& Id, _item_t const& Item)
		{
			{
			ScopedLock lock(cCriticalSection);
			cList.set(Id, Item);
			}
		Changed(this);
		}

private:
	// Common
	CriticalSection cCriticalSection;
	Clusters::slist<_id_t, _item_t, _group_size> cList;
};

}