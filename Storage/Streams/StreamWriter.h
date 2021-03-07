//================
// StreamWriter.h
//================

#pragma once


//=======
// Using
//=======

#include "Storage/Streams/OutputStream.h"
#include "StringClass.h"


//===========
// Namespace
//===========

namespace Storage {
	namespace Streams {


//===============
// Stream-Writer
//===============

class StreamWriter
{
public:
	// Con-/Destructors
	StreamWriter(Handle<OutputStream> Stream=nullptr, BOOL Unicode=false);

	// Common
	SIZE_T CompressUInt32(UINT Value);
	SIZE_T CompressUInt64(UINT64 Value);
	SIZE_T Print(LPCSTR Value) { return Print(0, Value); }
	SIZE_T Print(LPCWSTR Value) { return Print(0, Value); }
	SIZE_T Print(Handle<String> Value) { return Print(0, Value); }
	template <class _char_t, class... _args_t> SIZE_T Print(_char_t const* Format, _args_t... Arguments) { return Print(0, new String(Format, Arguments...)); }
	SIZE_T Print(UINT Length, LPCSTR Value);
	SIZE_T Print(UINT Length, LPCWSTR Value);
	SIZE_T Print(UINT Length, Handle<String> String);
	SIZE_T PrintChar(CHAR Char, UINT Count=1);
	SIZE_T PrintInt(INT Integer) { return Print(0, new String("%i", Integer)); }
	SIZE_T PrintInt64(INT64 Integer) { return Print(0, new String("%lli", Integer)); }
	SIZE_T PrintUInt(UINT Integer) { return Print(0, new String("%u", Integer)); }
	SIZE_T PrintUInt64(UINT64 Integer) { return Print(0, new String("%llu", Integer)); }
	VOID SetStream(OutputStream* Stream) { hStream=Stream; }
	SIZE_T Write(VOID const* Buffer, SIZE_T Size);
	SIZE_T WriteByte(BYTE Byte, SIZE_T Count=1);
	SIZE_T WriteChar(CHAR Char) { return Write(&Char, sizeof(CHAR)); }
	SIZE_T WriteChar(WCHAR Char) { return Write(&Char, sizeof(WCHAR)); }
	SIZE_T WriteFloat(FLOAT Float) { return Write(&Float, sizeof(FLOAT)); }
	SIZE_T WriteInt(INT Integer) { return Write(&Integer, sizeof(INT)); }
	SIZE_T WriteInt64(INT64 Integer) { return Write(&Integer, sizeof(INT64)); }
	SIZE_T WriteStream(Handle<InputStream> Stream);
	SIZE_T WriteString(LPCSTR Value) { return WriteString(0, Value); }
	SIZE_T WriteString(LPCWSTR Value) { return WriteString(0, Value); }
	SIZE_T WriteString(Handle<String> Value) { return WriteString(0, Value); }
	SIZE_T WriteString(UINT Length, LPCSTR Value);
	SIZE_T WriteString(UINT Length, LPCWSTR Value);
	SIZE_T WriteString(UINT Length, Handle<String> Value);
	SIZE_T WriteUInt(UINT Integer) { return Write(&Integer, sizeof(UINT)); }
	SIZE_T WriteUInt64(UINT64 Integer) { return Write(&Integer, sizeof(UINT64)); }
	SIZE_T WriteWord(WORD Word) { return Write(&Word, sizeof(WORD)); }

private:
	// Common
	BOOL bUnicode;
	Handle<OutputStream> hStream;
};

}}
