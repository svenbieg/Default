//================
// PacketBuffer.h
//================

#pragma once


//=======
// Using
//=======

#include "Storage/Streams/RandomAccessStream.h"
#include "Storage/pbuf.hpp"


//===========
// Namespace
//===========

namespace Storage {


//===============
// Packet-Buffer
//===============

class PacketBuffer: public Streams::RandomAccessStream
{
public:
	// Con-/Destructors
	~PacketBuffer();
	static inline Handle<PacketBuffer> Create() { return new PacketBuffer(); }

	// Common
	VOID Clear();

	// Input-Stream
	SIZE_T Available()override;
	SIZE_T Read(VOID* Buffer, SIZE_T Size)override;

	// Output-Stream
	VOID Flush()override;
	SIZE_T Write(VOID const* Buffer, SIZE_T Size)override;

private:
	// Con-/Destructors
	PacketBuffer() {}

	// Common
	pbuf<PAGE_SIZE> m_Buffer;
};

}