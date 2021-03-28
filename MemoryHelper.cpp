//==================
// MemoryHelper.cpp
//==================

#include "pch.h"


//=======
// Using
//=======

#include <string.h>


//========
// Common
//========

INT CompareMemory(const VOID* pbuf1, const VOID* pbuf2, SIZE_T usize)
{
return memcmp(pbuf1, pbuf2, usize);
}

VOID CopyMemory(VOID* pdst, const VOID* psrc, SIZE_T usize)
{
memcpy(pdst, psrc, usize);
}

VOID FillMemory(VOID* pdst, SIZE_T size, UINT value)
{
memset(pdst, value, size);
}

VOID MoveMemory(VOID* pdst, const VOID* psrc, SIZE_T usize)
{
memmove(pdst, psrc, usize);
}

VOID SetMemory(VOID* pdst, INT Value, SIZE_T usize)
{
memset(pdst, Value, usize);
}

VOID ZeroMemory(VOID* pdst, SIZE_T usize)
{
memset(pdst, 0, usize);
}
