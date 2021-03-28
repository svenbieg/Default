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

StreamWriter::StreamWriter(Handle<OutputStream> hstream, BOOL bunicode):
bUnicode(bunicode),
hStream(hstream)
{}


//========
// Common
//========

SIZE_T StreamWriter::CompressUInt32(UINT value)
{
BYTE* pval=(BYTE*)&value;
BYTE op=0;
BYTE rep=0;
for(UINT pos=0; pos<4; pos++)
	{
	if(!pval[pos])
		continue;
	op|=(BYTE)(1<<pos);
	if(rep)
		continue;
	for(UINT next=pos+1; next<4; next++)
		{
		if(pval[next]==pval[pos])
			{
			rep=pval[pos];
			op|=(BYTE)(1<<(4+pos));
			op|=(BYTE)(1<<(4+next));
			for(next++; next<4; next++)
				{
				if(pval[next]==rep)
					op|=(BYTE)(1<<(4+next));
				}
			break;
			}
		}
	}
SIZE_T size=0;
size+=Write(&op, sizeof(BYTE));
if(rep)
	size+=Write(&rep, sizeof(BYTE));
for(UINT pos=0; pos<4; pos++)
	{
	if(!pval[pos])
		continue;
	if(pval[pos]==rep)
		continue;
	size+=Write(&pval[pos], sizeof(BYTE));
	}
return size;
}

SIZE_T StreamWriter::CompressUInt64(UINT64 value)
{
BYTE* pval=(BYTE*)&value;
BYTE op=0;
for(UINT pos=0; pos<8; pos++)
	{
	if(pval[pos])
		op|=(BYTE)(1<<pos);
	}
SIZE_T size=0;
size+=Write(&op, sizeof(BYTE));
for(UINT pos=0; pos<8; pos++)
	{
	if(!pval[pos])
		continue;
	size+=Write(&pval[pos], sizeof(BYTE));
	}
return size;
}

SIZE_T StreamWriter::Print(UINT ulen, LPCSTR pstr)
{
ulen=StringLength(pstr, ulen);
if(ulen==0)
	return 0;
if(bUnicode)
	{
	SIZE_T usize=ulen*sizeof(WCHAR);
	if(hStream==nullptr)
		return usize;
	for(UINT u=0; u<ulen; u++)
		{
		WCHAR c=CharToUnicode(pstr[u]);
		hStream->Write(&c, sizeof(WCHAR));
		}
	return usize;
	}
if(hStream==nullptr)
	return ulen;
hStream->Write(pstr, ulen);
return ulen;
}

SIZE_T StreamWriter::Print(UINT ulen, LPCWSTR pstr)
{
ulen=StringLength(pstr, ulen);
if(ulen==0)
	return 0;
if(!bUnicode)
	{
	if(hStream==nullptr)
		return ulen;
	for(UINT u=0; u<ulen; u++)
		{
		CHAR c=CharToAnsi(pstr[u]);
		hStream->Write(&c, sizeof(CHAR));
		}
	return ulen;
	}
SIZE_T usize=ulen*sizeof(WCHAR);
if(hStream==nullptr)
	return usize;
hStream->Write(pstr, usize);
return usize;
}

SIZE_T StreamWriter::Print(UINT ulen, Handle<String> hstr)
{
if(hstr==nullptr)
	return 0;
return Print(ulen, hstr->Begin());
}

SIZE_T StreamWriter::PrintChar(CHAR c, UINT ucount)
{
if(!ucount)
	return 0;
if(bUnicode)
	{
	if(!hStream)
		return ucount*sizeof(WCHAR);
	WCHAR wc=CharToUnicode(c);
	for(UINT u=0; u<ucount; u++)
		hStream->Write(&wc, sizeof(WCHAR));
	return ucount*sizeof(WCHAR);
	}
if(!hStream)
	return ucount*sizeof(CHAR);
for(UINT u=0; u<ucount; u++)
	hStream->Write(&c, sizeof(CHAR));
return ucount*sizeof(CHAR);
}

SIZE_T StreamWriter::Write(VOID const* pbuf, SIZE_T size)
{
if(hStream)
	return hStream->Write(pbuf, size);
return size;
}

SIZE_T StreamWriter::WriteByte(BYTE ubyte, SIZE_T ucount)
{
if(!hStream)
	return ucount;
SIZE_T usize=0;
for(SIZE_T u=0; u<ucount; u++)
	{
	SIZE_T written=hStream->Write(&ubyte, sizeof(BYTE));
	if(!written)
		break;
	usize+=written;
	}
return usize;
}

SIZE_T StreamWriter::WriteStream(Handle<InputStream> hstream)
{
if(!hstream)
	return 0;
SIZE_T usize=hstream->Available();
if(!hStream)
	return usize;
BYTE pbuf[128];
for(SIZE_T upos=0; upos<usize;)
	{
	SIZE_T uread=hstream->Read(pbuf, 128);
	hStream->Write(pbuf, uread);
	upos+=uread;
	}
return usize;
}

SIZE_T StreamWriter::WriteString(UINT ulen, LPCSTR pstr)
{
SIZE_T usize=Print(ulen, pstr);
usize+=PrintChar(0);
return usize;
}

SIZE_T StreamWriter::WriteString(UINT ulen, LPCWSTR pstr)
{
SIZE_T usize=Print(ulen, pstr);
usize+=PrintChar(0);
return usize;
}

SIZE_T StreamWriter::WriteString(UINT ulen, Handle<String> hstr)
{
SIZE_T usize=0;
if(hstr)
	usize+=Print(ulen, hstr);
usize+=PrintChar(0);
return usize;
}

}}
