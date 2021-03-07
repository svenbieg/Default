//============
// Buffer.cpp
//============

#include "pch.h"


//=======
// Using
//=======

#include "Storage/BufferHelper.h"
#include "Buffer.h"


//===========
// Namespace
//===========

namespace User {
	namespace Storage {


//==================
// Con-/Destructors
//==================

Buffer::Buffer():
pBuffer(nullptr),
uSize(0)
{}

Buffer::Buffer(SIZE_T usize):
pBuffer(new BYTE[usize]),
uSize(usize)
{}

Buffer::~Buffer()
{
BufferClear(&pBuffer, &uSize);
}


//==============
// Modification
//==============

VOID Buffer::Clear()
{
BufferClear(&pBuffer, &uSize);
}

VOID Buffer::SetSize(SIZE_T usize)
{
BufferSetSize(&pBuffer, &uSize, usize);
}

VOID Buffer::Zero()
{
ZeroMemory(pBuffer, uSize);
}

}}
