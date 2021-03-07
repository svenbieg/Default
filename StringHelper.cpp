//==================
// StringHelper.cpp
//==================

#include "pch.h"


//=======
// Using
//=======

#include <math.h>
#include "CharHelper.h"
#include "MemoryHelper.h"
#include "StringHelper.h"


//========
// Common
//========

template <class _str_t, class _char_t> inline BOOL _StringContainsChar(_str_t const* pstr, _char_t c, UINT ustart, UINT ufind, BOOL bcs)
{
if(!pstr||!c)
	return false;
UINT ulen=StringLength(pstr);
UINT uend=ulen;
if(ufind>0)
	uend=MIN(ustart+ufind, ulen);
for(UINT u=ustart; u<uend; u++)
	{
	if(CharCompare(pstr[u], c, bcs)==0)
		return true;
	}
return false;
}

template <class _str_t, class _find_t> inline BOOL _StringContainsString(_str_t const* pstr, _find_t const* pfind, UINT ustart, UINT ufind, BOOL bcs)
{
if(!pstr||!pfind)
	return false;
UINT ulen=StringLength(pstr);
UINT uend=ulen;
if(ufind>0)
	uend=MIN(ustart+ufind, ulen);
UINT ufindlen=StringLength(pfind);
if(!ufindlen||uend<ufindlen-1)
	return false;
uend-=ufindlen-1;
for(UINT u=ustart; u<uend; u++)
	{
	if(StringCompare(&pstr[u], pfind, ufindlen, bcs)==0)
		return true;
	}
return false;
}

BOOL StringContains(LPCSTR pstr, CHAR c, UINT ustart, UINT ulen, BOOL bcs)
{
return _StringContainsChar<CHAR, CHAR>(pstr, c, ustart, ulen, bcs);
}

BOOL StringContains(LPCSTR pstr, WCHAR c, UINT ustart, UINT ulen, BOOL bcs)
{
return _StringContainsChar<CHAR, WCHAR>(pstr, c, ustart, ulen, bcs);
}

BOOL StringContains(LPCSTR pstr, LPCSTR pfind, UINT ustart, UINT ulen, BOOL bcs)
{
return _StringContainsString<CHAR, CHAR>(pstr, pfind, ustart, ulen, bcs);
}

BOOL StringContains(LPCSTR pstr, LPCWSTR pfind, UINT ustart, UINT ulen, BOOL bcs)
{
return _StringContainsString<CHAR, WCHAR>(pstr, pfind, ustart, ulen, bcs);
}

BOOL StringContains(LPCWSTR pstr, CHAR c, UINT ustart, UINT ulen, BOOL bcs)
{
return _StringContainsChar<WCHAR, CHAR>(pstr, c, ustart, ulen, bcs);
}

BOOL StringContains(LPCWSTR pstr, WCHAR c, UINT ustart, UINT ulen, BOOL bcs)
{
return _StringContainsChar<WCHAR, WCHAR>(pstr, c, ustart, ulen, bcs);
}

BOOL StringContains(LPCWSTR pstr, LPCSTR pfind, UINT ustart, UINT ulen, BOOL bcs)
{
return _StringContainsString<WCHAR, CHAR>(pstr, pfind, ustart, ulen, bcs);
}

BOOL StringContains(LPCWSTR pstr, LPCWSTR pfind, UINT ustart, UINT ulen, BOOL bcs)
{
return _StringContainsString<WCHAR, WCHAR>(pstr, pfind, ustart, ulen, bcs);
}

template <class _str_t, class _find_t> inline UINT _StringCount(_str_t const* pstr, _find_t const* pfind, UINT ustart, UINT ufind, BOOL bcs)
{
UINT ulen=StringLength(pstr);
UINT ufindlen=StringLength(pfind);
if(!ulen||!ufindlen||ulen<ufindlen)
	return 0;
UINT uend=ulen;
if(ufind>0)
	uend=MIN(ustart+ufind, ulen);
uend-=ufindlen-1;
UINT ucount=0;
for(UINT u=ustart; u<uend; u++)
	{
	if(StringCompare(&pstr[u], pfind, ufindlen, bcs)==0)
		{
		ucount++;
		u+=ufindlen-1;
		}
	}
return ucount;
}

UINT StringCount(LPCSTR pstr, LPCSTR pfind, UINT ustart, UINT ulen, BOOL bcs)
{
return _StringCount<CHAR, CHAR>(pstr, pfind, ustart, ulen, bcs);
}

UINT StringCount(LPCSTR pstr, LPCWSTR pfind, UINT ustart, UINT ulen, BOOL bcs)
{
return _StringCount<CHAR, WCHAR>(pstr, pfind, ustart, ulen, bcs);
}

UINT StringCount(LPCWSTR pstr, LPCSTR pfind, UINT ustart, UINT ulen, BOOL bcs)
{
return _StringCount<WCHAR, CHAR>(pstr, pfind, ustart, ulen, bcs);
}

UINT StringCount(LPCWSTR pstr, LPCWSTR pfind, UINT ustart, UINT ulen, BOOL bcs)
{
return _StringCount<WCHAR, WCHAR>(pstr, pfind, ustart, ulen, bcs);
}

template <class _str_t, class _find_t> inline BOOL _StringFind(_str_t const* pstr, _find_t const* pfind, UINT* ppos, UINT umax, BOOL bcs)
{
UINT ulen=StringLength(pstr, umax);
UINT ufindlen=StringLength(pfind);
if(!ulen||!ufindlen||ulen<ufindlen)
	return false;
UINT ustr=0;
if(ppos!=nullptr)
	ustr=*ppos;
UINT uend=ulen-ufindlen+1;
for(; ustr<uend; ustr++)
	{
	if(StringCompare(&pstr[ustr], pfind, ufindlen, bcs)==0)
		{
		if(ppos!=nullptr)
			*ppos=ustr;
		return true;
		}
	}
return false;
}

BOOL StringFind(LPCSTR pstr, LPCSTR pfind, UINT* ppos, UINT umax, BOOL bcs)
{
return _StringFind<CHAR, CHAR>(pstr, pfind, ppos, umax, bcs);
}

BOOL StringFind(LPCSTR pstr, LPCWSTR pfind, UINT* ppos, UINT umax, BOOL bcs)
{
return _StringFind<CHAR, WCHAR>(pstr, pfind, ppos, umax, bcs);
}

BOOL StringFind(LPCWSTR pstr, LPCSTR pfind, UINT* ppos, UINT umax, BOOL bcs)
{
return _StringFind<WCHAR, CHAR>(pstr, pfind, ppos, umax, bcs);
}

BOOL StringFind(LPCWSTR pstr, LPCWSTR pfind, UINT* ppos, UINT umax, BOOL bcs)
{
return _StringFind<WCHAR, WCHAR>(pstr, pfind, ppos, umax, bcs);
}

template <class _char_t> inline UINT _StringLength(_char_t const* pstr, UINT umax)
{
if(!pstr)
	return 0;
if(!umax)
	umax=MAX_UINT;
for(UINT u=0; u<umax; u++)
	{
	if(pstr[u]==0)
		return u;
	}
return umax;
}

UINT StringLength(LPCSTR pstr, UINT umax)
{
return _StringLength<CHAR>(pstr, umax);
}

UINT StringLength(LPCWSTR pstr, UINT umax)
{
return _StringLength<WCHAR>(pstr, umax);
}


