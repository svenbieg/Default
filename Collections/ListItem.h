//============
// ListItem.h
//============

#pragma once


//===========
// Namespace
//===========

namespace Collections {


//===========
// List-Item
//===========

template <class _item_t>
class ListItem: public virtual Object
{
public:
	// Access
	Handle<_item_t> GetNext() { return hNext; }
	Handle<_item_t> GetPrevious() { return hPrevious; }

	// Modification
	VOID SetNext(Handle<_item_t> Next) { hNext=Next; }
	VOID SetPrevious(Handle<_item_t> Previous) { hPrevious=Previous; }

protected:
	// Con-/Destructors
	ListItem() {}
	virtual ~ListItem() {}

private:
	// Common
	Handle<_item_t> hNext;
	Handle<_item_t> hPrevious;
};

}
