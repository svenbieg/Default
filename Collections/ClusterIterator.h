//===================
// ClusterIterator.h
//===================

#pragma once


//=======
// Using
//=======

#include "Clusters/list.hpp"


//===========
// Namespace
//===========

namespace Collections {


//======================
// Forward-Declarations
//======================

template <class _item_t, UINT _group_size> class Cluster;


//==================
// Cluster-Iterator
//==================

template <class _item_t, UINT _group_size>
class ClusterIterator: public Object
{
private:
	// Using
	using _cluster_t=Cluster<_item_t, _group_size>;

public:
	// Con-/Destructors
	ClusterIterator(Handle<_cluster_t> Cluster): cIt(&Cluster->cList), hCluster(Cluster)
		{
		hCluster->cCriticalSection.Lock();
		}
	ClusterIterator(Handle<_cluster_t> Cluster, SIZE_T Position): ClusterIterator(Cluster)
		{
		cIt.set_position(Position);
		}
	~ClusterIterator()
		{
		hCluster->cCriticalSection.Unlock();
		}

	// Access
	_item_t GetCurrent()const { return cIt.get_current(); }
	SIZE_T GetPosition()const { return cIt.get_position(); }
	BOOL HasCurrent()const { return cIt.has_current(); }

	// Modification
	BOOL First() { return cIt.set_position(0); }
	BOOL Last()
		{
		SIZE_T ucount=hCluster->cList.get_count();
		if(!ucount)
			return false;
		return cIt.set_position(ucount-1);
		}
	BOOL MoveNext() { return cIt.move_next(); }
	BOOL MovePrevious() { return cIt.move_previous(); }
	BOOL RemoveCurrent()
		{
		if(!cIt.has_current())
			return false;
		_item_t item=cIt.get_current();
		cIt.remove_current();
		hCluster->Removed(hCluster, item);
		return true;
		}
	BOOL SetPosition(SIZE_T Position) { return cIt.set_position(Position); }

private:
	// Common
	typename Clusters::list<_item_t, _group_size>::iterator cIt;
	Handle<_cluster_t> hCluster;
};

}