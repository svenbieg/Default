//============
// Buffer.cpp
//============

#include "pch.h"


//=======
// Using
//=======

#include "Buffer.h"


//===========
// Namespace
//===========

namespace Storage {


//==================
// Con-/Destructors
//==================

Buffer::Buffer(SIZE_T size):
m_Buffer(new BYTE[size]),
uPosition(0),
m_Size(size)
{}

Buffer::Buffer(VOID const* buf, SIZE_T size):
m_Buffer(new BYTE[size]),
uPosition(0),
m_Size(size)
{
CopyMemory(m_Buffer, buf, size);
}

Buffer::~Buffer()
{
if(m_Buffer)
	{
	delete m_Buffer;
	m_Buffer=nullptr;
	}
}


//==============
// Input-Stream
//==============

SIZE_T Buffer::Available()
{
return m_Size-uPosition;
}

SIZE_T Buffer::Read(VOID* buf, SIZE_T size)
{
SIZE_T available=m_Size-uPosition;
SIZE_T copy=Min(size, available);
if(buf)
	CopyMemory(buf, &m_Buffer[uPosition], copy);
uPosition+=copy;
return copy;
}


//===============
// Output-Stream
//===============

VOID Buffer::Flush()
{
}

SIZE_T Buffer::Write(VOID const* buf, SIZE_T size)
{
SIZE_T available=m_Size-uPosition;
SIZE_T copy=Min(size, available);
CopyMemory(&m_Buffer[uPosition], buf, copy);
uPosition+=copy;
return copy;
}


//==========
// Seekable
//==========

BOOL Buffer::Seek(FILE_SIZE pos)
{
if(pos>m_Size-1)
	return false;
uPosition=(SIZE_T)pos;
return true;
}


//==============
// Modification
//==============

SIZE_T Buffer::Fill(UINT value, SIZE_T size)
{
SIZE_T available=m_Size-uPosition;
if(size==0)
	size=available;
SIZE_T copy=Min(size, available);
FillMemory(&m_Buffer[uPosition], copy, value);
uPosition+=copy;
return copy;
}

SIZE_T Buffer::Zero(SIZE_T size)
{
SIZE_T available=m_Size-uPosition;
if(size==0)
	size=available;
SIZE_T copy=Min(size, available);
ZeroMemory(&m_Buffer[uPosition], copy);
uPosition+=copy;
return copy;
}

}