//============
// Assignment
//============

template <class _dst_t, class _src_t> inline UINT _StringAssign(_dst_t** ppstr, UINT* psize, _src_t const* passign, UINT ucopy)
{
if(!ppstr)
	return 0;
UINT ulen=StringLength(passign, ucopy);
if(!ulen)
	return StringClear(ppstr, psize);
UINT usize=0;
if(psize)
	usize=*psize;
if(ulen+1!=usize)
	{
	if(*ppstr!=nullptr)
		Free(*ppstr);
	*ppstr=(_dst_t*)Alloc((ulen+1)*sizeof(_dst_t));
	usize=ulen+1;
	if(psize)
		*psize=usize;
	}
return StringCopy(*ppstr, usize, passign, ucopy);
}

UINT StringAssign(LPSTR* ppstr, UINT* psize, LPCSTR passign, UINT ulen)
{
return _StringAssign<CHAR, CHAR>(ppstr, psize, passign, ulen);
}

UINT StringAssign(LPSTR* ppstr, UINT* psize, LPCWSTR passign, UINT ulen)
{
return _StringAssign<CHAR, WCHAR>(ppstr, psize, passign, ulen);
}

UINT StringAssign(LPWSTR* ppstr, UINT* psize, LPCSTR passign, UINT ulen)
{
return _StringAssign<WCHAR, CHAR>(ppstr, psize, passign, ulen);
}

UINT StringAssign(LPWSTR* ppstr, UINT* psize, LPCWSTR passign, UINT ulen)
{
return _StringAssign<WCHAR, WCHAR>(ppstr, psize, passign, ulen);
}

template <class _dst_t, class _src_t> inline UINT _StringCopy(_dst_t* pdst, UINT usize, _src_t const* psrc, UINT ucopy)
{
ASSERT(pdst&&usize);
UINT uend=usize-1;
if(ucopy)
	uend=MIN(uend, ucopy);
if(!psrc)
	{
	pdst[0]=0;
	return 0;
	}
UINT upos=0;
for(; upos<uend; upos++)
	{
	if(psrc[upos]==0)
		break;
	CharAssign(pdst[upos], psrc[upos]);
	}
pdst[upos]=0;
return upos;
}

UINT StringCopy(LPSTR pdst, UINT usize, LPCSTR psrc, UINT ucopy)
{
return _StringCopy<CHAR, CHAR>(pdst, usize, psrc, ucopy);
}

UINT StringCopy(LPSTR pdst, UINT usize, LPCWSTR psrc, UINT ucopy)
{
return _StringCopy<CHAR, WCHAR>(pdst, usize, psrc, ucopy);
}

UINT StringCopy(LPWSTR pdst, UINT usize, LPCSTR psrc, UINT ucopy)
{
return _StringCopy<WCHAR, CHAR>(pdst, usize, psrc, ucopy);
}

UINT StringCopy(LPWSTR pdst, UINT usize, LPCWSTR psrc, UINT ucopy)
{
return _StringCopy<WCHAR, WCHAR>(pdst, usize, psrc, ucopy);
}


//==============
// Modification
//==============

template <class _str_t, class _append_t> inline UINT _StringAppend(_str_t** ppstr, UINT* psize, _append_t const* pappend, UINT ucopy)
{
_str_t* pstr=*ppstr;
UINT usize=0;
if(psize)
	usize=*psize;
UINT ulen=StringLength(pstr);
UINT uappendlen=StringLength(pappend, ucopy);
UINT unewlen=ulen+uappendlen;
if(unewlen+1>usize)
	{
	StringSetSize(ppstr, psize, unewlen+1);
	pstr=*ppstr;
	usize=unewlen+1;
	}
StringCopy(&pstr[ulen], usize-ulen, pappend, ucopy);
return unewlen;
}

UINT StringAppend(LPSTR* ppstr, UINT* psize, LPCSTR pappend, UINT ulen)
{
return _StringAppend<CHAR, CHAR>(ppstr, psize, pappend, ulen);
}

UINT StringAppend(LPSTR* ppstr, UINT* psize, LPCWSTR pappend, UINT ulen)
{
return _StringAppend<CHAR, WCHAR>(ppstr, psize, pappend, ulen);
}

UINT StringAppend(LPWSTR* ppstr, UINT* psize, LPCSTR pappend, UINT ulen)
{
return _StringAppend<WCHAR, CHAR>(ppstr, psize, pappend, ulen);
}

UINT StringAppend(LPWSTR* ppstr, UINT* psize, LPCWSTR pappend, UINT ulen)
{
return _StringAppend<WCHAR, WCHAR>(ppstr, psize, pappend, ulen);
}

template <class _str_t> inline UINT _StringClear(_str_t** ppstr, UINT* psize)
{
_str_t* pstr=*ppstr;
if(pstr!=nullptr)
	{
	Free(pstr);
	*ppstr=nullptr;
	}
if(psize)
	*psize=0;
return 0;
}

UINT StringClear(LPSTR* ppstr, UINT* psize)
{
return _StringClear<CHAR>(ppstr, psize);
}

UINT StringClear(LPWSTR* ppstr, UINT* psize)
{
return _StringClear<WCHAR>(ppstr, psize);
}

template <class _str_t, class _insert_t> inline UINT _StringInsert(_str_t* pstr, UINT usize, _insert_t const* pinsert, UINT upos, UINT ucopy)
{
UINT ulen=StringLength(pstr);
if(upos>ulen)
	return 0;
UINT uinsertlen=StringLength(pinsert, ucopy);
if(uinsertlen==0)
	return ulen;
UINT unewlen=ulen+uinsertlen;
if(unewlen+1>usize)
	return 0;
MoveMemory(&pstr[upos+uinsertlen], &pstr[upos], (ulen-upos+1)*sizeof(_str_t));
for(UINT u=0; u<uinsertlen; u++)
	CharAssign(pstr[upos++], pinsert[u]);
return unewlen;
}

template <class _str_t, class _insert_t> inline UINT _StringInsert(_str_t** ppstr, UINT* psize, _insert_t const* pinsert, UINT upos, UINT ucopy)
{
_str_t* pstr=*ppstr;
UINT ulen=StringLength(pstr);
if(upos>ulen)
	return 0;
UINT uinsertlen=StringLength(pinsert, ucopy);
if(uinsertlen==0)
	return ulen;
UINT usize=0;
if(psize)
	usize=*psize;
UINT unewlen=ulen+uinsertlen;
if(unewlen+1>usize)
	{
	usize=unewlen+1;
	_str_t* pnew=(_str_t*)Alloc(usize*sizeof(_str_t));
	StringCopy(pnew, usize, pstr, upos);
	StringCopy(&pnew[ulen], usize-ulen, pinsert, uinsertlen);
	if(ulen>upos)
		StringCopy(&pnew[upos+uinsertlen], usize-upos-uinsertlen, &pstr[upos], ulen-upos);
	Free(pstr);
	pstr=pnew;
	*ppstr=pstr;
	if(psize)
		*psize=usize;
	return uinsertlen;
	}
MoveMemory(&pstr[upos+uinsertlen], &pstr[upos], (ulen-upos)*sizeof(_str_t));
for(UINT u=0; u<uinsertlen; u++)
	CharAssign(pstr[upos++], pinsert[u]);
return unewlen;
}

