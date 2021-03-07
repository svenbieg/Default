//==============
// StringList.h
//==============

#pragma once


//=======
// Using
//=======

#include "List.h"
#include "StringListItem.h"


//===========
// Namespace
//===========

namespace Collections {


//=============
// String-List
//=============

class StringList: public List<StringListItem>
{
public:
	// Con-/Destructors
	StringList();
	template <class... _params_t> StringList(_params_t... Params): StringList()
		{
		Handle<String> pstrs[]={ Params... };
		for(UINT u=0; u<ARRAYSIZE(pstrs); u++)
			Append(pstrs[u]);
		}

	// Access
	BOOL Contains(Handle<String> String);

	// Modification
	VOID Append(Handle<String> String);
	VOID Remove(Handle<String> String);
};

}