//==================
// StreamReader.cpp
//==================

#include "pch.h"


//=======
// Using
//=======

#include "Storage/Compression.h"
#include "Storage/Intermediate.h"
#include "CharHelper.h"
#include "StreamReader.h"


//===========
// Namespace
//===========

namespace Storage {
	namespace Streams {


//==================
// Con-/Destructors
//==================

StreamReader::StreamReader(Handle<InputStream> hstream, BOOL bunicode):
bUnicode(bunicode),
hStream(hstream)
{}


//========
// Access
//========

SIZE_T StreamReader::Available()
{
return hStream->Available();
}

SIZE_T StreamReader::ExtractUInt32(UINT* pvalue)
{
*pvalue=0;
SIZE_T size=0;
BYTE op=0;
size+=Read(&op, sizeof(BYTE));
if(!op)
	return size;
BYTE repeat=0;
if(op&0xF0)
	size+=Read(&repeat, sizeof(BYTE));
BYTE* pval=(BYTE*)pvalue;
for(UINT pos=0; pos<4; pos++)
	{
	if(op&(1<<pos))
		{
		if(op&(1<<(4+pos)))
			{
			pval[pos]=repeat;
			}
		else
			{
			size+=Read(&pval[pos], sizeof(BYTE));
			}
		}
	}
return size;
}

SIZE_T StreamReader::ExtractUInt64(UINT64* pvalue)
{
*pvalue=0;
SIZE_T size=0;
BYTE op=0;
size+=Read(&op, sizeof(BYTE));
if(!op)
	return size;
BYTE* pval=(BYTE*)pvalue;
for(UINT pos=0; pos<8; pos++)
	{
	if(op&(1<<pos))
		size+=Read(&pval[pos], sizeof(BYTE));
	}
return size;
}

SIZE_T StreamReader::GoTo(TCHAR cto)
{
SIZE_T uavailable=hStream->Available();
for(SIZE_T upos=0; upos<uavailable; upos++)
	{
	TCHAR c=ReadChar();
	if(c==cto)
		return upos+1;
	}
return uavailable;
}

SIZE_T StreamReader::Read(VOID* pbuf, SIZE_T size)
{
return hStream->Read(pbuf, size);
}

BYTE StreamReader::ReadByte()
{
BYTE b=0;
hStream->Read(&b, sizeof(BYTE));
return b;
}

TCHAR StreamReader::ReadChar()
{
SIZE_T uavailable=hStream->Available();
UINT uchar=bUnicode? sizeof(WCHAR): sizeof(CHAR);
if(uavailable<uchar)
	return 0;
TCHAR tc=0;
if(bUnicode)
	{
	#ifdef _UNICODE
	hStream->Read(&tc, sizeof(WCHAR));
	#else
	WCHAR wc;
	hStream->Read(&wc, sizeof(WCHAR));
	tc=CharToAnsi(wc);
	#endif
	}
else
	{
	#ifdef _UNICODE
	CHAR c=0;
	hStream->Read(&c, sizeof(CHAR));
	tc=CharToUnicode(c);
	#else
	hStream->Read(&tc, sizeof(CHAR));
	#endif
	}
return tc;
}

FLOAT StreamReader::ReadFloat()
{
FLOAT f=0.f;
Read(&f, sizeof(FLOAT));
return f;
}

INT StreamReader::ReadInt()
{
INT i=0;
Read(&i, sizeof(INT));
return i;
}

Handle<String> StreamReader::ReadString(TCHAR cstop, SIZE_T* psize)
{
Handle<Intermediate> hbuf=new Intermediate();
SIZE_T usize=0;
while(hStream->Available())
	{
	TCHAR c=ReadChar();
	usize++;
	if(c==cstop)
		c=0;
	if(c==0)
		break;
	hbuf->Write(&c, sizeof(TCHAR));
	}
if(psize)
	*psize+=usize;
UINT ulen=hbuf->GetSize().ToUINT()/sizeof(TCHAR);
if(ulen==0)
	return nullptr;
Handle<String> hstr=new String(ulen+1, nullptr);
LPTSTR pstr=(LPTSTR)hstr->Begin();
hbuf->Seek(0);
hbuf->Read(pstr, ulen*sizeof(TCHAR));
pstr[ulen]=0;
return hstr;
}

UINT StreamReader::ReadString(LPTSTR pstr, UINT usize, TCHAR cstop)
{
SIZE_T uavailable=hStream->Available();
if(!uavailable)
	{
	pstr[0]=0;
	return 0;
	}
SIZE_T umax=MIN(usize, uavailable);
SIZE_T upos=0;
while(upos<umax)
	{
	TCHAR c=ReadChar();
	if(c==cstop)
		c=0;
	pstr[upos++]=c;
	if(!c)
		break;
	}
return upos;
}

UINT StreamReader::ReadUInt()
{
UINT u=0;
Read(&u, sizeof(UINT));
return u;
}

SIZE_T StreamReader::ReadUInt(UINT* pu)
{
return hStream->Read(pu, sizeof(UINT));
}

UINT64 StreamReader::ReadUInt64()
{
UINT64 u=0;
Read(&u, sizeof(UINT64));
return u;
}

SIZE_T StreamReader::ReadUInt64(UINT64* pu)
{
return hStream->Read(pu, sizeof(UINT));
}

WORD StreamReader::ReadWord()
{
WORD u=0;
Read(&u, sizeof(WORD));
return u;
}

SIZE_T StreamReader::Skip()
{
SIZE_T usize=hStream->Available();
return hStream->Read(nullptr, usize);
}

SIZE_T StreamReader::Skip(SIZE_T usize)
{
return hStream->Read(nullptr, usize);
}

SIZE_T StreamReader::SkipChar()
{
SIZE_T uchar=bUnicode? sizeof(WCHAR): sizeof(CHAR);
SIZE_T uavailable=hStream->Available();
SIZE_T uskip=MIN(uavailable, uchar);
return hStream->Read(nullptr, uskip);
}

SIZE_T StreamReader::SkipChars(UINT ucount)
{
SIZE_T uchar=bUnicode? sizeof(WCHAR): sizeof(CHAR);
SIZE_T utotal=uchar*ucount;
SIZE_T uavailable=hStream->Available();
SIZE_T uskip=MIN(uavailable, utotal);
return hStream->Read(nullptr, uskip);
}

}}
