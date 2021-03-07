//============
// ListItem.h
//============

#pragma once


//===========
// Namespace
//===========

namespace User {
	namespace Collections {


//======================
// Forward-Declarations
//======================

template <class _item_t> class List;
template <class _item_t> class SmallList;


//===========
// List-Item
//===========

template <class _item_t>
class ListItem
{
public:
	// Friends
	friend class List<_item_t>;
	friend class SmallList<_item_t>;

	// Common
	_item_t* GetNext() { return pNext; }
	_item_t* GetPrevious() { return pPrevious; }
	VOID SetNext(_item_t* Next) { pNext=Next; }
	VOID SetPrevious(_item_t* Previous) { pPrevious=Previous; }

protected:
	// Con-/Destructors
	ListItem(): pNext(nullptr), pPrevious(nullptr) {}
	virtual ~ListItem() {}

private:
	// Common
	_item_t* pNext;
	_item_t* pPrevious;
};

}}
