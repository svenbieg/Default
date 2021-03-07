//==========
// Vector.h
//==========

#pragma once


//=======
// Using
//=======

#include "Collections/ArrayHelper.h"


//===========
// Namespace
//===========

namespace User {
	namespace Collections {


//========
// Vector
//========

template<class _item_t, UINT _block_size=1>
class Vector
{
protected:
	// Using
	using _array_helper_t=ArrayHelper<_item_t, UINT>;

public:
	// Con-/Destructors
	Vector(): pItems(nullptr), uCount(0), uSize(0) {}
	Vector(UINT Size): pItems(nullptr), uCount(0), uSize(0) { _array_helper_t::SetSize(&pItems, &uSize, &uCount, _block_size, Size); }
	Vector(_item_t const* Items, UINT Count): pItems(nullptr), uCount(0), uSize(0) { _array_helper_t::Assign(&pItems, &uSize, &uCount, _block_size, Items, Count); }
	Vector(Vector<_item_t> const& Items): pItems(nullptr), uCount(0), uSize(0) { _array_helper_t::Assign(&pItems, &uSize, &uCount, _block_size, Items.GetItems(), Items.GetCount()); }
	~Vector() { _array_helper_t::Clear(&pItems, &uSize, &uCount); }

	// Access
	inline operator BOOL() { return PointerValid(this)&&uCount>0; }
	inline _item_t& operator[](UINT Position) { return *_array_helper_t::GetAt(pItems, uCount, Position); }
	inline _item_t const& operator[](UINT Position)const { return *_array_helper_t::GetAt(pItems, uCount, Position); }
	_item_t* Begin() { return pItems; }
	_item_t const* Begin()const { return pItems; }
	inline BOOL Contains(_item_t const& Item)const { return _array_helper_t::Contains(pItems, uCount, Item); }
	inline _item_t& GetAt(UINT Position) { return *_array_helper_t::GetAt(pItems, uCount, Position); }
	inline _item_t const& GetAt(UINT Position)const { return *_array_helper_t::GetAt(pItems, uCount, Position); }
	inline UINT GetCount()const { return uCount; }
	inline _item_t& GetFirst() { return *_array_helper_t::GetFirst(pItems, uCount); }
	inline _item_t const& GetFirst()const { return *_array_helper_t::GetFirst(pItems, uCount); }
	inline _item_t* GetItems()const { return pItems; }
	inline _item_t& GetLast() { return *_array_helper_t::GetLast(pItems, uCount); }
	inline _item_t const& GetLast()const { return *_array_helper_t::GetLast(pItems, uCount); }
	inline UINT GetSize()const { return uSize; }

	// Assignment
	inline VOID Assign(_item_t const* Items, UINT Count) { _array_helper_t::Assign(&pItems, &uSize, &uCount, _block_size, Items, Count); }

	// Modification
	inline BOOL Add(_item_t const& Item) { return _array_helper_t::Add(&pItems, &uSize, &uCount, _block_size, Item); }
	inline _item_t& Append() { return *_array_helper_t::Append(&pItems, &uSize, &uCount, _block_size); }
	inline UINT Append(_item_t const& Item) { return _array_helper_t::Append(&pItems, &uSize, &uCount, _block_size, &Item, 1); }
	inline VOID Append(_item_t const* Items, UINT Count) { _array_helper_t::Append(&pItems, &uSize, &uCount, _block_size, Items, Count); }
	inline VOID Clear() { _array_helper_t::Clear(&pItems, &uSize, &uCount); }
	inline VOID InsertAt(UINT Position, _item_t const& Item) { _array_helper_t::InsertAt(&pItems, &uSize, &uCount, _block_size, Position, &Item, 1); }
	inline VOID InsertAt(UINT Position, _item_t const* Items, UINT Count) { _array_helper_t::InsertAt(&pItems, &uSize, &uCount, _block_size, Position, Items, Count); }
	inline BOOL Remove(_item_t const& Item) { return _array_helper_t::Remove(&pItems, &uSize, &uCount, _block_size, &Item); }
	inline VOID Remove(Vector<_item_t> const& Items) { _array_helper_t::Remove(&pItems, &uSize, &uCount, _block_size, Items.GetItems(), Items.GetCount()); }
	inline VOID RemoveAt(UINT Position, UINT Count=1, BOOL Shrink=true) { _array_helper_t::RemoveAt(&pItems, &uSize, &uCount, _block_size, Position, Count, false, Shrink); }
	inline VOID SetAt(UINT Position, _item_t const& Item) { _array_helper_t::SetAt(pItems, uCount, Position, Item); }
	inline VOID SetCount(UINT Count) { _array_helper_t::SetCount(&pItems, &uSize, &uCount, _block_size, Count); }
	inline VOID SetSize(UINT Size) { _array_helper_t::SetSize(&pItems, &uSize, &uCount, _block_size, Size); }
	inline VOID Zero() { ZeroMemory(pItems, uSize*sizeof(_item_t)); }

private:
	// Common
	_item_t* pItems;
	UINT uCount;
	UINT uSize;
};

}}
