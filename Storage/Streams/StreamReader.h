//================
// StreamReader.h
//================

#pragma once


//=======
// Using
//=======

#include "Storage/Streams/InputStream.h"


//===========
// Namespace
//===========

namespace Storage {
	namespace Streams {


//===============
// Stream-Reader
//===============

class StreamReader
{
public:
	// Con-/Destructors
	StreamReader(Handle<InputStream> Stream, BOOL Unicode=false);

	// Access
	SIZE_T Available();
	SIZE_T ExtractUInt32(UINT* Value);
	SIZE_T ExtractUInt64(UINT64* Value);
	SIZE_T GoTo(TCHAR Char);
	SIZE_T Read(VOID* Buffer, SIZE_T Size);
	BYTE ReadByte();
	SIZE_T ReadByte(BYTE* Value) { return Read(&Value, sizeof(BYTE)); }
	TCHAR ReadChar();
	FLOAT ReadFloat();
	SIZE_T ReadFloat(FLOAT* Value) { return Read(&Value, sizeof(FLOAT)); }
	INT ReadInt();
	SIZE_T ReadInt(INT* Value) { return Read(&Value, sizeof(INT)); }
	Handle<String> ReadString(TCHAR Stop=0, SIZE_T* Size=nullptr);
	UINT ReadString(LPTSTR Buffer, UINT Size, TCHAR Stop=0);
	UINT ReadUInt();
	UINT64 ReadUInt64();
	SIZE_T ReadUInt(UINT* Value);
	SIZE_T ReadUInt64(UINT64* Value);
	WORD ReadWord();
	SIZE_T ReadWord(WORD* Value) { return Read(&Value, sizeof(WORD)); }
	SIZE_T Skip();
	SIZE_T Skip(SIZE_T Size);
	SIZE_T SkipChar();
	SIZE_T SkipChars(UINT Count);

private:
	// Common
	BOOL bUnicode;
	Handle<InputStream> hStream;
};

}}
