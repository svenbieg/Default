//================
// StringList.cpp
//================

#include "pch.h"


//=======
// Using
//=======

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

BOOL StringList::Contains(Handle<String> str, BOOL cs)
{
ScopedLock lock(cCriticalSection);
for(auto it=cList.first(); it.has_current(); it.move_next())
	{
	auto item=it.get_current();
	if(StringCompare(str->Begin(), item->Begin(), 0, cs)==0)
		return true;
	}
return false;
}

Handle<StringListIterator> StringList::First()
{
return new StringListIterator(this, 0);
}

Handle<StringListIterator> StringList::Last()
{
Handle<StringListIterator> it=new StringListIterator(this);
it->Last();
return it;
}


//==============
// Modification
//==============

VOID StringList::Append(Handle<String> str)
{
ScopedLock lock(cCriticalSection);
cList.append(str);
lock.Release();
Added(this, str);
}

VOID StringList::InsertAt(SIZE_T pos, Handle<String> str)
{
ScopedLock lock(cCriticalSection);
cList.insert_at(pos, str);
lock.Release();
Added(this, str);
}

VOID StringList::Remove(Handle<String> str, BOOL cs)
{
if(str==nullptr)
	return;
ScopedLock lock(cCriticalSection);
for(auto it=cList.first(); it.has_current(); it.move_next())
	{
	auto item=it.get_current();
	if(StringCompare(str->Begin(), item->Begin(), 0, cs)==0)
		{
		it.remove_current();
		lock.Release();
		Removed(this, item);
		return;
		}
	}
}

VOID StringList::RemoveAt(SIZE_T pos)
{
ScopedLock lock(cCriticalSection);
auto str=cList.get_at(pos);
if(!str)
	return;
cList.remove_at(pos);
lock.Release();
Removed(this, str);
}

}