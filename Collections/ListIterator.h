//================
// ListIterator.h
//================

#pragma once


//===========
// Namespace
//===========

namespace Collections {


//======================
// Forward-Declarations
//======================

template <class _item_t> class List;


//===============
// List-Iterator
//===============

template <class _item_t>
class ListIterator: public Object
{
private:
	// Using
	using _list_t=List<_item_t>;

public:
	// Con-/Destructors
	ListIterator(Handle<_list_t> List): hList(List) {}

	// Access
	BOOL First()
		{
		hCurrent=hList->GetFirst();
		return hCurrent!=nullptr;
		}
	Handle<_item_t> GetCurrent()const { return hCurrent; }
	BOOL HasCurrent()const { return hCurrent!=nullptr; }
	BOOL Last()
		{
		hCurrent=hList->GetLast();
		return hCurrent!=nullptr;
		}
	BOOL MoveNext()
		{
		if(!hCurrent)
			return false;
		hCurrent=hCurrent->GetNext();
		return hCurrent!=nullptr;
		}
	BOOL MovePrevious()
		{
		if(!hCurrent)
			return false;
		hCurrent=hCurrent->GetPrevious();
		return hCurrent!=nullptr;
		}

	// Modification
	BOOL RemoveCurrent()
		{
		if(!hCurrent)
			return false;
		Handle<_item_t> hitem=hCurrent;
		hCurrent=hCurrent->GetNext();
		hList->Remove(hitem);
		return true;
		}

private:
	// Common
	Handle<_item_t> hCurrent;
	Handle<_list_t> hList;
};

}
