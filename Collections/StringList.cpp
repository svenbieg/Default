//================
// StringList.cpp
//================

#include "pch.h"


//=======
// Using
//=======

#include "ListHelper.h"
#include "StringList.h"


//===========
// Namespace
//===========

namespace Collections {


//==================
// Con-/Destructors
//==================

StringList::StringList()
{}


//========
// Access
//========

BOOL StringList::Contains(Handle<String> hstr)
{
for(auto hit=First(); hit->HasCurrent(); hit->MoveNext())
	{
	if(hit->GetCurrent()->Value==hstr)
		return true;
	}
return false;
}


//==============
// Modification
//==============

VOID StringList::Append(Handle<String> hstr)
{
Handle<StringListItem> hitem=new StringListItem(hstr);
List::Append(hitem);
}

VOID StringList::Remove(Handle<String> hstr)
{
if(hstr==nullptr)
	return;
for(auto hit=First(); hit->HasCurrent(); hit->MoveNext())
	{
	if(hit->GetCurrent()->Value==hstr)
		{
		hit->RemoveCurrent();
		return;
		}
	}
}

}