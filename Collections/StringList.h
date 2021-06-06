//==============
// StringList.h
//==============

#pragma once


//=======
// Using
//=======

#include "StringListIterator.h"


//======================
// Forward-Declarations
//======================

class String;
template <> class Handle<String>;


//===========
// Namespace
//===========

namespace Collections {


//=============
// String-List
//=============

class StringList: public Object
{
public:
	// Friends
	friend StringListIterator;

	// Con-/Destructors
	StringList();
	template <class... _params_t> StringList(_params_t... Params): StringList()
		{
		Handle<String> pstrs[]={ Params... };
		for(UINT u=0; u<ARRAYSIZE(pstrs); u++)
			Append(pstrs[u]);
		}

	// Access
	BOOL Contains(Handle<String> String, BOOL CaseSensitive=true);
	Handle<StringListIterator> First();
	Handle<StringListIterator> Last();

	// Modification
	Event<StringList, Handle<String>> Added;
	VOID Append(Handle<String> String);
	VOID InsertAt(SIZE_T Position, Handle<String> String);
	VOID Remove(Handle<String> String, BOOL CaseSensitive=true);
	VOID RemoveAt(SIZE_T Position);
	Event<StringList, Handle<String>> Removed;

private:
	// Common
	CriticalSection cCriticalSection;
	Clusters::list<Handle<String>> cList;
};

}