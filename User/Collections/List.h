//========
// List.h
//========

#pragma once


//======================
// Forward-Declarations
//======================

namespace User
{
namespace Collections
	{
	template <class _item_t> class List;
	}
}


//=======
// Using
//=======

#include "ListHelper.h"
#include "ListIterator.h"


//===========
// Namespace
//===========

namespace User {
	namespace Collections {


//======
// List
//======

template <class _item_t>
class List
{
private:
	// Using
	using _it_t=ListIterator<_item_t>;

public:
	// Con-/Destructors
	List(): pFirst(nullptr), pLast(nullptr), uCount(0) {}
	List(List const& List)=delete;
	~List() { Clear(); }

	// Access
	_it_t First()
		{
		_it_t it(this, pFirst);
		return it;
		}
	inline UINT GetCount() { return uCount; }
	inline _item_t* GetFirst()const { return pFirst; }
	inline _item_t* GetLast()const { return pLast; }
	inline BOOL HasItems()const { return pFirst!=nullptr; }
	inline BOOL IsEmpty()const { return pFirst==nullptr; }
	_it_t Last()
		{
		_it_t it(this, pLast);
		return it;
		}

	// Modification
	VOID Append(_item_t* Item)
		{
		ListAppend(&pFirst, &pLast, Item);
		uCount++;
		}
	VOID Clear()
		{
		ListClear(&pFirst, &pLast);
		uCount=0;
		}
	BOOL Remove(_item_t* Item)
		{
		if(ListRemove(&pFirst, &pLast, Item))
			{
			uCount--;
			return true;
			}
		return false;
		}

private:
	// Common
	_item_t* pFirst;
	_item_t* pLast;
	UINT uCount;
};

}}
