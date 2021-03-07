//================
// CharHelper.cpp
//================

#include "pch.h"


//=======
// Using
//=======

#include "CharHelper.h"


//========
// Common
//========

template <class _char_t> BOOL CharIsAlpha(_char_t c)
{
if(c>='A'&&c<='Z')
	return true;
if(c>='a'&&c<='z')
	return true;
return false;
}

BOOL CharIsAlpha(CHAR c)
{
return CharIsAlpha<CHAR>(c);
}

BOOL CharIsAlpha(WCHAR c)
{
return CharIsAlpha<WCHAR>(c);
}

template <class _char_t> BOOL CharIsBinary(_char_t c)
{
if(c=='0'||c=='1')
	return true;
return false;
}

BOOL CharIsBinary(CHAR c)
{
return CharIsBinary<CHAR>(c);
}

BOOL CharIsBinary(WCHAR c)
{
return CharIsBinary<WCHAR>(c);
}

template <class _char_t> BOOL CharIsBreak(_char_t c, _char_t const* pstr, UINT ulen)
{
if(c==0)
	return true;
for(UINT u=0; u<ulen; u++)
	{
	if(c==pstr[u])
		return true;
	}
return false;
}

BOOL CharIsBreak(CHAR c)
{
CHAR pstr[]="\n\r\t;:&|+*/\\?!";
return CharIsBreak<CHAR>(c, pstr, ARRAYSIZE(pstr));
}

BOOL CharIsBreak(WCHAR c)
{
WCHAR pstr[]=L"\n\r\t;:&|+*/\\?!";
return CharIsBreak<WCHAR>(c, pstr, ARRAYSIZE(pstr));
}

template <class _char_t> BOOL CharIsCapital(_char_t c)
{
if(c>='A'&&c<='Z')
	return true;
return false;
}

BOOL CharIsCapital(CHAR c)
{
return CharIsCapital<CHAR>(c);
}

BOOL CharIsCapital(WCHAR c)
{
return CharIsCapital<WCHAR>(c);
}

template <class _char_t> BOOL CharIsHex(_char_t c)
{
if(c>='0'&&c<='9')
	return true;
if(c>='A'&&c<='F')
	return true;
if(c>='a'&&c<='f')
	return true;
return false;
}

BOOL CharIsHex(CHAR c)
{
return CharIsHex<CHAR>(c);
}

BOOL CharIsHex(WCHAR c)
{
return CharIsHex<WCHAR>(c);
}

template <class _char_t> BOOL CharIsNumber(_char_t c)
{
if(c>='0'&&c<='9')
	return true;
return false;
}

BOOL CharIsNumber(CHAR c)
{
return CharIsNumber<CHAR>(c);
}

BOOL CharIsNumber(WCHAR c)
{
return CharIsNumber<WCHAR>(c);
}

template <class _char_t> BOOL CharIsPrintable(_char_t c)
{
if(c>=' '&&c<='~')
	return true;
return false;
}

BOOL CharIsPrintable(CHAR c)
{
return CharIsPrintable<CHAR>(c);
}

BOOL CharIsPrintable(WCHAR c)
{
return CharIsPrintable<WCHAR>(c);
}

template <class _char_t> BOOL CharIsSmall(_char_t c)
{
if(c>='a'&&c<='z')
	return true;
return false;
}

BOOL CharIsSmall(CHAR c)
{
return CharIsSmall<CHAR>(c);
}

BOOL CharIsSmall(WCHAR c)
{
return CharIsSmall<WCHAR>(c);
}

template <class _char_t> BOOL CharIsSpecial(_char_t c, _char_t const* pstr, UINT ulen)
{
for(UINT u=0; u<ulen; u++)
	{
	if(c==pstr[u])
		return true;
	}
return false;
}

BOOL CharIsSpecial(CHAR c)
{
CHAR pstr[]="\"*/:<>?\\|";
return CharIsSpecial<CHAR>(c, pstr, ARRAYSIZE(pstr));
}

BOOL CharIsSpecial(WCHAR c)
{
WCHAR pstr[]=L"\"*/:<>?\\|";
return CharIsSpecial<WCHAR>(c, pstr, ARRAYSIZE(pstr));
}


//============
// Conversion
//============

template <class _char_t> _char_t CharToCapital(_char_t c)
{
if(c>='a'&&c<='z')
	return (_char_t)(c-0x20);
return c;
}

CHAR CharToCapital(CHAR c)
{
return CharToCapital<CHAR>(c);
}

WCHAR CharToCapital(WCHAR c)
{
return CharToCapital<WCHAR>(c);
}

BYTE CharToHex(CHAR c)
{
if(c<'0')
	return 0;
BYTE u=(BYTE)(c-'0');
if(u<10)
	return u;
if(c<'A')
	return 0;
u=(BYTE)(c-'A'+10);
if(u<16)
	return u;
if(u<'a')
	return 0;
u=(BYTE)(c-'a'+10);
if(u<16)
	return u;
return 0;
}

BYTE CharToHex(WCHAR c)
{
return CharToHex(CharToAnsi(c));
}

template <class _char_t> _char_t CharToSmall(_char_t c)
{
if(c>='A'&&c<='Z')
	return (_char_t)(c+0x20);
return c;
}

CHAR CharToSmall(CHAR c)
{
return CharToSmall<CHAR>(c);
}

WCHAR CharToSmall(WCHAR c)
{
return CharToSmall<WCHAR>(c);
}


//============
// Comparison
//============

template <class _char_t> INT CharCompare(_char_t c1, _char_t c2, BOOL bcs, _char_t const* psort, UINT ulen)
{
_char_t c1i=c1;
_char_t c2i=c2;
if(!bcs)
	{
	c1i=CharToCapital(c1);
	c2i=CharToCapital(c2);
	}
UINT upos1=0;
for(; upos1<ulen; upos1++)
	{
	if(c1i==psort[upos1])
		break;
	}
UINT upos2=0;
for(; upos2<ulen; upos2++)
	{
	if(c2i==psort[upos2])
		break;
	}
if(upos1==upos2)
	{
	if(c1i>c2i)
		return 1;
	if(c2i>c1i)
		return -1;
	return 0;
	}
if(upos1>upos2)
	return 1;
if(upos2>upos1)
	return -1;
return 0;
}

INT CharCompare(CHAR c1, CHAR c2, BOOL bcs)
{
CHAR psort[]="0123456789AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz";
return CharCompare<CHAR>(c1, c2, bcs, psort, ARRAYSIZE(psort));
}

INT CharCompare(WCHAR c1, WCHAR c2, BOOL bcs)
{
WCHAR psort[]=L"0123456789AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz";
return CharCompare<WCHAR>(c1, c2, bcs, psort, ARRAYSIZE(psort));
}

template <class _char_t> BOOL CharEqual(_char_t c1, _char_t c2, BOOL bcs)
{
if(bcs)
	return c1==c2;
c1=CharToCapital(c1);
c2=CharToCapital(c2);
return c1==c2;
}

BOOL CharEqual(CHAR c1, CHAR c2, BOOL bcs)
{
return CharEqual<CHAR>(c1, c2, bcs);
}

BOOL CharEqual(WCHAR c1, WCHAR c2, BOOL bcs)
{
return CharEqual<WCHAR>(c1, c2, bcs);
}