UINT StringInsert(LPSTR pstr, UINT usize, LPCSTR pinsert, UINT upos, UINT ulen)
{
return _StringInsert<CHAR, CHAR>(pstr, usize, pinsert, upos, ulen);
}

UINT StringInsert(LPSTR pstr, UINT usize, LPCWSTR pinsert, UINT upos, UINT ulen)
{
return _StringInsert<CHAR, WCHAR>(pstr, usize, pinsert, upos, ulen);
}

UINT StringInsert(LPWSTR pstr, UINT usize, LPCSTR pinsert, UINT upos, UINT ulen)
{
return _StringInsert<WCHAR, CHAR>(pstr, usize, pinsert, upos, ulen);
}

UINT StringInsert(LPWSTR pstr, UINT usize, LPCWSTR pinsert, UINT upos, UINT ulen)
{
return _StringInsert<WCHAR, WCHAR>(pstr, usize, pinsert, upos, ulen);
}

UINT StringInsert(LPSTR* ppstr, UINT* psize, LPCSTR pinsert, UINT ustr, UINT ulen)
{
return _StringInsert<CHAR, CHAR>(ppstr, psize, pinsert, ustr, ulen);
}

UINT StringInsert(LPSTR* ppstr, UINT* psize, LPCWSTR pinsert, UINT ustr, UINT ulen)
{
return _StringInsert<CHAR, WCHAR>(ppstr, psize, pinsert, ustr, ulen);
}

UINT StringInsert(LPWSTR* ppstr, UINT* psize, LPCSTR pinsert, UINT ustr, UINT ulen)
{
return _StringInsert<WCHAR, CHAR>(ppstr, psize, pinsert, ustr, ulen);
}

UINT StringInsert(LPWSTR* ppstr, UINT* psize, LPCWSTR pinsert, UINT ustr, UINT ulen)
{
return _StringInsert<WCHAR, WCHAR>(ppstr, psize, pinsert, ustr, ulen);
}

template <class _str_t> inline UINT _StringLowerCase(_str_t* pstr, UINT ustart, UINT ufind)
{
UINT ulen=StringLength(pstr);
ASSERT(ustart<=ulen);
if(ustart>ulen)
	return ulen;
UINT uend=ulen;
if(ufind>0)
	uend=MIN(ustart+ufind, ulen);
for(UINT u=ustart; u<uend; u++)
	pstr[u]=CharToSmall(pstr[u]);
return ulen;
}

UINT StringLowerCase(LPSTR pstr, UINT ustart, UINT ulen)
{
return _StringLowerCase<CHAR>(pstr, ustart, ulen);
}

UINT StringLowerCase(LPWSTR pstr, UINT ustart, UINT ulen)
{
return _StringLowerCase<WCHAR>(pstr, ustart, ulen);
}

template <class _str_t> inline UINT _StringRemove(_str_t* pstr, UINT upos, UINT usize)
{
UINT ulen=StringLength(pstr);
if(!usize)
	return ulen;
if(upos>=ulen)
	return ulen;
UINT umove=(UINT)((ulen-upos-usize+1)*sizeof(_str_t));
MoveMemory(&pstr[upos], &pstr[upos+usize], umove);
return ulen-usize;
}

UINT StringRemove(LPSTR pstr, UINT ustr, UINT usize)
{
return _StringRemove<CHAR>(pstr, ustr, usize);
}

UINT StringRemove(LPWSTR pstr, UINT ustr, UINT usize)
{
return _StringRemove<WCHAR>(pstr, ustr, usize);
}

template <class _str_t, class _find_t> inline UINT _StringReplace(_str_t** ppstr, UINT* psize, _find_t const* pfind, _find_t const* pinsert, UINT ustart, UINT ufind, BOOL bcs, BOOL ball)
{
_str_t* pstr=*ppstr;
UINT ulen=StringLength(pstr);
if(ustart>=ulen)
	return ulen;
UINT ufindlen=StringLength(pfind);
if(ufindlen==0)
	return ulen;
UINT uinsertlen=StringLength(pinsert);
UINT usearchlen=ulen-ustart;
if(ufind>0)
	usearchlen=MIN(ufind, usearchlen);
UINT ucount=StringCount(&pstr[ustart], pfind, usearchlen, bcs);
if(!ucount)
	return ulen;
if(!ball)
	ucount=1;
INT idiflen=(INT)uinsertlen-ufindlen;
UINT unewlen=ulen+idiflen*ucount;
UINT unewsize=unewlen+1;
_str_t* pnew=(_str_t*)Alloc(unewsize*sizeof(_str_t));
StringCopy(pnew, ustart, pstr, ustart);
UINT ustr=ustart;
UINT unewpos=ustart;
for(UINT u=0; u<ucount; u++)
	{
	if(StringCompare(&pstr[ustr], pfind, ufindlen, bcs)==0)
		{
		StringCopy(&pnew[unewpos], uinsertlen+1, pinsert, uinsertlen);
		ustr+=ufindlen;
		unewpos+=uinsertlen;
		continue;
		}
	pnew[unewpos]=pstr[ustr];
	ustr++;
	unewpos++;
	}
StringCopy(&pnew[unewpos], unewsize-unewpos, &pstr[ustr], ulen-ustr);
pnew[unewlen]=0;
UINT usize=0;
if(psize)
	usize=*psize;
if(unewsize>usize)
	{
	Free(pstr);
	*ppstr=pnew;
	if(psize)
		*psize=unewsize;
	return unewlen;
	}
StringCopy(pstr, usize, pnew);
return unewlen;
}

UINT StringReplace(LPSTR* ppstr, UINT* psize, LPCSTR pfind, LPCSTR pinsert, UINT ustart, UINT ulen, BOOL bcs, BOOL ball)
{
return _StringReplace<CHAR, CHAR>(ppstr, psize, pfind, pinsert, ustart, ulen, bcs, ball);
}

UINT StringReplace(LPSTR* ppstr, UINT* psize, LPCWSTR pfind, LPCWSTR pinsert, UINT ustart, UINT ulen, BOOL bcs, BOOL ball)
{
return _StringReplace<CHAR, WCHAR>(ppstr, psize, pfind, pinsert, ustart, ulen, bcs, ball);
}

UINT StringReplace(LPWSTR* ppstr, UINT* psize, LPCSTR pfind, LPCSTR pinsert, UINT ustart, UINT ulen, BOOL bcs, BOOL ball)
{
return _StringReplace<WCHAR, CHAR>(ppstr, psize, pfind, pinsert, ustart, ulen, bcs, ball);
}

UINT StringReplace(LPWSTR* ppstr, UINT* psize, LPCWSTR pfind, LPCWSTR pinsert, UINT ustart, UINT ulen, BOOL bcs, BOOL ball)
{
return _StringReplace<WCHAR, WCHAR>(ppstr, psize, pfind, pinsert, ustart, ulen, bcs, ball);
}

template <class _str_t> inline VOID _StringSetSize(_str_t** ppstr, UINT* psize, UINT unewsize)
{
UINT usize=0;
if(psize)
	usize=*psize;
if(unewsize==usize)
	return;
if(unewsize==0)
	{
	StringClear(ppstr, psize);
	return;
	}
_str_t* pstr=*ppstr;
_str_t* pnew=(_str_t*)Alloc(unewsize*sizeof(_str_t));
if(pstr)
	{
	StringCopy(pnew, unewsize, pstr);
	pnew[unewsize-1]=0;
	Free(pstr);
	}
else
	{
	pnew[0]=0;
	}
*ppstr=pnew;
if(psize)
	*psize=unewsize;
}

