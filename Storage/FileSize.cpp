//==============
// FileSize.cpp
//==============

#include "pch.h"


//=======
// Using
//=======

#include "FileSize.h"


//===========
// Namespace
//===========

namespace Storage {


//==================
// Con-/Destructors
//==================

FileSize::FileSize(UINT64 usize):
uSize(usize)
{}

FileSize::FileSize(DWORD dwhi, DWORD dwlo):
uSize((((UINT64)dwhi)<<32)|dwlo)
{}


//========
// Access
//========

Handle<String> FileSize::ToString()const
{
return ToString(uSize);
}

Handle<String> FileSize::ToString(UINT64 usize)
{
if(usize>1024*1024*1024)
	return new String("%.2f GB", ((FLOAT)(usize/1024/1024))/1024.f);
if(usize>1024*1024)
	return new String("%.2f MB", ((FLOAT)(usize/1024))/1024.f);
if(usize>1024)
	return new String("%.2f KB", ((FLOAT)usize)/1024.f);
return new String("%u Bytes", (UINT)usize);
}

SIZE_T FileSize::ToSIZE_T()const
{
if(uSize>MAX_SIZE_T)
	return MAX_SIZE_T;
return (SIZE_T)uSize;
}

UINT FileSize::ToUINT()const
{
if(uSize>MAX_UINT)
	return MAX_UINT;
return (UINT)uSize;
}

}