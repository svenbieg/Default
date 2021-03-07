//===========
// Cluster.h
//===========

#pragma once


//=======
// Using
//=======

#include "ClusterIterator.h"
#include "ScopedLock.h"


//===========
// Namespace
//===========

namespace Collections {


//=========
// Cluster
//=========

template <class _item_t, UINT _group_size=10>
class Cluster: public virtual Object
{
public:
	// Types
	typedef ClusterIterator<_item_t, _group_size> Iterator;

	// Friends
	friend Iterator;

	// Con-/Destructors
	Cluster() {}

	// Access
	Handle<Iterator> At(SIZE_T Position) { return new Iterator(this, Position); }
	Handle<Iterator> First() { return new Iterator(this, 0); }
	_item_t GetAt(SIZE_T Position)
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
	Event<Cluster, _item_t> Added;
	VOID Append(_item_t const& Item)
		{
			{
			ScopedLock lock(cCriticalSection);
			cList.append(Item);
			}
		Added(this, Item);
		Changed(this);
		}
	Event<Cluster> Changed;
	VOID Clear()
		{
			{
			ScopedLock lock(cCriticalSection);
			if(!cList.get_count())
				return;
			cList.clear();
			}
		Changed(this);
		}
	VOID InsertAt(SIZE_T Position, _item_t const& Item)
		{
			{
			ScopedLock lock(cCriticalSection);
			cList.insert_at(Position, Item);
			}
		Added(this, Item);
		Changed(this);
		}
	VOID RemoveAll()
		{
		BOOL brem=false;
		for(auto hit=First(); hit->HasCurrent();)
			{
			_item_t item=hit->GetCurrent();
			hit->RemoveCurrent();
			Removed(this, item);
			brem=true;
			}
		if(brem)
			Changed(this);
		}
	BOOL RemoveAt(SIZE_T Position)
		{
		_item_t item;
		BOOL brem=false;
			{
			ScopedLock lock(cCriticalSection);
			SIZE_T ucount=cList.get_count();
			if(Position>=ucount)
				return false;
			item=cList.get_at(Position);
			cList.remove_at(Position);
			brem=true;
			}
		if(brem)
			{
			Removed(this, item);
			Changed(this);
			return true;
			}
		return false;
		}
	Event<Cluster, _item_t> Removed;
	BOOL SetAt(SIZE_T Position, _item_t const& Item)
		{
			{
			ScopedLock lock(cCriticalSection);
			SIZE_T ucount=cList.get_count();
			if(Position>=ucount)
				return false;
			cList.set_at(Position, Item);
			}
		Changed(this);
		return true;
		}

private:
	// Common
	CriticalSection cCriticalSection;
	Clusters::list<_item_t, _group_size> cList;
};

}