VOID StringSetSize(LPSTR* ppstr, UINT* psize, UINT unewsize)
{
_StringSetSize<CHAR>(ppstr, psize, unewsize);
}

VOID StringSetSize(LPWSTR* ppstr, UINT* psize, UINT unewsize)
{
_StringSetSize<WCHAR>(ppstr, psize, unewsize);
}

template <class _str_t> inline UINT _StringUpperCase(_str_t* pstr, UINT ustart, UINT ufind)
{
UINT ulen=StringLength(pstr);
ASSERT(ustart<=ulen);
if(ustart>ulen)
	return ulen;
UINT uend=ulen;
if(ufind>0)
	uend=MIN(ustart+ufind, ulen);
for(UINT u=ustart; u<uend; u++)
	pstr[u]=CharToCapital(pstr[u]);
return ulen;
}

UINT StringUpperCase(LPSTR pstr, UINT ustart, UINT ulen)
{
return _StringLowerCase<CHAR>(pstr, ustart, ulen);
}

UINT StringUpperCase(LPWSTR pstr, UINT ustart, UINT ulen)
{
return _StringLowerCase<WCHAR>(pstr, ustart, ulen);
}


//=====================
// Formatting - Format
//=====================

enum class StringFlags: UINT
{
Left=1,
None=0,
Numeric=2,
Precision=4,
Signed=8,
Space=16,
Width=32,
Zero=64
};

enum class StringFormat
{
Char,
Double,
Float,
Hex,
Int,
None,
Percent,
String,
UInt,
WChar,
WString
};

template <class _fmt_t> UINT _StringGetFormat(_fmt_t const* pfmt, StringFormat& format, StringFlags& flags, UINT& uwidth, UINT& uprec)
{
if(!pfmt)
	return 0;
if(!CharEqual(pfmt[0], '%'))
	return 0;
if(pfmt[1]==0)
	{
	format=StringFormat::Percent;
	return 1;
	}
if(CharEqual(pfmt[1], '%'))
	{
	format=StringFormat::Percent;
	return 2;
	}
// flags
UINT ufmt=1;
for(; pfmt[ufmt]; ufmt++)
	{
	if(CharCompare(pfmt[ufmt], ' ')==0)
		{
		SetFlag(flags, StringFlags::Space);
		}
	else if(CharCompare(pfmt[ufmt], '+')==0)
		{
		SetFlag(flags, StringFlags::Signed);
		}
	else if(CharCompare(pfmt[ufmt], '-')==0)
		{
		SetFlag(flags, StringFlags::Left);
		}
	else if(CharCompare(pfmt[ufmt], '#')==0)
		{
		SetFlag(flags, StringFlags::Numeric);
		}
	else if(CharCompare(pfmt[ufmt], '0')==0)
		{
		if(GetFlag(flags, StringFlags::Zero))
			break;
		SetFlag(flags, StringFlags::Zero);
		}
	else
		{
		break;
		}
	}
// Width
if(CharEqual(pfmt[ufmt], '*'))
	{
	SetFlag(flags, StringFlags::Width);
	ufmt++;
	}
else
	{
	ufmt+=StringScanUInt(&pfmt[ufmt], 0, &uwidth);
	}
// Precision
if(CharEqual(pfmt[ufmt], '.'))
	{
	ufmt++;
	if(CharEqual(pfmt[ufmt], '*'))
		{
		SetFlag(flags, StringFlags::Precision);
		ufmt++;
		}
	else
		{
		UINT ulen=StringScanUInt(&pfmt[ufmt], 0, &uprec);
		if(ulen==0)
			uprec=0;
		ufmt+=ulen;
		}
	}
// Size
INT isize=0;
for(; pfmt[ufmt]; ufmt++)
	{
	if(CharEqual(pfmt[ufmt], 'h'))
		{
		isize--;
		}
	else if(CharEqual(pfmt[ufmt], 'l'))
		{
		isize++;
		}
	else
		{
		break;
		}
	}
// Type
CHAR ctype=0;
CharAssign(ctype, pfmt[ufmt]);
if(ctype==0)
	return ufmt;
switch(ctype)
	{
	case 'c':
		{
		switch(isize)
			{
			case 1:
				{
				format=StringFormat::WChar;
				break;
				}
			default:
				{
				format=StringFormat::Char;
				break;
				}
			}
		break;
		}
	case 'd':
		{
		format=StringFormat::Double;
		break;
		}
	case 'f':
		{
		format=StringFormat::Float;
		break;
		}
	case 'i':
		{
		format=StringFormat::Int;
		break;
		}
	case 's':
		{
		switch(isize)
			{
			case 1:
				{
				format=StringFormat::WString;
				break;
				}
			default:
				{
				format=StringFormat::String;
				break;
				}
			}
		break;
		}
	case 'u':
		{
		format=StringFormat::UInt;
		break;
		}
	case 'x':
		{
		format=StringFormat::Hex;
		break;
		}
	}
return ufmt+1;
}


//======================
// Formatting - Strings
//======================

template <class _str_t, class _char_t> inline UINT _StringPrintChar(_str_t* pstr, UINT usize, _char_t c)
{
if(usize)
	CharAssign(pstr[0], c);
return 1;
}

template <class _str_t, class _char_t> UINT _StringPrintChars(_str_t* pstr, UINT usize, _char_t c, UINT ucount)
{
if(usize)
	{
	usize=MIN(usize, ucount);
	for(UINT u=0; u<usize; u++)
		CharAssign(pstr[u], c);
	}
return ucount;
}

template <class _str_t, class _print_t> UINT _StringPrintString(_str_t* pstr, UINT usize, _print_t const* pprint)
{
if(!pprint)
	return 0;
UINT ustr=0;
for(UINT u=0; pprint[u]; u++)
	ustr+=_StringPrintChar(pstr? &pstr[ustr]: nullptr, usize>ustr? usize-ustr: 0, pprint[u]);
return ustr;
}

template <class _str_t, class _print_t> UINT _StringPrintString(_str_t* pstr, UINT usize, _print_t const* pprint, StringFlags flags, UINT uwidth)
{
if(!pprint)
	return 0;
UINT ulen=0;
if(uwidth>0)
	ulen=_StringPrintString((_str_t*)nullptr, 0, pprint);
UINT ustr=0;
if(ulen<uwidth)
	{
	if(!GetFlag(flags, StringFlags::Left))
		ustr+=_StringPrintChars(&pstr[ustr], usize>ustr? usize-ustr: 0, ' ', uwidth-ulen);
	}
ustr+=_StringPrintString(&pstr[ustr], usize>ustr? usize-ustr: 0, pprint);
if(ulen<uwidth)
	{
	if(GetFlag(flags, StringFlags::Left))
		ustr+=_StringPrintChars(&pstr[ustr], usize>ustr? usize-ustr: 0, ' ', uwidth-ulen);
	}
if(ustr<usize)
	pstr[ustr]=0;
return ustr;
}


//==========================
// Formatting - Hexadecimal
//==========================

template <class _str_t> UINT _StringPrintHex(_str_t* pstr, UINT usize, UINT64 u)
{
CHAR buf[20];
LPSTR pbuf=&buf[19];
*pbuf=0;
do
	{
	CHAR c=(CHAR)((u%16)+'0');
	if(c>'9')
		c=(CHAR)(c+7);
	*--pbuf=c;
	u/=16;
	}
while(u);
return _StringPrintString(pstr, usize, pbuf);
}

