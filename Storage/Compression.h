//===============
// Compression.h
//===============

#pragma once


//===========
// Namespace
//===========

namespace Storage {


//=============
// Compression
//=============

UINT Compress(VOID const* Source, UINT SourceSize, VOID* Destination, UINT DestinationSize);
UINT Compress32(UINT Value, VOID* Buffer);
UINT Compress64(UINT64 Value, VOID* Buffer);


//============
// Extraction
//============

UINT Extract(VOID const* Source, UINT SourceSize, VOID* Destination, UINT* DestinationSize);
UINT Extract32(VOID const* Buffer, UINT* Value);
UINT Extract64(VOID const* Buffer, UINT64* Value);

}
