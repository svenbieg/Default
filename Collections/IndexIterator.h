//=================
// IndexIterator.h
//=================

#pragma once


//=======
// Using
//=======

#include "Clusters/slist.hpp"


//===========
// Namespace
//===========

namespace Collections {


//======================
// Forward-Declarations
//======================

template <class _id_t, UINT _group_size> class Index;


//================
// Index-Iterator
//================

template <class _id_t, UINT _group_size>
class IndexIterator: public Object
{
private:
	// Using
	using _index_t=Index<_id_t, _group_size>;

public:
	// Con-/Destructors
	IndexIterator(Handle<_index_t> Index): cIt(&Index->cList), hIndex(Index)
		{
		hIndex->cCriticalSection.Lock();
		}
	IndexIterator(Handle<_index_t> Index, SIZE_T Position): IndexIterator(Index)
		{
		cIt.set_position(Position);
		}
	IndexIterator(Handle<_index_t> Index, SIZE_T, _id_t const& Id): IndexIterator(Index)
		{
		cIt.find(Id);
		}
	~IndexIterator()
		{
		hIndex->cCriticalSection.Unlock();
		}

	// Access
	_id_t GetCurrent()const { return cIt.get_current(); }
	SIZE_T GetPosition()const { return cIt.get_position(); }
	BOOL HasCurrent()const { return cIt.has_current(); }

	// Modification
	BOOL Find(_id_t const& Id) { return cIt.find(Id); }
	BOOL First() { return cIt.set_position(0); }
	BOOL Last()
		{
		SIZE_T ucount=hIndex->cList.get_count();
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
		_id_t id=cIt.get_current_id();
		cIt.remove_current();
		hIndex->Removed(hIndex, id);
		return true;
		}
	VOID SetPosition(SIZE_T Position) { cIt.set_position(Position); }

private:
	// Common
	Clusters::_slist_iterator<_id_t, VOID, _group_size> cIt;
	Handle<_index_t> hIndex;
};

}