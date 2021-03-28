//===============
// MapIterator.h
//===============

#pragma once


//=======
// Using
//=======

#include "Clusters/slist.hpp"
#include "ScopedLock.h"


//===========
// Namespace
//===========

namespace Collections {


//======================
// Forward-Declarations
//======================

template <class _id_t, class _item_t, UINT _group_size> class Map;


//==============
// Map-Iterator
//==============

template <class _id_t, class _item_t, UINT _group_size>
class MapIterator: public Object
{
private:
	// Using
	using _map_t=Map<_id_t, _item_t, _group_size>;

public:
	// Con-/Destructors
	MapIterator(Handle<_map_t> Map): cIt(&Map->cList), hMap(Map)
		{
		hMap->cCriticalSection.Lock();
		}
	MapIterator(Handle<_map_t> Map, SIZE_T Position): MapIterator(Map)
		{
		cIt.set_position(Position);
		}
	MapIterator(Handle<_map_t> Map, SIZE_T, _id_t const& Id): MapIterator(Map)
		{
		cIt.find(Id);
		}
	~MapIterator()
		{
		hMap->cCriticalSection.Unlock();
		}

	// Access
	_id_t GetCurrentId()const { return cIt.get_current_id(); }
	_item_t GetCurrentItem()const { return cIt.get_current_item(); }
	SIZE_T GetPosition()const { return cIt.get_position(); }
	BOOL HasCurrent()const { return cIt.has_current(); }

	// Modification
	BOOL Find(_id_t const& Id) { return cIt.find(Id); }
	BOOL First() { return cIt.set_position(0); }
	BOOL Last()
		{
		SIZE_T ucount=hMap->cList.get_count();
		if(!ucount)
			return false;
		return cIt.set_position(ucount-1);
		}
	BOOL MoveNext() { return cIt.move_next(); }
	BOOL MovePrevious() { return cIt.move_previous(); }
	BOOL RemoveCurrent() { return cIt.remove_current(); }
	VOID SetCurrentItem(_item_t const& Item) { cIt.set_current_item(Item); }
	VOID SetPosition(SIZE_T Position) { cIt.set_position(Position); }

private:
	// Common
	typename Clusters::slist<_id_t, _item_t, _group_size>::iterator cIt;
	Handle<_map_t> hMap;
};

}