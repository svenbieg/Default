//===========
// Pointer.h
//===========

#pragma once


//===========
// Namespace
//===========

namespace User {


//=========
// Pointer
//=========

template <class _item_t>
class Pointer
{
public:
	// Con-/Destructors
	Pointer(): pItem(nullptr) {}
	Pointer(_item_t* Item): pItem(Item) {}
	Pointer(Pointer<_item_t> const& Pointer): pItem(Pointer.pItem) {}
	Pointer(Pointer<_item_t>&& Pointer): pItem(Pointer.pItem) { Pointer.pItem=nullptr; }
	~Pointer()
		{
		if(pItem)
			delete pItem;
		}

	// Access
	inline operator BOOL()const { return pItem!=nullptr; }
	inline operator _item_t*()const { return pItem; }
	inline BOOL operator==(_item_t* Item) { return pItem==Item; }
	inline BOOL operator==(const Pointer<_item_t>& Pointer) { return pItem==Pointer.pItem; }
	inline _item_t* operator->()const { return pItem; }
	inline _item_t* Get()const { return pItem; }

	// Assignment
	Pointer& operator=(_item_t* Item)
		{
		if(pItem)
			delete pItem;
		pItem=Item;
		return *this;
		}

private:
	_item_t* pItem;
};

}
