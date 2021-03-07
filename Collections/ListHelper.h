//==============
// ListHelper.h
//==============

#pragma once


//===========
// Namespace
//===========

namespace Collections {


//==============
// Modification
//==============

template <class _item_t>
VOID ListAppend(Handle<_item_t>* First, Handle<_item_t>* Last, Handle<_item_t> Item)
{
if(!Item)
	return;
if(*First==nullptr)
	{
	*First=Item;
	*Last=Item;
	return;
	}
auto hlast=*Last;
hlast->SetNext(Item);
Item->SetPrevious(hlast);
*Last=Item;
}

template <class _item_t>
VOID ListClear(Handle<_item_t>* First, Handle<_item_t>* Last)
{
Handle<_item_t> hitem=*First;
while(hitem!=nullptr)
	{
	auto hnext=hitem->GetNext();
	hitem->SetPrevious(nullptr);
	hitem->SetNext(nullptr);
	hitem=hnext;
	}
*First=nullptr;
*Last=nullptr;
}

template <class _item_t>
BOOL ListRemove(Handle<_item_t>* First, Handle<_item_t>* Last, Handle<_item_t> Item)
{
if(Item==nullptr)
	return false;
auto hnext=Item->GetNext();
auto hprev=Item->GetPrevious();
if(hprev==nullptr)
	{
	if(hnext==nullptr)
		{
		*Last=nullptr;
		}
	else
		{
		hnext->SetPrevious(nullptr);
		}
	*First=hnext;
	}
else
	{
	if(hnext==nullptr)
		{
		*Last=hprev;
		}
	else
		{
		hnext->SetPrevious(hprev);
		}
	hprev->SetNext(hnext);
	}
Item->SetPrevious(nullptr);
Item->SetNext(nullptr);
return true;
}

}
