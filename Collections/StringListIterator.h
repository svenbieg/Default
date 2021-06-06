//======================
// StringListIterator.h
//======================

#pragma once


//=======
// Using
//=======

#include "Clusters/list.hpp"
#include "Handle.h"


//======================
// Forward-Declarations
//======================

class String;
template <> class Handle<String>;

namespace Collections
{
class StringList;
}


//===========
// Namespace
//===========

namespace Collections {


//=====================
// StringList-Iterator
//=====================

class StringListIterator: public Object
{
public:
	// Con-/Destructors
	StringListIterator(Handle<StringList> List);
	StringListIterator(Handle<StringList> List, SIZE_T Position);
	~StringListIterator();

	// Access
	Handle<String> GetCurrent()const;
	SIZE_T GetPosition()const;
	BOOL HasCurrent()const;

	// Modification
	BOOL First();
	BOOL Last();
	BOOL MoveNext();
	BOOL MovePrevious();
	BOOL RemoveCurrent();
	BOOL SetPosition(SIZE_T Position);

private:
	// Common
	typename Clusters::list<Handle<String>>::iterator cIt;
	Handle<StringList> hList;
};

}