template <class _str_t> UINT _StringPrintHex(_str_t* pstr, UINT usize, UINT64 u, StringFlags flags, UINT uwidth)
{
UINT ulen=0;
if(uwidth>0)
	ulen=_StringPrintHex(pstr, 0, u, flags, 0);
UINT ustr=0;
if(ulen<uwidth)
	{
	if(!GetFlag(flags, StringFlags::Left)&&!GetFlag(flags, StringFlags::Zero))
		ustr+=_StringPrintChars(pstr, usize, ' ', uwidth-ulen);
	}
if(GetFlag(flags, StringFlags::Numeric))
	ustr+=_StringPrintString(&pstr[ustr], usize>ustr? usize-ustr: 0, "0x");
if(ulen<uwidth)
	{
	if(!GetFlag(flags, StringFlags::Left)&&GetFlag(flags, StringFlags::Zero))
		ustr+=_StringPrintChars(&pstr[ustr], usize>ustr? usize-ustr: 0, '0', uwidth-ulen);
	}
ustr+=_StringPrintHex(&pstr[ustr], usize>ustr? usize-ustr: 0, u);
if(ulen<uwidth)
	{
	if(GetFlag(flags, StringFlags::Left))
		_StringPrintChars(&pstr[ustr], usize>ustr? usize-ustr: 0, ' ', uwidth-ulen);
	}
if(ustr<usize)
	pstr[ustr]=0;
return ustr;
}


//================================
// Formatting - Unsigned Integers
//================================

template <class _str_t> UINT _StringPrintUInt(_str_t* pstr, UINT usize, UINT64 u)
{
CHAR buf[22];
LPSTR pbuf=&buf[21];
*pbuf=0;
do
	{
	*--pbuf=(CHAR)((u%10)+'0');
	u/=10;
	}
while(u);
return _StringPrintString(pstr, usize, pbuf);
}

template <class _str_t> UINT _StringPrintUInt(_str_t* pstr, UINT usize, UINT64 u, StringFlags flags, UINT uwidth)
{
UINT ulen=0;
if(uwidth>0)
	ulen=_StringPrintUInt(pstr, 0, u, flags, 0);
UINT ustr=0;
if(ulen<uwidth)
	{
	if(!GetFlag(flags, StringFlags::Left)&&!GetFlag(flags, StringFlags::Zero))
		ustr+=_StringPrintChars(pstr, usize, ' ', uwidth-ulen);
	}
if(GetFlag(flags, StringFlags::Signed))
	ustr+=_StringPrintChar(&pstr[ustr], usize>ustr? usize-ustr: 0, '+');
if(ulen<uwidth)
	{
	if(!GetFlag(flags, StringFlags::Left)&&GetFlag(flags, StringFlags::Zero))
		ustr+=_StringPrintChars(&pstr[ustr], usize>ustr? usize-ustr: 0, '0', uwidth-ulen);
	}
ustr+=_StringPrintUInt(&pstr[ustr], usize>ustr? usize-ustr: 0, u);
if(ulen<uwidth)
	{
	if(GetFlag(flags, StringFlags::Left))
		ustr+=_StringPrintChars(&pstr[ustr], usize>ustr? usize-ustr: 0, ' ', uwidth-ulen);
	}
if(ustr<usize)
	pstr[ustr]=0;
return ustr;
}


//=======================
// Formatting - Integers
//=======================

template <class _str_t> UINT _StringPrintInt(_str_t* pstr, UINT usize, INT64 i, StringFlags flags, UINT uwidth)
{
UINT ulen=0;
if(uwidth>0)
	ulen=_StringPrintInt(pstr, 0, i, flags, 0);
UINT ustr=0;
if(ulen<uwidth)
	{
	if(!GetFlag(flags, StringFlags::Left)&&!GetFlag(flags, StringFlags::Zero))
		ustr+=_StringPrintChars(&pstr[ustr], usize>ustr? usize-ustr: 0, ' ', uwidth-ulen);
	}
if(i<0)
	{
	ustr+=_StringPrintChar(&pstr[ustr], usize>ustr? usize-ustr: 0, '-');
	i*=-1;
	}
else if(GetFlag(flags, StringFlags::Signed))
	{
	ustr+=_StringPrintChar(&pstr[ustr], usize>ustr? usize-ustr: 0, '+');
	}
if(ulen<uwidth)
	{
	if(!GetFlag(flags, StringFlags::Left)&&GetFlag(flags, StringFlags::Zero))
		ustr+=_StringPrintChars(&pstr[ustr], usize>ustr? usize-ustr: 0, '0', uwidth-ulen);
	}
ustr+=_StringPrintUInt(&pstr[ustr], usize>ustr? usize-ustr: 0, i);
if(ulen<uwidth)
	{
	if(GetFlag(flags, StringFlags::Left))
		ustr+=_StringPrintChars(&pstr[ustr], usize>ustr? usize-ustr: 0, ' ', uwidth-ulen);
	}
if(ustr<usize)
	pstr[ustr]=0;
return ustr;
}


//=====================
// Formatting - Floats
//=====================

INT NormalizeDouble(DOUBLE& d, DOUBLE dmax, DOUBLE dmin)
{
if(d==0)
	return 0;
INT ex=0;
if(d>=dmax)
	{
	if(d>=1e256)
		{
		d/=1e256;
		ex+=256;
		}
	if(d>=1e128)
		{
		d/=1e128;
		ex+=128;
		}
	if(d>=1e64)
		{
		d/=1e64;
		ex+=64;
		}
	if(d>=1e32)
		{
		d/=1e32;
		ex+=32;
		}
	if(d>=1e16)
		{
		d/=1e16;
		ex+=16;
		}
	if(d>=1e8)
		{
		d/=1e8;
		ex+=8;
		}
	if(d>=1e4)
		{
		d/=1e4;
		ex+=4;
		}
	if(d>=1e2)
		{
		d/=1e2;
		ex+=2;
		}
	if(d>=1e1)
		{
		d/=1e1;
		ex+=1;
		}
	return ex;
	}
if(d<dmin)
	{
	if(d<1e-255)
		{
		d*=1e256;
		ex-=256;
		}
	if(d<1e-127)
		{
		d*=1e128;
		ex-=128;
		}
	if(d<1e-63)
		{
		d*=1e64;
		ex-=64;
		}
	if(d<1e-31)
		{
		d*=1e32;
		ex-=32;
		}
	if(d<1e-15)
		{
		d*=1e16;
		ex-=16;
		}
	if(d<1e-7)
		{
		d*=1e8;
		ex-=8;
		}
	if(d<1e-3)
		{
		d*=1e4;
		ex-=4;
		}
	if(d<1e-1)
		{
		d*=1e2;
		ex-=2;
		}
	if(d<1e0)
		{
		d*=1e1;
		ex-=1;
		}
	}
return ex;
}

