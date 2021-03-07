//==================
// StringListItem.h
//==================

#pragma once


//=======
// Using
//=======

#include "ListItem.h"
#include "StringClass.h"


//===========
// Namespace
//===========

namespace Collections {


//======================
// Forward-Declarations
//======================

class StringList;


//==================
// Item String-List
//==================

class StringListItem: public ListItem<StringListItem>
{
public:
	// Con-/Destructors
	StringListItem(Handle<String> Value=nullptr): Value(Value) {}

	// Comparison
	BOOL operator==(StringListItem const& Item) { return Value==Item.Value; }
	BOOL operator!=(StringListItem const& Item) { return Value!=Item.Value; }

	// Common
	Handle<String> Value;
};

}