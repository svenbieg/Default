//==================
// StreamWriter.cpp
//==================

#include "pch.h"


//=======
// Using
//=======

#include "CharHelper.h"
#include "StreamWriter.h"


//===========
// Namespace
//===========

namespace Storage {
	namespace Streams {


//==================
// Con-/Destructors
//==================

StreamWriter::StreamWriter(OutputStream* stream):
pStream(nullptr),
pWriteAnsi(nullptr),
pWriteUnicode(nullptr)
{
SetStream(stream);
}


//========
// Common
//========

UINT StreamWriter::Print(LPCSTR value)
{
return DoPrint(pWriteAnsi, 0, value);
}

UINT StreamWriter::Print(LPCSTR value, StringFormatFlags flags, UINT width)
{
return DoPrint(value, flags, width);
}

UINT StreamWriter::Print(LPCWSTR value)
{
return DoPrint(pWriteUnicode, 0, value);
}

UINT StreamWriter::Print(LPCWSTR value, StringFormatFlags flags, UINT width)
{
return DoPrint(value, flags, width);
}

UINT StreamWriter::Print(UINT len, LPCSTR value)
{
return DoPrint(pWriteAnsi, len, value);
}

UINT StreamWriter::Print(UINT len, LPCWSTR value)
{
return DoPrint(pWriteUnicode, len, value);
}

UINT StreamWriter::Print(Handle<String> value)
{
if(!value)
	return 0;
return Print(0, value->Begin());
}

UINT StreamWriter::Print(LPCSTR str, VariableArguments const& args)
{
UINT written=0;
UINT pos=0;
UINT arg=0;
while(str[pos])
	{
	StringFormat format=StringFormat::None;
	StringFormatFlags flags=StringFormatFlags::None;
	UINT width=0;
	UINT prec=0;
	pos+=StringGetFormat(&str[pos], format, flags, width, prec);
	if(format==StringFormat::None)
		{
		written+=PrintChar(str[pos++]);
		continue;
		}
	if(format==StringFormat::Percent)
		{
		written+=PrintChar('%');
		continue;
		}
	if(GetFlag(flags, StringFormatFlags::Width))
		{
		if(!args.GetAt(arg++, width))
			return written;
		}
	if(GetFlag(flags, StringFormatFlags::Precision))
		{
		if(!args.GetAt(arg++, prec))
			return written;
		}
	switch(format)
		{
		case StringFormat::Int:
			{
			INT64 i=0;
			if(!args.GetAt(arg++, i))
				return written;
			written+=PrintInt64(i, flags, width);
			continue;
			}
		case StringFormat::UInt:
			{
			UINT64 u=0;
			if(!args.GetAt(arg++, u))
				return written;
			written+=PrintUInt64(u, flags, width);
			continue;
			}
		case StringFormat::Hex:
			{
			UINT64 u=0;
			if(!args.GetAt(arg++, u))
				return written;
			written+=PrintHex(u, flags, width);
			continue;
			}
		case StringFormat::Float:
			{
			FLOAT f=0;
			if(!args.GetAt(arg++, f))
				return written;
			written+=PrintFloat(f, flags, width, prec);
			continue;
			}
		case StringFormat::Double:
			{
			DOUBLE d=0;
			if(!args.GetAt(arg++, d))
				return written;
			written+=PrintDouble(d, flags, width, prec);
			continue;
			}
		case StringFormat::Char:
			{
			WCHAR c=0;
			if(!args.GetAt(arg++, c))
				return written;
			written+=PrintChar(c);
			continue;
			}
		case StringFormat::String:
			{
			LPCSTR p=nullptr;
			if(args.GetAt(arg, p))
				{
				arg++;
				written+=DoPrint(p, flags, width);
				continue;
				}
			LPCWSTR pw=nullptr;
			if(args.GetAt(arg, pw))
				{
				arg++;
				written+=DoPrint(pw, flags, width);
				continue;
				}
			return written;
			}
		default:
			return written;
		}
	}
return written;
}

UINT StreamWriter::PrintChar(CHAR c, UINT count)
{
return DoPrintChar(pWriteAnsi, c, count);
}

UINT StreamWriter::PrintChar(WCHAR c, UINT count)
{
return DoPrintChar(pWriteUnicode, c, count);
}

UINT StreamWriter::PrintDouble(DOUBLE value, StringFormatFlags flags, UINT width, UINT prec)
{
CHAR buf[64];
StringPrintDouble(buf, 64, value, flags, width, prec);
return DoPrint(pWriteAnsi, 0, buf);
}

UINT StreamWriter::PrintFloat(FLOAT value, StringFormatFlags flags, UINT width, UINT prec)
{
CHAR buf[32];
StringPrintFloat(buf, 32, value, flags, width, prec);
return DoPrint(pWriteAnsi, 0, buf);
}

UINT StreamWriter::PrintHex(UINT value, StringFormatFlags flags, UINT width)
{
CHAR buf[32];
StringPrintHex(buf, 32, value, flags, width);
return DoPrint(pWriteAnsi, 0, buf);
}

UINT StreamWriter::PrintHex64(UINT64 value, StringFormatFlags flags, UINT width)
{
CHAR buf[64];
StringPrintHex64(buf, 64, value, flags, width);
return DoPrint(pWriteAnsi, 0, buf);
}

UINT StreamWriter::PrintInt(INT value, StringFormatFlags flags, UINT width)
{
CHAR buf[32];
StringPrintInt(buf, 32, value, flags, width);
return DoPrint(pWriteAnsi, 0, buf);
}

UINT StreamWriter::PrintInt64(INT64 value, StringFormatFlags flags, UINT width)
{
CHAR buf[64];
StringPrintInt64(buf, 64, value, flags, width);
return DoPrint(pWriteAnsi, 0, buf);
}

UINT StreamWriter::PrintUInt(UINT value, StringFormatFlags flags, UINT width)
{
CHAR buf[32];
StringPrintUInt(buf, 32, value, flags, width);
return DoPrint(pWriteAnsi, 0, buf);
}

UINT StreamWriter::PrintUInt64(UINT64 value, StringFormatFlags flags, UINT width)
{
CHAR buf[64];
StringPrintUInt64(buf, 64, value, flags, width);
return DoPrint(pWriteAnsi, 0, buf);
}

VOID StreamWriter::SetStream(OutputStream* stream)
{
if(pStream==stream)
	return;
pStream=stream;
auto format=pStream->GetFormat();
switch(format)
	{
	case StreamFormat::Ansi:
		{
		pWriteAnsi=AnsiWrite<CHAR>;
		pWriteUnicode=AnsiWrite<WCHAR>;
		break;
		}
	case StreamFormat::Unicode:
		{
		pWriteAnsi=UnicodeWrite<CHAR>;
		pWriteUnicode=UnicodeWrite<WCHAR>;
		break;
		}
	default:
	case StreamFormat::UTF8:
		{
		pWriteAnsi=Utf8Write<CHAR>;
		pWriteUnicode=Utf8Write<WCHAR>;
		break;
		}
	}
}


//================
// Common Private
//================

template <class _func_t, class _char_t> UINT StreamWriter::DoPrint(_func_t write_fn, UINT len, _char_t const* value)
{
if(!value)
	return 0;
if(len==0)
	len=UINT_MAX;
UINT size=0;
for(UINT u=0; value[u]; u++)
	{
	if(u==len)
		break;
	size+=write_fn(pStream, value[u]);
	}
return size;
}

template <class _char_t> UINT StreamWriter::DoPrint(_char_t const* value, StringFormatFlags flags, UINT width)
{
if(!value)
	return 0;
UINT len=0;
if(width>0)
	len=StringLength(value);
UINT written=0;
if(len<width)
	{
	if(!GetFlag(flags, StringFormatFlags::Left))
		written+=PrintChar(' ', width-len);
	}
written+=Print(value);
if(len<width)
	{
	if(GetFlag(flags, StringFormatFlags::Left))
		written+=PrintChar(' ', width-len);
	}
return written;
}

template <class _func_t, class _char_t> UINT StreamWriter::DoPrintChar(_func_t write_fn, _char_t c, UINT count)
{
UINT size=0;
for(UINT u=0; u<count; u++)
	size+=write_fn(pStream, c);
return size;
}

}}
