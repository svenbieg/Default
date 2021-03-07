//==================
// Intermediate.cpp
//==================

#include "pch.h"


//=======
// Using
//=======

#include "Storage/Streams/MemoryStream.h"
#include "Intermediate.h"

using namespace Storage::Streams;


//===========
// Namespace
//===========

namespace Storage {


//==================
// Con-/Destructors
//==================

Intermediate::Intermediate():
uPosition(0)
{}


//========
// Access
//========

SIZE_T Intermediate::Available()
{
return cList.get_count()-uPosition;
}

FileSize Intermediate::GetSize()
{
return cList.get_count();
}

SIZE_T Intermediate::Read(VOID* pbuf, SIZE_T usize)
{
SIZE_T ucopy=MIN(usize, cList.get_count()-uPosition);
if(!ucopy||!pbuf)
	return ucopy;
return cList.get_many(uPosition, ucopy, (BYTE*)pbuf);
}

BOOL Intermediate::Seek(UINT64 upos)
{
if(upos>=cList.get_count())
	return false;
uPosition=(SIZE_T)upos;
return true;
}


//==============
// Modification
//==============

VOID Intermediate::Flush()
{
uPosition=0;
}

SIZE_T Intermediate::Write(VOID const* pbufv, SIZE_T usize)
{
SIZE_T uwritten=cList.set_many(uPosition, usize, (BYTE const*)pbufv);
uPosition+=uwritten;
return uwritten;
}

}