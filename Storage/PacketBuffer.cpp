//==================
// PacketBuffer.cpp
//==================

#include "pch.h"


//=======
// Using
//=======

#include "Storage/PacketBuffer.h"


//===========
// Namespace
//===========

namespace Storage {


//==================
// Con-/Destructors
//==================

PacketBuffer::~PacketBuffer()
{
Clear();
}


//========
// Common
//========

VOID PacketBuffer::Clear()
{
m_Buffer.clear();
}


//==============
// Input-Stream
//==============

SIZE_T PacketBuffer::Available()
{
return m_Buffer.available();
}

SIZE_T PacketBuffer::Read(VOID* buf, SIZE_T size)
{
return m_Buffer.read(buf, size);
}


//===============
// Output-Stream
//===============

VOID PacketBuffer::Flush()
{
m_Buffer.flush();
}

SIZE_T PacketBuffer::Write(VOID const* buf, SIZE_T size)
{
return m_Buffer.write(buf, size);
}

}