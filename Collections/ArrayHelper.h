//===============
// ArrayHelper.h
//===============

#pragma once


//=======
// Using
//=======

#include <new>
#include <utility>
#include "MemoryHelper.h"


//==============
// Array-Helper
//==============

template <class _item_t, class _size_t>
class ArrayHelper
{
public:
	// Access
	template <class _param_t> static BOOL Contains(_item_t const* Items, _size_t Count, _param_t Item)
		{
		for(_size_t u=0; u<Count; u++)
			{
			if(Items[u]==Item)
				return true;
			}
		return false;
		}
	static inline _item_t* GetAt(_item_t* Items, _size_t Count, _size_t Position)
		{
		ASSERT(Position<Count);
		return &Items[Position];
		}
	static inline _item_t const* GetAt(_item_t const* Items, _size_t Count, _size_t Position)
		{
		ASSERT(Position<Count);
		return &Items[Position];
		}
	static inline _item_t* GetFirst(_item_t* Items, _size_t Count)
		{
		ASSERT(Count>0);
		return Items;
		}
	static inline _item_t const* GetFirst(_item_t const* Items, _size_t Count)
		{
		ASSERT(Count>0);
		return Items;
		}
	static inline _item_t* GetLast(_item_t* Items, _size_t Count)
		{
		ASSERT(Count>0);
		return &Items[Count-1];
		}
	static inline _item_t const* GetLast(_item_t const* Items, _size_t Count)
		{
		ASSERT(Count>0);
		return &Items[Count-1];
		}
	template <class _param_t> static BOOL GetPosition(_item_t const* Items, _size_t Count, _param_t Item, _size_t* Position)
		{
		for(_size_t u=0; u<Count; u++)
			{
			if(Items[u]==Item)
				{
				*Position=u;
				return true;
				}
			}
		return false;
		}

	// Assignment
	static inline VOID InitItem(_item_t* Item) { new (Item) _item_t(); }
	static VOID InitItems(_item_t* Items, _size_t Count)
		{
		for(_size_t u=0; u<Count; u++)
			new (&Items[u]) _item_t();
		}

