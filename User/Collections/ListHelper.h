//==============
// ListHelper.h
//==============

#pragma once


//===========
// Namespace
//===========

namespace User {
	namespace Collections {


//==============
// Modification
//==============

template <class _item_t>
VOID ListAppend(_item_t** First, _item_t* Item)
{
if(*First==nullptr)
	{
	*First=Item;
	return;
	}
_item_t* pitem=*First;
while(1)
	{
	_item_t* pnext=pitem->GetNext();
	if(!pnext)
		break;
	pitem=pnext;
	}
pitem->SetNext(Item);
Item->SetPrevious(pitem);
}

template <class _item_t>
VOID ListAppend(_item_t** First, _item_t** Last, _item_t* Item)
{
if(*First==nullptr)
	{
	*First=Item;
	*Last=Item;
	return;
	}
_item_t* plast=*Last;
plast->SetNext(Item);
Item->SetPrevious(plast);
*Last=Item;
}

template <class _item_t>
VOID ListClear(_item_t** First, _item_t** Last)
{
_item_t* pitem=*First;
while(pitem!=nullptr)
	{
	_item_t* pnext=pitem->GetNext();
	delete pitem;
	pitem=pnext;
	}
*First=nullptr;
if(Last)
	*Last=nullptr;
}

template <class _item_t>
BOOL ListRemove(_item_t** First, _item_t** Last, _item_t* Item)
{
if(Item==nullptr)
	return false;
_item_t* pprev=Item->GetPrevious();
_item_t* pnext=Item->GetNext();
if(pprev==nullptr)
	{
	if(pnext)
		{
		pnext->SetPrevious(nullptr);
		}
	else
		{
		if(Last)
			*Last=nullptr;
		}
	*First=pnext;
	}
else
	{
	if(pnext)
		{
		pnext->SetPrevious(pprev);
		}
	else
		{
		if(Last)
			*Last=pprev;
		}
	pprev->SetNext(pnext);
	}
delete Item;
return true;
}

}}
