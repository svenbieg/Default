//================
// BufferHelper.h
//================

#pragma once


//========
// Access
//========

inline SIZE_T BufferRead(BYTE const* Buffer, SIZE_T Size, SIZE_T Position, VOID* Destination, SIZE_T Read)
{
ASSERT(Position+Read<=Size);
CopyMemory(Destination, &Buffer[Position], Read);
return Read;
}


//============
// Assignment
//============

SIZE_T BufferAssign(BYTE** Buffer, SIZE_T* Size, VOID const* Source, SIZE_T SourceSize);
VOID BufferClear(BYTE** Buffer, SIZE_T* Size);


//==============
// Modification
//==============

SIZE_T BufferAppend(BYTE** Buffer, SIZE_T* Size, VOID const* Source, SIZE_T SourceSize);
SIZE_T BufferInsert(BYTE** Buffer, SIZE_T* Size, SIZE_T Position, VOID const* Source, SIZE_T SourceSize);
SIZE_T BufferRemove(BYTE** Buffer, SIZE_T* Size, SIZE_T Position, SIZE_T Remove);
VOID BufferSetSize(BYTE** Buffer, SIZE_T* Size, SIZE_T NewSize);
SIZE_T BufferWrite(BYTE** Buffer, SIZE_T* Size, SIZE_T Position, VOID const* Source, SIZE_T SourceSize);