	// Modification
	static BOOL Add(_item_t** Items, _size_t* Size, _size_t* Count, UINT BlockSize, _item_t const& Item)
		{
		_item_t* pitems=*Items;
		_size_t ucount=*Count;
		for(_size_t u=0; u<ucount; u++)
			{
			if(pitems[u]==Item)
				return false;
			}
		_size_t unewcount=ucount+1;
		if(unewcount>*Size)
			{
			SetSize(Items, Size, Count, BlockSize, unewcount);
			pitems=*Items;
			}
		new (&pitems[ucount]) _item_t(Item);
		*Count=unewcount;
		return true;
		}
	static _item_t* Append(_item_t* Items, _size_t Size, _size_t* Count)
		{
		UINT ucount=*Count;
		if(ucount==Size)
			return nullptr;
		_item_t* pitem=&Items[ucount];
		*Count=ucount+1;
		return pitem;
		}
	static VOID Append(_item_t* Items, _size_t Size, _size_t* Count, _item_t const& Item)
		{
		ASSERT(*Count<Size);
		Items[*Count]=Item;
		Count[0]++;
		}
	static _item_t* Append(_item_t** Items, _size_t* Size, _size_t* Count, UINT BlockSize)
		{
		_size_t ucount=*Count;
		_size_t unewcount=ucount+1;
		if(unewcount>*Size)
			SetSize(Items, Size, Count, BlockSize, unewcount);
		_item_t* pitems=*Items;
		*Count=unewcount;
		return &pitems[ucount];
		}
	static _size_t Append(_item_t* Items, _size_t Size, _size_t* Count, _item_t const* Insert, _size_t InsertCount, BOOL Moving=false)
		{
		_size_t ucount=*Count;
		_size_t unewcount=ucount+InsertCount;
		if(unewcount>Size)
			{
			ASSERT(false);
			return ucount;
			}
		if(Moving)
			{
			MoveItems(&Items[ucount], Insert, InsertCount);
			}
		else
			{
			OverWriteItems(&Items[ucount], Insert, InsertCount);
			}
		*Count=unewcount;
		return unewcount;
		}
	static _size_t Append(_item_t** Items, _size_t* Size, _size_t* Count, UINT BlockSize, _item_t const* NewItems, _size_t InsertCount, BOOL Moving=false)
		{
		ASSERT(Items&&Count&&BlockSize&&NewItems&&InsertCount);
		_size_t ucount=*Count;
		_size_t usize=ucount;
		if(Size)
			usize=*Size;
		_size_t unewcount=ucount+InsertCount;
		if(unewcount>usize)
			SetSize(Items, Size, Count, BlockSize, unewcount);
		_item_t* pitems=*Items;
		if(Moving)
			{
			MoveItems(&pitems[ucount], NewItems, InsertCount);
			}
		else
			{
			OverWriteItems(&pitems[ucount], NewItems, InsertCount);
			}
		*Count=unewcount;
		return unewcount;
		}
	static _size_t Assign(_item_t** Items, _size_t* Size, _size_t* Count, UINT BlockSize, _item_t const* NewItems, _size_t NewCount, BOOL Moving=false)
		{
		_item_t* pitems=*Items;
		DestroyItems(pitems, *Count);
		*Count=0;
		SetSize(Items, Size, Count, BlockSize, NewCount);
		if(Moving)
			{
			MoveItems(pitems, NewItems, NewCount);
			}
		else
			{
			OverWriteItems(pitems, NewItems, NewCount);
			}
		*Count=NewCount;
		return NewCount;
		}
	static VOID Clear(_item_t** Items, _size_t* Size, _size_t* Count)
		{
		ASSERT(Items&&Count);
		DestroyItems(*Items, *Count);
		operator delete(*Items);
		*Items=nullptr;
		if(Size)
			*Size=0;
		*Count=0;
		}
	static inline VOID DestroyItem(_item_t* Item) { *Item.~_item_t(); }
	static VOID DestroyItems(_item_t* Items, _size_t Count)
		{
		for(_size_t u=0; u<Count; u++)
			Items[u].~_item_t();
		}
	static _item_t* InsertAt(_item_t* Items, _size_t Size, _size_t* Count, _size_t Position)
		{
		_size_t ucount=*Count;
		if(ucount==Size||Position>ucount)
			return nullptr;
		if(Position<ucount)
			MoveItems(&Items[Position+1], &Items[Position], ucount-Position);
		*Count=ucount+1;
		return &Items[Position];
		}
	static _item_t* InsertAt(_item_t** Items, _size_t* Size, _size_t* Count, UINT BlockSize, _size_t Position)
		{
		_size_t ucount=*Count;
		if(Position>ucount)
			return nullptr;
		_size_t unewcount=ucount+1;
		if(unewcount>*Size)
			SetSize(Items, Size, Count, BlockSize, unewcount);
		_item_t* pitems=*Items;
		if(Position<ucount)
			MoveItems(&pitems[Position+1], &pitems[Position], ucount-Position);
		*Count=unewcount;
		return &pitems[Position];
		}
	static _size_t InsertAt(_item_t* Items, _size_t Size, _size_t* Count, _size_t Position, _item_t const* Insert, _size_t InsertCount, BOOL Moving=false)
		{
		_size_t ucount=*Count;
		_size_t unewcount=ucount+InsertCount;
		if(Position>ucount||unewcount>Size)
			{
			ASSERT(false);
			return ucount;
			}
		if(Position<ucount)
			MoveItems(&Items[Position+InsertCount], &Items[Position], ucount-Position);
		if(Moving)
			{
			MoveItems(&Items[Position], Insert, InsertCount);
			}
		else
			{
			OverWriteItems(&Items[Position], Insert, InsertCount);
			}
		*Count=unewcount;
		return unewcount;
		}
	static _size_t InsertAt(_item_t** Items, _size_t* Size, _size_t* Count, UINT BlockSize, _size_t Position, _item_t const* NewItems, _size_t NewCount, BOOL Moving=false)
		{
		_size_t ucount=*Count;
		if(Position>ucount)
			{
			ASSERT(false);
			return ucount;
			}
		_size_t unewcount=ucount+NewCount;
		if(unewcount>*Size)
			SetSize(Items, Size, Count, BlockSize, unewcount);
		_item_t* pitems=*Items;
		MoveItems(&pitems[Position+NewCount], &pitems[Position], ucount-Position);
		if(Moving)
			{
			MoveItems(&pitems[Position], NewItems, NewCount);
			}
		else
			{
			OverWriteItems(&pitems[Position], NewItems, NewCount);
			}
		*Count=unewcount;
		return unewcount;
		}
	static inline VOID MoveItems(_item_t* Destination, _item_t const* Source, _size_t Count)
		{
		if(Destination>Source)
			{
			for(_size_t u=0; u<Count; u++)
				new (&Destination[Count-u-1]) _item_t(std::move(Source[Count-u-1]));
			}
		else if(Destination<Source)
			{
			for(_size_t u=0; u<Count; u++)
				new (&Destination[u]) _item_t(std::move(Source[u]));
			}
		}
	static VOID OverWriteItems(_item_t* Destination, _item_t const* Source, _size_t Count)
		{
		for(_size_t u=0; u<Count; u++)
			new (&Destination[u]) _item_t(Source[u]);
		}
	static BOOL Remove(_item_t** Items, _size_t* Size, _size_t* Count, UINT BlockSize, _item_t const* Remove)
		{
		_item_t* pitems=*Items;
		_size_t ucount=*Count;
		for(_size_t u=0; u<ucount; u++)
			{
			if(pitems[u]==*Remove)
				{
				RemoveAt(Items, Size, Count, u, 1, BlockSize, false);
				return true;
				}
			}
		return false;
		}
	static _size_t Remove(_item_t** Items, _size_t* Size, _size_t* Count, UINT BlockSize, _item_t const* Remove, _size_t RemoveCount)
		{
		_item_t* pitems=*Items;
		_size_t ucount=*Count;
		for(_size_t uitem=0; uitem<RemoveCount; uitem++)
			{
			for(_size_t u=0; u<ucount; )
				{
				if(pitems[u]==Remove[uitem])
					{
					RemoveAt(Items, Size, Count, u, 1, BlockSize, false);
					ucount--;
					}
				else
					{
					u++;
					}
				}
			}
		Shrink(Items, Size, *Count, BlockSize);
		return ucount;
		}
	static _size_t RemoveAt(_item_t* Items, _size_t* Count, _size_t Position, _size_t RemoveCount=1, BOOL Moving=false)
		{
		_size_t ucount=*Count;
		if(Position+RemoveCount>ucount)
			{
			ASSERT(false);
			return ucount;
			}
		if(!Moving)
			DestroyItems(&Items[Position], RemoveCount);
		MoveItems(&Items[Position], &Items[Position+RemoveCount], ucount-Position-RemoveCount);
		ucount-=RemoveCount;
		*Count=ucount;
		return ucount;
		}
	static _size_t RemoveAt(_item_t** Items, _size_t* Size, _size_t* Count, UINT BlockSize, _size_t Position, _size_t RemoveCount=1, BOOL Moving=false, BOOL DoShrink=true)
		{
		_size_t ucount=*Count;
		if(Position+RemoveCount>ucount)
			{
			ASSERT(false);
			return ucount;
			}
		_item_t* pitems=*Items;
		if(!Moving)
			DestroyItems(&pitems[Position], RemoveCount);
		MoveItems(&pitems[Position], &pitems[Position+RemoveCount], ucount-Position-RemoveCount);
		ucount-=RemoveCount;
		*Count=ucount;
		if(DoShrink)
			Shrink(Items, Size, *Count, BlockSize);
		return ucount;
		}
	static inline VOID SetAt(_item_t* Items, _size_t Count, _size_t Position, _item_t const& Set)
		{
		ASSERT(Position<Count);
		Items[Position]=Set;
		}
	static VOID SetAt(_item_t** Items, _size_t* Size, _size_t* Count, UINT BlockSize, _size_t Position, _item_t const& Set)
		{
		if(Position>=*Size)
			SetSize(Items, Size, Count, BlockSize, Position+1);
		Items[0][Position]=Set;
		}
	static VOID SetCount(_item_t** Items, _size_t* Size, _size_t* Count, UINT BlockSize, _size_t NewCount)
		{
		ASSERT(Items&&Count&&BlockSize);
		if(!NewCount)
			{
			Clear(Items, Size, Count);
			return;
			}
		_size_t ucount=*Count;
		if(NewCount==ucount)
			return;
		_size_t usize=ucount;
		if(Size)
			usize=*Size;
		_item_t* pitems=*Items;
		if(ucount>NewCount)
			DestroyItems(&pitems[NewCount], ucount-NewCount);
		_size_t unewsize=BlockAlign<_size_t>(NewCount, BlockSize);
		if(unewsize!=usize)
			{
			_item_t* pold=pitems;
			pitems=(_item_t*)operator new(unewsize*sizeof(_item_t));
			if(pold)
				{
				_size_t ucopy=MIN(ucount, NewCount);
				MoveItems(pitems, pold, ucopy);
				operator delete(pold);
				}
			*Items=pitems;
			if(Size)
				*Size=unewsize;
			}
		if(NewCount>ucount)
			InitItems(&pitems[ucount], NewCount-ucount);
		*Count=NewCount;
		}
	static inline VOID SetItem(_item_t* Item, _item_t const& NewItem) { *Item=NewItem; }
	static VOID SetSize(_item_t** Items, _size_t* Size, _size_t* Count, UINT BlockSize, _size_t NewSize)
		{
		ASSERT(Items&&Count&&BlockSize);
		if(!NewSize)
			{
			Clear(Items, Size, Count);
			return;
			}
		_size_t ucount=*Count;
		_size_t usize=ucount;
		if(Size)
			usize=*Size;
		_size_t unewsize=BlockAlign<_size_t>(NewSize, BlockSize);
		if(unewsize==usize)
			return;
		_item_t* pitems=*Items;
		_size_t unewcount=MIN(unewsize, ucount);
		if(unewcount<ucount)
			DestroyItems(&pitems[unewcount], ucount-unewcount);
		*Items=(_item_t*)operator new(unewsize*sizeof(_item_t));
		if(pitems)
			{
			_size_t ucopy=MIN(ucount, unewcount);
			MoveItems(*Items, pitems, ucopy);
			operator delete(pitems);
			}
		if(Size)
			*Size=unewsize;
		*Count=unewcount;
		}
	static VOID Shrink(_item_t** Items, _size_t* Size, _size_t Count, UINT BlockSize)
		{
		ASSERT(Items&&BlockSize);
		_size_t usize=Count;
		if(Size)
			usize=*Size;
		_size_t unewsize=BlockAlign(Count, BlockSize);
		if(unewsize==usize)
			return;
		_item_t* pitems=(_item_t*)operator new(unewsize*sizeof(_item_t));
		MoveItems(pitems, *Items, Count);
		operator delete(*Items);
		*Items=pitems;
		if(Size)
			*Size=unewsize;
		}
};
