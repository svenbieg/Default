//=============
// SmallList.h
//=============

#pragma once


//======================
// Forward-Declarations
//======================

namespace User
{
namespace Collections
	{
	template <class _item_t> class SmallList;
	}
}


//=======
// Using
//=======

#include "ListHelper.h"
#include "SmallListIterator.h"


//===========
// Namespace
//===========

namespace User {
	namespace Collections {


//============
// Small List
//============

template <class _item_t>
class SmallList
{
private:
	// Using
	using _it_t=SmallListIterator<_item_t>;

public:
	// Con-/Destructors
	SmallList(): pFirst(nullptr) {}
	SmallList(SmallList const& List)=delete;
	~SmallList() { Clear(); }

	// Access
	_it_t First()
		{
		_it_t it(this, pFirst);
		return it;
		}
	inline _item_t* GetFirst()const { return pFirst; }
	inline BOOL HasItems()const { return pFirst!=nullptr; }
	inline BOOL IsEmpty()const { return pFirst==nullptr; }

	// Modification
	VOID Append(_item_t* Item)
		{
		ListAppend(&pFirst, Item);
		}
	VOID Clear()
		{
		ListClear(&pFirst, (_item_t**)nullptr);
		}
	BOOL Remove(_item_t* Item)
		{
		return ListRemove(&pFirst, (_item_t**)nullptr, Item);
		}

private:
	// Common
	_item_t* pFirst;
};

}}