VOID SplitDouble(DOUBLE d, UINT& integral, UINT& decimal, INT& ex, UINT& uwidth, UINT& uprec)
{
DOUBLE pmul[]={ 1e0, 1e1, 1e2, 1e3, 1e4, 1e5, 1e6, 1e7, 1e8, 1e9 };
DOUBLE pdiv[]={ 1e0, 1e-1, 1e-2, 1e-3, 1e-4, 1e-5 };
uwidth=MIN(uwidth, ARRAYSIZE(pmul)-1);
uprec=MIN(uprec, ARRAYSIZE(pdiv)-1);
ex=NormalizeDouble(d, pmul[uwidth], pdiv[uprec]);
integral=(UINT)d;
DOUBLE remainder=d-integral;
remainder*=pmul[uprec];
decimal=(UINT)remainder;
remainder-=decimal;
if(remainder>=0.5)
	{
	decimal++;
	if(decimal==1000000000)
		{
		integral++;
		decimal=0;
		if(integral>=pmul[uwidth])
			{
			ex++;
			integral/=10;
			}
		}
	}
}

template <class _str_t> UINT _StringPrintDouble(_str_t* pstr, UINT usize, DOUBLE d, StringFlags flags, UINT uwidth, UINT uprec)
{
UINT ustr=0;
if(isnan(d))
	{
	ustr+=_StringPrintString(pstr, usize, "nan");
	return ustr;
	}
if(d<0)
	{
	ustr+=_StringPrintChar(pstr, usize, '-');
	d*=-1;
	}
else if(GetFlag(flags, StringFlags::Signed))
	{
	ustr+=_StringPrintChar(pstr, usize, '+');
	}
if(isinf(d))
	{
	ustr+=_StringPrintString(&pstr[ustr], usize>ustr? usize-ustr: 0, "inf");
	return ustr;
	}
UINT integral=0;
UINT decimal=0;
INT exponent=0;
SplitDouble(d, integral, decimal, exponent, uwidth, uprec);
ustr+=_StringPrintUInt(&pstr[ustr], usize>ustr? usize-ustr: 0, integral);
CHAR buf[16];
LPSTR pbuf=&buf[15];
*pbuf=0;
INT idec=uprec;
for(; idec>1&&decimal%10==0; idec--)
	{
	if(GetFlag(flags, StringFlags::Zero))
		*--pbuf='0';
	decimal/=10;
	}
for(; idec>0; idec--)
	{
	*--pbuf=(CHAR)((decimal%10)+'0');
	decimal/=10;
	}
if(uprec)
	*--pbuf='.';
ustr+=_StringPrintString(&pstr[ustr], usize>ustr? usize-ustr: 0, pbuf);
if(exponent!=0||GetFlag(flags, StringFlags::Numeric))
	{
	ustr+=_StringPrintChar(&pstr[ustr], usize>ustr? usize-ustr: 0, 'e');
	if(exponent<0)
		{
		ustr+=_StringPrintChar(&pstr[ustr], usize>ustr? usize-ustr: 0, '-');
		exponent*=-1;
		}
	ustr+=_StringPrintUInt(&pstr[ustr], usize>ustr? usize-ustr: 0, exponent);
	}
if(ustr<usize)
	pstr[ustr]=0;
return ustr;
}


//============
// Formatting
//============

template <class _str_t, class _fmt_t> UINT _StringVPrint(_str_t* pstr, UINT usize, _fmt_t const* pformat, VariableArguments& args)
{
if(!pformat)
	return 0;
args.Begin();
UINT ustr=0;
for(UINT uformat=0; pformat[uformat]; )
	{
	if(ustr+1==usize)
		break;
	StringFormat format=StringFormat::None;
	StringFlags flags=StringFlags::None;
	UINT uwidth=-1;
	UINT uprec=-1;
	uformat+=_StringGetFormat(&pformat[uformat], format, flags, uwidth, uprec);
	if(format==StringFormat::None)
		{
		ustr+=_StringPrintChar(&pstr[ustr], usize>ustr? usize-ustr: 0, pformat[uformat]);
		uformat++;
		continue;
		}
	if(format==StringFormat::Percent)
		{
		ustr+=_StringPrintChar(&pstr[ustr], usize>ustr? usize-ustr: 0, '%');
		continue;
		}
	if(GetFlag(flags, StringFlags::Width))
		args.Get(uwidth);
	if(GetFlag(flags, StringFlags::Precision))
		args.Get(uprec);
	UINT ucopy=usize>ustr? usize-ustr: 0;
	switch(format)
		{
		case StringFormat::Char:
			{
			CHAR c=' ';
			args.Get(c);
			ustr+=_StringPrintChar(&pstr[ustr], ucopy, c);
			continue;
			}
		case StringFormat::Double:
			{
			DOUBLE d=0;
			args.Get(d);
			ustr+=_StringPrintDouble(&pstr[ustr], ucopy, d, flags, uwidth, uprec);
			continue;
			}
		case StringFormat::Float:
			{
			FLOAT f=0;
			args.Get(f);
			ustr+=_StringPrintDouble(&pstr[ustr], ucopy, f, flags, uwidth, uprec);
			continue;
			}
		case StringFormat::Hex:
			{
			UINT64 u=0;
			args.Get(u);
			ustr+=_StringPrintHex(&pstr[ustr], ucopy, u, flags, uwidth==(UINT)-1? 0: uwidth);
			continue;
			}
		case StringFormat::Int:
			{
			INT64 i=0;
			args.Get(i);
			ustr+=_StringPrintInt(&pstr[ustr], ucopy, i, flags, uwidth==(UINT)-1? 0: uwidth);
			continue;
			}
		case StringFormat::String:
			{
			LPCSTR p=nullptr;
			args.Get(p);
			ustr+=_StringPrintString(&pstr[ustr], ucopy, p, flags, uwidth==(UINT)-1? 0: uwidth);
			continue;
			}
		case StringFormat::UInt:
			{
			UINT64 u=0;
			args.Get(u);
			ustr+=_StringPrintUInt(&pstr[ustr], ucopy, u, flags, uwidth==(UINT)-1? 0: uwidth);
			continue;
			}
		case StringFormat::WChar:
			{
			WCHAR c=' ';
			args.Get(c);
			ustr+=_StringPrintChar(&pstr[ustr], ucopy, c);
			continue;
			}
		case StringFormat::WString:
			{
			LPCWSTR p=nullptr;
			args.Get(p);
			ustr+=_StringPrintString(&pstr[ustr], ucopy, p, flags, uwidth==(UINT)-1? 0: uwidth);
			continue;
			}
		default:
			continue;
		}
	}
if(ustr<usize)
	pstr[ustr]=0;
return ustr;
}

template <class _str_t, class _fmt_t> UINT _StringVPrint(_str_t** ppstr, UINT* psize, _fmt_t const* pformat, VariableArguments& args)
{
UINT ulen=StringVPrint((_str_t*)nullptr, 0, pformat, args);
if(ppstr)
	{
	if(*ppstr)
		{
		Free(*ppstr);
		*ppstr=nullptr;
		}
	if(ulen>0)
		{
		*ppstr=(_str_t*)Alloc((ulen+1)*sizeof(_str_t));
		ulen=StringVPrint(*ppstr, ulen+1, pformat, args);
		}
	}
if(psize)
	{
	if(ulen==0)
		{
		*psize=0;
		}
	else
		{
		*psize=ulen+1;
		}
	}
return ulen;
}

UINT StringVPrint(LPSTR pstr, UINT usize, LPCSTR pformat, VariableArguments& args)
{
return _StringVPrint(pstr, usize, pformat, args);
}

UINT StringVPrint(LPSTR pstr, UINT usize, LPCWSTR pformat, VariableArguments& args)
{
return _StringVPrint(pstr, usize, pformat, args);
}

