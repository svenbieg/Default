//========================
// StringListIterator.cpp
//========================

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

StringListIterator::StringListIterator(Handle<StringList> list):
cIt(&list->cList),
hList(list)
{
hList->cCriticalSection.Lock();
}

StringListIterator::StringListIterator(Handle<StringList> list, SIZE_T pos):
StringListIterator(list)
{
cIt.set_position(pos);
}

StringListIterator::~StringListIterator()
{
hList->cCriticalSection.Unlock();
}


//========
// Access
//========

Handle<String> StringListIterator::GetCurrent()const
{
return cIt.get_current();
}

SIZE_T StringListIterator::GetPosition()const
{
return cIt.get_position();
}

BOOL StringListIterator::HasCurrent()const
{
return cIt.has_current();
}


//==============
// Modification
//==============

BOOL StringListIterator::First()
{
return cIt.set_position(0);
}

BOOL StringListIterator::Last()
{
SIZE_T ucount=hList->cList.get_count();
if(!ucount)
	return false;
return cIt.set_position(ucount-1);
}

BOOL StringListIterator::MoveNext()
{
return cIt.move_next();
}

BOOL StringListIterator::MovePrevious()
{
return cIt.move_previous();
}

BOOL StringListIterator::RemoveCurrent()
{
if(!cIt.has_current())
	return false;
auto str=cIt.get_current();
cIt.remove_current();
hList->Removed(hList, str);
return true;
}

BOOL StringListIterator::SetPosition(SIZE_T pos)
{
return cIt.set_position(pos);
}

}