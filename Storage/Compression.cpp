//=================
// Compression.cpp
//=================

#include "pch.h"


//=======
// Using
//=======

#include "Compression.h"


//===========
// Operators
//===========
// |    7   |     6    |    5   |  4 | 3 | 2 | 1 | 0 |
// | REPEAT | RESIDENT | (DATA) | (TYPE) |    SIZE   |

#define COMP_REPEAT 0x80
#define COMP_RESIDENT 0x40
#define COMP_DATA 0x20

#define COMP_TYPE_BYTE 0
#define COMP_TYPE_WORD 1
#define COMP_TYPE_DWORD 2
#define COMP_TYPE_QWORD 3


//===========
// Namespace
//===========

namespace Storage {


//=============
// Compression
//=============

UINT Compress(VOID const* psrc, UINT usrcsize, VOID* pdst, UINT udstsize)
{
ASSERT(psrc&&usrcsize&&pdst&&udstsize);
BYTE* psrcbuf=(BYTE*)psrc;
BYTE* pdstbuf=(BYTE*)pdst;
UINT usrcpos=0;
UINT udstpos=0;
while(usrcpos<usrcsize)
	{
	UINT upos=usrcpos;
	UINT64* pqwordbuf=0;
	UINT uqwordcount=0;
	UINT* pdwordbuf=0;
	UINT udwordcount=0;
	WORD* pwordbuf=0;
	UINT uwordcount=0;
	UINT ubytecount=0;
	for(; upos<usrcsize; upos++)
		{
		ubytecount=0;
		if(upos<usrcsize)
			{
			ubytecount++;
			UINT ucount=usrcsize-upos;
			for(UINT u=1; u<ucount; u++)
				{
				if(psrcbuf[u]!=psrcbuf[0])
					break;
				ubytecount++;
				}
			}
		if(ubytecount>7)
			break;
		pwordbuf=(WORD*)&psrcbuf[upos];
		uwordcount=0;
		if(upos+2<=usrcsize)
			{
			uwordcount++;
			UINT ucount=(usrcsize-upos)/2;
			for(UINT u=1; u<ucount; u++)
				{
				if(pwordbuf[u]!=pwordbuf[0])
					break;
				uwordcount++;
				}
			}
		if(uwordcount>3)
			break;
		pdwordbuf=(UINT*)&psrcbuf[upos];
		udwordcount=0;
		if(upos+4<=usrcsize)
			{
			udwordcount++;
			UINT ucount=(usrcsize-upos)/4;
			for(UINT u=1; u<ucount; u++)
				{
				if(pdwordbuf[u]!=pdwordbuf[0])
					break;
				udwordcount++;
				}
			}
		if(udwordcount>2)
			break;
		pqwordbuf=(UINT64*)&psrcbuf[upos];
		uqwordcount=0;
		if(upos+8<=usrcsize)
			{
			uqwordcount++;
			UINT ucount=(usrcsize-upos)/8;
			for(UINT u=1; u<ucount; u++)
				{
				if(pqwordbuf[u]!=pqwordbuf[0])
					break;
				uqwordcount++;
				}
			}
		if(uqwordcount>1)
			break;
		if(udwordcount>1)
			break;
		if(uwordcount>2)
			break;
		if(ubytecount>2)
			break;
		}
	if(upos>usrcpos)
		{
		UINT ucopy=upos-usrcpos;
		if(ucopy<64)
			{
			if(pdst)
				{
				if(udstpos+1+ucopy>udstsize)
					return 0;
				pdstbuf[udstpos]=(BYTE)(COMP_RESIDENT|ucopy);
				CopyMemory(&pdstbuf[udstpos+1], &psrcbuf[usrcpos], ucopy);
				}
			udstpos+=1+ucopy;
			}
		else
			{
			UINT usize=0;
			for(UINT u=ucopy; u>0; u=u>>8)
				usize++;
			if(pdst)
				{
				if(udstpos+1+usize+ucopy>udstsize)
					return 0;
				pdstbuf[udstpos]=(BYTE)usize;
				CopyMemory(&pdstbuf[udstpos+1], &ucopy, usize);
				CopyMemory(&pdstbuf[udstpos+usize], &psrcbuf[usrcpos], ucopy);
				}
			udstpos+=1+usize+ucopy;
			}
		usrcpos+=ucopy;
		}
	if(usrcpos==usrcsize)
		break;
	if(uqwordcount>1)
		{
		if(udwordcount<2&&uwordcount<4&&ubytecount<8)
			{
			BYTE op=COMP_REPEAT;
			op|=COMP_TYPE_QWORD<<3;
			UINT ublocksize=1;
			if(pqwordbuf[0])
				{
				op|=COMP_DATA;
				ublocksize+=8;
				}
			if(uqwordcount<8)
				{
				if(pdst)
					{
					if(udstpos+ublocksize>udstsize)
						return 0;
					op|=COMP_RESIDENT;
					BYTE u=(BYTE)uqwordcount;
					op|=u;
					pdstbuf[udstpos]=op;
					if(pqwordbuf[0])
						CopyMemory(&pdstbuf[udstpos+1], pqwordbuf, 8);
					}
				udstpos+=ublocksize;
				}
			else
				{
				BYTE usize=0;
				for(UINT u=uqwordcount; u>0; u=u>>8)
					usize++;
				ublocksize+=usize;
				if(pdst)
					{
					if(udstpos+ublocksize>udstsize)
						return 0;
					op|=usize;
					pdstbuf[udstpos]=op;
					CopyMemory(&pdstbuf[udstpos+1], &uqwordcount, usize);
					if(pqwordbuf[0])
						CopyMemory(&pdstbuf[udstpos+1+usize], pqwordbuf, 8);
					}
				udstpos+=ublocksize;
				}
			usrcpos+=uqwordcount*8;
			continue;
			}
		}
	if(udwordcount>1)
		{
		if(uwordcount<2&&ubytecount<4)
			{
			BYTE op=COMP_REPEAT;
			op|=COMP_TYPE_DWORD<<3;
			UINT ublocksize=1;
			if(pdwordbuf[0])
				{
				op|=COMP_DATA;
				ublocksize+=4;
				}
			if(udwordcount<8)
				{
				if(pdst)
					{
					if(udstpos+ublocksize>udstsize)
						return 0;
					op|=COMP_RESIDENT;
					BYTE u=(BYTE)udwordcount;
					op|=u;
					pdstbuf[udstpos]=op;
					if(pdwordbuf[0])
						CopyMemory(&pdstbuf[udstpos+1], pdwordbuf, 4);
					}
				udstpos+=ublocksize;
				}
			else
				{
				BYTE usize=0;
				for(UINT u=udwordcount; u>0; u=u>>8)
					usize++;
				ublocksize+=usize;
				if(pdst)
					{
					if(udstpos+ublocksize>udstsize)
						return 0;
					op|=usize;
					pdstbuf[udstpos]=op;
					CopyMemory(&pdstbuf[udstpos+1], &udwordcount, usize);
					if(pdwordbuf[0])
						CopyMemory(&pdstbuf[udstpos+1+usize], pdwordbuf, 4);
					}
				udstpos+=ublocksize;
				}
			usrcpos+=udwordcount*4;
			continue;
			}
		}
	if(uwordcount>1)
		{
		if(ubytecount<2)
			{
			BYTE op=COMP_REPEAT;
			op|=COMP_TYPE_WORD<<3;
			UINT ublocksize=1;
			if(pwordbuf[0])
				{
				op|=COMP_DATA;
				ublocksize+=2;
				}
			if(uwordcount<8)
				{
				if(pdst)
					{
					if(udstpos+ublocksize>udstsize)
						return 0;
					op|=COMP_RESIDENT;
					BYTE u=(BYTE)uwordcount;
					op|=u;
					pdstbuf[udstpos]=op;
					if(pwordbuf[0])
						CopyMemory(&pdstbuf[udstpos+1], pwordbuf, 2);
					}
				udstpos+=ublocksize;
				}
			else
				{
				BYTE usize=0;
				for(UINT u=uwordcount; u>0; u=u>>8)
					usize++;
				ublocksize+=usize;
				if(pdst)
					{
					if(udstpos+ublocksize>udstsize)
						return 0;
					op|=usize;
					pdstbuf[udstpos]=op;
					CopyMemory(&pdstbuf[udstpos+1], &uwordcount, usize);
					if(pwordbuf[0])
						CopyMemory(&pdstbuf[udstpos+1+usize], pwordbuf, 2);
					}
				udstpos+=ublocksize;
				}
			usrcpos+=uwordcount*2;
			continue;
			}
		}
	BYTE op=COMP_REPEAT;
	UINT ublocksize=1;
	if(psrcbuf[0])
		{
		op|=COMP_DATA;
		ublocksize++;
		}
	if(ubytecount<8)
		{
		if(pdst)
			{
			if(udstpos+ublocksize>udstsize)
				return 0;
			op|=COMP_RESIDENT;
			BYTE u=(BYTE)ubytecount;
			op|=u;
			pdstbuf[udstpos]=op;
			if(psrcbuf[0])
				pdstbuf[udstpos+1]=psrcbuf[upos];
			}
		udstpos+=ublocksize;
		}
	else
		{
		BYTE usize=0;
		for(UINT u=ubytecount; u>0; u=u>>8)
			usize++;
		ublocksize+=usize;
		if(pdst)
			{
			if(udstpos+ublocksize>udstsize)
				return 0;
			op|=(BYTE)usize;
			pdstbuf[udstpos]=op;
			CopyMemory(&pdstbuf[udstpos+1], &ubytecount, usize);
			if(psrcbuf[0])
				pdstbuf[udstpos+1+usize]=psrcbuf[upos];
			}
		udstpos+=ublocksize;
		}
	usrcpos+=ubytecount;
	}
return udstpos;
}

UINT Compress32(UINT uvalue, VOID* pbufv)
{
BYTE* pbuf=(BYTE*)pbufv;
BYTE ptmp[5];
if(!pbuf)
	pbuf=ptmp;
BYTE* pvalue=(BYTE*)&uvalue;
BYTE op=0;
BYTE rep=0;
for(UINT upos=0; upos<4; upos++)
	{
	if(!pvalue[upos])
		continue;
	for(UINT upos1=upos+1; upos1<4; upos1++)
		{
		if(pvalue[upos1]==pvalue[upos])
			{
			rep=pvalue[upos];
			BYTE u=(BYTE)(1<<(4+upos));
			op|=u;
			BYTE u1=(BYTE)(1<<(4+upos1));
			op|=u1;
			for(UINT upos2=upos1+1; upos2<4; upos2++)
				{
				if(pvalue[upos2]==rep)
					{
					BYTE u2=(BYTE)(1<<(4+upos2));
					op|=u2;
					}
				}
			upos=4;
			break;
			}
		}
	}
UINT ubufpos=1;
if(rep)
	{
	pbuf[ubufpos]=rep;
	ubufpos++;
	}
for(UINT upos=0; upos<4; upos++)
	{
	if(pvalue[upos])
		{
		BYTE u=(BYTE)(1<<upos);
		op|=u;
		if(pvalue[upos]==rep)
			continue;
		pbuf[ubufpos]=pvalue[upos];
		ubufpos++;
		}
	}
pbuf[0]=op;
return ubufpos;
}

UINT Compress64(UINT64 uvalue, VOID* pbufv)
{
BYTE* pbuf=(BYTE*)pbufv;
BYTE ptmp[9];
if(!pbuf)
	pbuf=ptmp;
BYTE* pvalue=(BYTE*)&uvalue;
BYTE op=0;
UINT ubufpos=1;
for(UINT upos=0; upos<8; upos++)
	{
	if(pvalue[upos])
		{
		pbuf[ubufpos]=pvalue[upos];
		ubufpos++;
		BYTE u=(BYTE)(1<<upos);
		op|=u;
		}
	}
pbuf[0]=op;
return ubufpos;
}


//============
// Extraction
//============

UINT Extract(VOID const* psrc, UINT usrcsize, VOID* pdst, UINT* pdstsize)
{
ASSERT(psrc&&usrcsize&&pdst&&pdstsize);
UINT udstsize=*pdstsize;
if(pdst&&!udstsize)
	return 0;
BYTE* psrcbuf=(BYTE*)psrc;
BYTE op=psrcbuf[0];
if(!op)
	{
	if(pdst)
		{
		if(udstsize<1)
			return 0;
		BYTE* pdstbuf=(BYTE*)pdst;
		pdstbuf[0]=0;
		}
	*pdstsize=1;
	return 1;
	}
UINT usrcpos=1;
UINT ucount=0;
if(op&COMP_RESIDENT)
	{
	ucount=op&0x07;
	}
else
	{
	UINT usize=op&0x07;
	CopyMemory(&ucount, &psrcbuf[usrcpos], usize);
	usrcpos+=usize;
	}
if(op&COMP_REPEAT)
	{
	BYTE type=(op>>3)&0x03;
	switch(type)
		{
		case COMP_TYPE_BYTE:
			{
			if(pdst)
				{
				if(ucount>udstsize)
					return 0;
				if(op&COMP_DATA)
					{
					SetMemory(pdst, psrcbuf[usrcpos], ucount);
					usrcpos++;
					}
				else
					{
					ZeroMemory(pdst, ucount);
					}
				}
			*pdstsize=ucount;
			return usrcpos;
			}
		case COMP_TYPE_WORD:
			{
			if(pdst)
				{
				if(ucount*2>udstsize)
					return 0;
				if(op&COMP_DATA)
					{
					WORD word=0;
					CopyMemory(&word, &psrcbuf[usrcpos], 2);
					WORD* pdstbuf=(WORD*)pdst;
					for(UINT u=0; u<ucount; u++)
						pdstbuf[u]=word;
					usrcpos+=2;
					}
				else
					{
					ZeroMemory(pdst, ucount*2);
					}
				}
			*pdstsize=ucount*2;
			return usrcpos;
			}
		case COMP_TYPE_DWORD:
			{
			if(pdst)
				{
				if(ucount*4>udstsize)
					return 0;
				if(op&COMP_DATA)
					{
					DWORD dword=0;
					CopyMemory(&dword, &psrcbuf[usrcpos], 4);
					DWORD* pdstbuf=(DWORD*)pdst;
					for(UINT u=0; u<ucount; u++)
						pdstbuf[u]=dword;
					usrcpos+=4;
					}
				else
					{
					ZeroMemory(pdst, ucount*4);
					}
				}
			*pdstsize=ucount*4;
			return usrcpos;
			}
		case COMP_TYPE_QWORD:
			{
			if(pdst)
				{
				if(ucount*8>udstsize)
					return 0;
				if(op&COMP_DATA)
					{
					UINT64 qword=0;
					CopyMemory(&qword, &psrcbuf[usrcpos], 8);
					UINT64* pdstbuf=(UINT64*)pdst;
					for(UINT u=0; u<ucount; u++)
						pdstbuf[u]=qword;
					usrcpos+=8;
					}
				else
					{
					ZeroMemory(pdst, ucount*8);
					}
				}
			*pdstsize=ucount*8;
			return usrcpos;
			}
		default:
			{
			return 0;
			}
		}
	}
if(pdst)
	{
	if(ucount>udstsize)
		return 0;
	CopyMemory(pdst, &psrcbuf[usrcpos], ucount);
	usrcpos+=ucount;
	}
*pdstsize=ucount;
return usrcpos;
}

UINT Extract32(VOID const* pbufv, UINT* pvalue)
{
ASSERT(pbufv&&pvalue);
*pvalue=0;
BYTE* pbuf=(BYTE*)pbufv;
BYTE op=pbuf[0];
if(!op)
	return 1;
UINT ubufpos=1;
BYTE rep=0;
if(op&0xF0)
	{
	rep=pbuf[ubufpos];
	ubufpos++;
	}
BYTE* pvalueb=(BYTE*)pvalue;
for(UINT upos=0; upos<4; upos++)
	{
	if(op&(1<<upos))
		{
		if(op&(1<<(4+upos)))
			{
			pvalueb[upos]=rep;
			}
		else
			{
			pvalueb[upos]=pbuf[ubufpos];
			ubufpos++;
			}
		}
	}
return ubufpos;
}

UINT Extract64(VOID const* pbufv, UINT64* pvalue)
{
ASSERT(pbufv&&pvalue);
*pvalue=0;
BYTE* pbuf=(BYTE*)pbufv;
BYTE op=pbuf[0];
if(!op)
	return 1;
UINT ubufpos=1;
BYTE* pvalueb=(BYTE*)pvalue;
for(UINT upos=0; upos<8; upos++)
	{
	if(op&(1<<upos))
		{
		pvalueb[upos]=pbuf[ubufpos];
		ubufpos++;
		}
	}
return ubufpos;
}

}