UINT StringVPrint(LPSTR* ppstr, UINT* psize, LPCSTR pformat, VariableArguments& args)
{
return _StringVPrint(ppstr, psize, pformat, args);
}

UINT StringVPrint(LPSTR* ppstr, UINT* psize, LPCWSTR pformat, VariableArguments& args)
{
return _StringVPrint(ppstr, psize, pformat, args);
}

UINT StringVPrint(LPWSTR pstr, UINT usize, LPCSTR pformat, VariableArguments& args)
{
return _StringVPrint(pstr, usize, pformat, args);
}

UINT StringVPrint(LPWSTR pstr, UINT usize, LPCWSTR pformat, VariableArguments& args)
{
return _StringVPrint(pstr, usize, pformat, args);
}

UINT StringVPrint(LPWSTR* ppstr, UINT* psize, LPCSTR pformat, VariableArguments& args)
{
return _StringVPrint(ppstr, psize, pformat, args);
}

UINT StringVPrint(LPWSTR* ppstr, UINT* psize, LPCWSTR pformat, VariableArguments& args)
{
return _StringVPrint(ppstr, psize, pformat, args);
}


//==========
// Scanning
//==========

template <class _str_t, class _float_t> UINT _StringScanFloat(_str_t const* pstr, UINT ulen, _float_t* pfloat)
{
if(!pstr)
	return 0;
UINT ustr=0;
BOOL bneg=false;
if(CharEqual(pstr[ustr], '-'))
	{
	bneg=true;
	ustr++;
	}
if(!CharIsNumber(pstr[ustr]))
	return 0;
_float_t f=(_float_t)pstr[ustr]-'0';
for(ustr++; ustr<ulen; ustr++)
	{
	if(!CharIsNumber(pstr[ustr]))
		break;
	f*=10;
	f+=(_float_t)pstr[ustr]-'0';
	}
if(pstr[ustr]&&(ulen==0||ustr<ulen))
	{
	if(CharEqual(pstr[ustr], '.')||CharEqual(pstr[ustr], ','))
		{
		_float_t div=10;
		for(ustr++; pstr[ustr]&&(ulen==0||ustr<ulen); ustr++)
			{
			if(!CharIsNumber(pstr[ustr]))
				break;
			f+=((_float_t)pstr[ustr]-'0')/div;
			div*=10;
			}
		}
	}
if(pstr[ustr]&&(ulen==0||ustr<ulen))
	{
	if(CharEqual(pstr[ustr], 'E', false))
		{
		ustr++;
		if(ustr==ulen)
			return 0;
		INT ex=0;
		UINT uex=StringScanInt(&pstr[ustr], ulen>ustr? ulen-ustr: 0, &ex);
		if(uex==0)
			return 0;
		ustr+=uex;
		ex*=10;
		if(ex<0)
			{
			f/=(FLOAT)-ex;
			}
		else
			{
			f*=(FLOAT)ex;
			}
		}
	}
if(bneg)
	f*=-1;
if(pfloat)
	*pfloat=f;
return ustr;
}

template <class _str_t, class _int_t> UINT _StringScanInt(_str_t const* pstr, UINT ulen, _int_t* pint)
{
if(!pstr)
	return 0;
UINT ustr=0;
BOOL bneg=false;
if(CharEqual(pstr[ustr], '-'))
	{
	bneg=true;
	ustr++;
	}
if(ulen>0&&ustr==ulen)
	return 0;
if(!CharIsNumber(pstr[ustr]))
	return 0;
_int_t i=(_int_t)pstr[ustr]-'0';
for(ustr++; ulen==0||ustr<ulen; ustr++)
	{
	if(!CharIsNumber(pstr[ustr]))
		break;
	i*=10;
	i+=(_int_t)pstr[ustr]-'0';
	}
if(bneg)
	i*=-1;
if(pint)
	*pint=i;
return ustr;
}

template <class _str_t, class _buf_t, class _stop_t> UINT _StringScanString(_str_t const* pstr, UINT ulen, _buf_t* pbuf, UINT usize, _stop_t cstop)
{
if(!pstr)
	return 0;
UINT ustr=0;
for(; ulen==0||ustr<ulen; ustr++)
	{
	if(!pstr[ustr]||pstr[ustr]==cstop)
		break;
	if(ustr<usize)
		CharAssign(pbuf[ustr], pstr[ustr]);
	}
if(ustr<usize)
	pbuf[ustr]=0;
return ustr;
}

template <class _str_t, class _uint_t> UINT _StringScanUInt(_str_t const* pstr, UINT ulen, _uint_t* pint)
{
if(!pstr)
	return 0;
if(!CharIsNumber(pstr[0]))
	return 0;
UINT ustr=0;
BOOL bbinary=false;
BOOL bhex=false;
if(CharEqual(pstr[ustr], '0'))
	{
	if(ulen==0||ustr+1<ulen)
		{
		if(CharEqual(pstr[ustr+1], 'b'))
			{
			bbinary=true;
			ustr+=2;
			}
		if(CharEqual(pstr[ustr+1], 'x'))
			{
			bhex=true;
			ustr+=2;
			}
		}
	}
if(ulen>0&&ustr==ulen)
	return 0;
if(bbinary)
	{
	_uint_t u=0;
	UINT uend=ustr;
	for(; ulen==0||uend<ulen; uend++)
		{
		if(!CharIsBinary(pstr[uend]))
			break;
		u*=2;
		u+=(_uint_t)pstr[uend]-'0';
		}
	if(uend==ustr)
		return 0;
	if(pint)
		*pint=u;
	return uend;
	}
if(bhex)
	{
	_uint_t u=0;
	UINT uend=ustr;
	for(; ulen==0||uend<ulen; uend++)
		{
		if(!CharIsHex(pstr[uend]))
			break;
		_str_t c=(_str_t)(pstr[uend]-'0');
		if(c>9)
			c=(_str_t)(c-7);
		u*=16;
		u+=c;
		}
	if(uend==ustr)
		return 0;
	if(pint)
		*pint=u;
	return uend;
	}
_uint_t u=(_uint_t)pstr[ustr]-'0';
for(ustr++; ulen==0||ustr<ulen; ustr++)
	{
	if(!CharIsNumber(pstr[ustr]))
		break;
	u*=10;
	u+=(_uint_t)pstr[ustr]-'0';
	}
if(pint)
	*pint=u;
return ustr;
}

