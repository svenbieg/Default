//================
// ListIterator.h
//================

#pragma once


//======================
// Forward-Declarations
//======================

namespace User
{
namespace Collections
	{
	template <class _item_t> class ListIterator;
	}
}


//=======
// Using
//=======

#include "List.h"


//===========
// Namespace
//===========

namespace User {
	namespace Collections {


//===============
// List-Iterator
//===============

template <class _item_t>
class ListIterator
{
private:
	// Using
	using _list_t=List<_item_t>;

public:
	// Con-/Destructors
	ListIterator(_list_t* List, _item_t* Current): pCurrent(Current), pList(List) {}

	// Access
	_item_t* GetCurrent()const { return pCurrent; }
	BOOL HasCurrent()const { return pCurrent!=nullptr; }

	// Modification
	_item_t* First()
		{
		pCurrent=pList->GetFirst();
		return pCurrent;
		}
	_item_t* Last()
		{
		pCurrent=pList->GetLast();
		return pCurrent;
		}
	_item_t* MoveNext()
		{
		if(!pCurrent)
			return nullptr;
		pCurrent=pCurrent->GetNext();
		return pCurrent;
		}
	_item_t* MovePrevious()
		{
		if(!pCurrent)
			return nullptr;
		pCurrent=pCurrent->GetPrevious();
		return pCurrent;
		}
	_item_t* RemoveCurrent()
		{
		if(!pCurrent)
			return nullptr;
		_item_t* pitem=pCurrent;
		pCurrent=pCurrent->GetNext();
		pList->Remove(pitem);
		return pCurrent;
		}

private:
	// Common
	_item_t* pCurrent;
	_list_t* pList;
};

}}