template <class _str_t, class _fmt_t> UINT _StringVScan(_str_t const* pstr, UINT ulen, _fmt_t const* pfmt, VariableArguments& args)
{
if(!pstr||!pfmt)
	return 0;
UINT ustr=0;
args.Begin();
UINT uarg=0;
for(UINT ufmt=0; pfmt[ufmt]; )
	{
	if(pstr[ustr]==0)
		return uarg;
	if(ulen>0&&ustr==ulen)
		return uarg;
	StringFormat format=StringFormat::None;
	StringFlags flags=StringFlags::None;
	UINT uwidth=-1;
	UINT uprec=-1;
	ufmt+=_StringGetFormat(&pfmt[ufmt], format, flags, uwidth, uprec);
	if(format==StringFormat::None)
		{
		if(pstr[ustr++]!=pfmt[ufmt++])
			return uarg;
		continue;
		}
	if(format==StringFormat::Percent)
		{
		if(pstr[ustr++]!='%')
			return uarg;
		continue;
		}
	switch(format)
		{
		case StringFormat::Double:
			{
			DOUBLE* p=nullptr;
			args.Get(p);
			if(!p)
				return uarg;
			UINT u=_StringScanFloat(&pstr[ustr], ulen>ustr? ulen-ustr: 0, p);
			if(!u)
				return uarg;
			uarg++;
			ustr+=u;
			continue;
			}
		case StringFormat::Float:
			{
			FLOAT* p=nullptr;
			args.Get(p);
			if(!p)
				return uarg;
			UINT u=_StringScanFloat(&pstr[ustr], ulen>ustr? ulen-ustr: 0, p);
			if(!u)
				return uarg;
			uarg++;
			ustr+=u;
			continue;
			}
		case StringFormat::Int:
			{
			INT* p=nullptr;
			args.Get(p);
			if(!p)
				return uarg;
			UINT u=_StringScanInt(&pstr[ustr], ulen>ustr? ulen-ustr: 0, p);
			if(!u)
				return uarg;
			uarg++;
			ustr+=u;
			continue;
			}
		case StringFormat::String:
			{
			LPSTR pbuf=nullptr;
			args.Get(pbuf);
			if(!pbuf)
				return uarg;
			UINT usize=0;
			args.Get(usize);
			if(!usize)
				return uarg;
			UINT u=_StringScanString(&pstr[ustr], ulen>ustr? ulen-ustr: 0, pbuf, usize, pfmt[ufmt]);
			if(!u)
				return uarg;
			uarg++;
			ustr+=u;
			continue;
			}
		case StringFormat::UInt:
			{
			UINT64 u=0;
			UINT len=_StringScanUInt(&pstr[ustr], ulen>ustr? ulen-ustr: 0, &u);
			if(!len)
				return uarg;
			UINT* p32=nullptr;
			args.TryGet(p32);
			if(p32)
				{
				args.MoveNext();
				if(u>MAX_UINT)
					return uarg;
				*p32=(UINT)u;
				uarg++;
				ustr+=len;
				continue;
				}
			UINT64* p64=nullptr;
			args.Get(p64);
			if(p64)
				{
				*p64=u;
				uarg++;
				ustr+=len;
				continue;
				}
			return uarg;
			}
		case StringFormat::WString:
			{
			LPWSTR pbuf=nullptr;
			args.Get(pbuf);
			if(!pbuf)
				return uarg;
			UINT usize=0;
			args.Get(usize);
			if(!usize)
				return uarg;
			UINT u=_StringScanString(&pstr[ustr], ulen>ustr? ulen-ustr: 0, pbuf, usize, pfmt[ufmt]);
			if(!u)
				return uarg;
			uarg++;
			ustr+=u;
			continue;
			}
		default:
			break;
		}
	}
return uarg;
}

UINT StringScanDouble(LPCSTR pstr, UINT ulen, DOUBLE* pvalue)
{
return _StringScanFloat(pstr, ulen, pvalue);
}

UINT StringScanDouble(LPCWSTR pstr, UINT ulen, DOUBLE* pvalue)
{
return _StringScanFloat(pstr, ulen, pvalue);
}

UINT StringScanFloat(LPCSTR pstr, UINT ulen, FLOAT* pvalue)
{
return _StringScanFloat(pstr, ulen, pvalue);
}

UINT StringScanFloat(LPCWSTR pstr, UINT ulen, FLOAT* pvalue)
{
return _StringScanFloat(pstr, ulen, pvalue);
}

UINT StringScanInt(LPCSTR pstr, UINT ulen, INT* pvalue)
{
return _StringScanInt(pstr, ulen, pvalue);
}

UINT StringScanInt(LPCWSTR pstr, UINT ulen, INT* pvalue)
{
return _StringScanInt(pstr, ulen, pvalue);
}

UINT StringScanUInt(LPCSTR pstr, UINT ulen, UINT* pvalue)
{
return _StringScanUInt(pstr, ulen, pvalue);
}

UINT StringScanUInt(LPCWSTR pstr, UINT ulen, UINT* pvalue)
{
return _StringScanUInt(pstr, ulen, pvalue);
}

UINT StringVScan(LPCSTR pstr, UINT ulen, LPCSTR pformat, VariableArguments& args)
{
return _StringVScan(pstr, ulen, pformat, args);
}

UINT StringVScan(LPCSTR pstr, UINT ulen, LPCWSTR pformat, VariableArguments& args)
{
return _StringVScan(pstr, ulen, pformat, args);
}

UINT StringVScan(LPCWSTR pstr, UINT ulen, LPCSTR pformat, VariableArguments& args)
{
return _StringVScan(pstr, ulen, pformat, args);
}

UINT StringVScan(LPCWSTR pstr, UINT ulen, LPCWSTR pformat, VariableArguments& args)
{
return _StringVScan(pstr, ulen, pformat, args);
}


//============
// Comparison
//============

template <class _char1_t, class _char2_t> inline INT _StringCompare(_char1_t const* pstr1, _char2_t const* pstr2, UINT ucmp, BOOL bcs)
{
UINT ulen1=StringLength(pstr1, ucmp);
UINT ulen2=StringLength(pstr2, ucmp);
if(!ulen1&&!ulen2)
	return 0;
if(!ulen1)
	return -1;
if(!ulen2)
	return 1;
UINT upos1=0;
UINT upos2=0;
for(; upos1<ulen1&&upos2<ulen2; )
	{
	if(upos1==upos2&&upos1>0)
		{
		if(pstr1[upos1]=='-'&&pstr2[upos2]=='-')
			{
			upos1++;
			upos2++;
			continue;
			}
		}
	DOUBLE d1=0;
	UINT udlen1=_StringScanFloat(&pstr1[upos1], ulen1-upos1, &d1);
	DOUBLE d2=0;
	UINT udlen2=_StringScanFloat(&pstr2[upos2], ulen2-upos2, &d2);
	if(udlen1==0)
		{
		if(udlen2==0)
			{
			INT icmp=CharCompare(pstr1[upos1], pstr2[upos2], bcs);
			if(icmp==0)
				{
				upos1++;
				upos2++;
				continue;
				}
			return icmp;
			}
		return -1;
		}
	if(udlen2==0)
		return 1;
	if(d1>d2)
		return 1;
	if(d2>d1)
		return -1;
	upos1+=udlen1;
	upos2+=udlen2;
	}
if(upos1==ulen1)
	{
	if(upos2==ulen2)
		return 0;
	return -1;
	}
return 1;
}

INT StringCompare(LPCSTR pstr1, LPCSTR pstr2, UINT ulen, BOOL bcs)
{
return _StringCompare<CHAR, CHAR>(pstr1, pstr2, ulen, bcs);
}

INT StringCompare(LPCSTR pstr1, LPCWSTR pstr2, UINT ulen, BOOL bcs)
{
return _StringCompare<CHAR, WCHAR>(pstr1, pstr2, ulen, bcs);
}

INT StringCompare(LPCWSTR pstr1, LPCSTR pstr2, UINT ulen, BOOL bcs)
{
return _StringCompare<WCHAR, CHAR>(pstr1, pstr2, ulen, bcs);
}

INT StringCompare(LPCWSTR pstr1, LPCWSTR pstr2, UINT ulen, BOOL bcs)
{
return _StringCompare<WCHAR, WCHAR>(pstr1, pstr2, ulen, bcs);
}
