//================
// StringHelper.h
//================

#pragma once


//=======
// Using
//=======

#include "VariableArguments.h"


//========
// Access
//========

BOOL StringContains(LPCSTR String, CHAR Find, UINT Start=0, UINT Length=0, BOOL CaseSensitive=true);
BOOL StringContains(LPCSTR String, WCHAR Find, UINT Start=0, UINT Length=0, BOOL CaseSensitive=true);
BOOL StringContains(LPCSTR String, LPCSTR Find, UINT Start=0, UINT Length=0, BOOL CaseSensitive=true);
BOOL StringContains(LPCSTR String, LPCWSTR Find, UINT Start=0, UINT Length=0, BOOL CaseSensitive=true);
BOOL StringContains(LPCWSTR String, CHAR Find, UINT Start=0, UINT Length=0, BOOL CaseSensitive=true);
BOOL StringContains(LPCWSTR String, WCHAR Find, UINT Start=0, UINT Length=0, BOOL CaseSensitive=true);
BOOL StringContains(LPCWSTR String, LPCSTR Find, UINT Start=0, UINT Length=0, BOOL CaseSensitive=true);
BOOL StringContains(LPCWSTR String, LPCWSTR Find, UINT Start=0, UINT Length=0, BOOL CaseSensitive=true);
UINT StringCount(LPCSTR String, LPCSTR Find, UINT Start=0, UINT Length=0, BOOL CaseSensitive=true);
UINT StringCount(LPCSTR String, LPCWSTR Find, UINT Start=0, UINT Length=0, BOOL CaseSensitive=true);
UINT StringCount(LPCWSTR String, LPCSTR Find, UINT Start=0, UINT Length=0, BOOL CaseSensitive=true);
UINT StringCount(LPCWSTR String, LPCWSTR Find, UINT Start=0, UINT Length=0, BOOL CaseSensitive=true);
BOOL StringFind(LPCSTR String, LPCSTR Find, UINT* Position=nullptr, UINT Length=0, BOOL CaseSensitive=true);
BOOL StringFind(LPCSTR String, LPCWSTR Find, UINT* Position=nullptr, UINT Length=0, BOOL CaseSensitive=true);
BOOL StringFind(LPCWSTR String, LPCSTR Find, UINT* Position=nullptr, UINT Length=0, BOOL CaseSensitive=true);
BOOL StringFind(LPCWSTR String, LPCWSTR Find, UINT* Position=nullptr, UINT Length=0, BOOL CaseSensitive=true);
inline BOOL StringIsSet(LPCSTR String) { return String&&String[0]; }
inline BOOL StringIsSet(LPCWSTR String) { return String&&String[0]; }
UINT StringLength(LPCSTR String, UINT Max=0);
UINT StringLength(LPCWSTR String, UINT Max=0);


//============
// Assignment
//============

UINT StringAssign(LPSTR* Value, UINT* Size, LPCSTR Assign, UINT Length=0);
UINT StringAssign(LPSTR* Value, UINT* Size, LPCWSTR Assign, UINT Length=0);
UINT StringAssign(LPWSTR* Value, UINT* Size, LPCSTR Assign, UINT Length=0);
UINT StringAssign(LPWSTR* Value, UINT* Size, LPCWSTR Assign, UINT Length=0);
UINT StringCopy(LPSTR Destination, UINT Size, LPCSTR Source, UINT Length=0);
UINT StringCopy(LPSTR Destination, UINT Size, LPCWSTR Source, UINT Length=0);
UINT StringCopy(LPWSTR Destination, UINT Size, LPCSTR Source, UINT Length=0);
UINT StringCopy(LPWSTR Destination, UINT Size, LPCWSTR Source, UINT Length=0);


//==============
// Modification
//==============

UINT StringAppend(LPSTR* Value, UINT* Size, LPCSTR Append, UINT Length=0);
UINT StringAppend(LPSTR* Value, UINT* Size, LPCWSTR Append, UINT Length=0);
UINT StringAppend(LPWSTR* Value, UINT* Size, LPCSTR Append, UINT Length=0);
UINT StringAppend(LPWSTR* Value, UINT* Size, LPCWSTR Append, UINT Length=0);
UINT StringClear(LPSTR* Buffer, UINT* Size);
UINT StringClear(LPWSTR* Buffer, UINT* Size);
UINT StringInsert(LPSTR Value, UINT Size, LPCSTR Insert, UINT Position, UINT Length=0);
UINT StringInsert(LPSTR Value, UINT Size, LPCWSTR Insert, UINT Position, UINT Length=0);
UINT StringInsert(LPWSTR Value, UINT Size, LPCSTR Insert, UINT Position, UINT Length=0);
UINT StringInsert(LPWSTR Value, UINT Size, LPCWSTR Insert, UINT Position, UINT Length=0);
UINT StringInsert(LPSTR* Value, UINT* Size, LPCSTR Insert, UINT Position, UINT Length=0);
UINT StringInsert(LPSTR* Value, UINT* Size, LPCWSTR Insert, UINT Position, UINT Length=0);
UINT StringInsert(LPWSTR* Value, UINT* Size, LPCSTR Insert, UINT Position, UINT Length=0);
UINT StringInsert(LPWSTR* Value, UINT* Size, LPCWSTR Insert, UINT Position, UINT Length=0);
UINT StringLowerCase(LPSTR Value, UINT Start=0, UINT Length=0);
UINT StringLowerCase(LPWSTR Value, UINT Start=0, UINT Length=0);
UINT StringRemove(LPSTR Value, UINT Position, UINT Size);
UINT StringRemove(LPWSTR Value, UINT Position, UINT Size);
UINT StringReplace(LPSTR* Value, UINT* Size, LPCSTR Find, LPCSTR Insert, UINT Start=0, UINT Length=0, BOOL CaseSensitive=true, BOOL All=false);
UINT StringReplace(LPSTR* Value, UINT* Size, LPCWSTR Find, LPCWSTR Insert, UINT Start=0, UINT Length=0, BOOL CaseSensitive=true, BOOL All=false);
UINT StringReplace(LPWSTR* Value, UINT* Size, LPCSTR Find, LPCSTR Insert, UINT Start=0, UINT Length=0, BOOL CaseSensitive=true, BOOL All=false);
UINT StringReplace(LPWSTR* Value, UINT* Size, LPCWSTR Find, LPCWSTR Insert, UINT Start=0, UINT Length=0, BOOL CaseSensitive=true, BOOL All=false);
VOID StringSetSize(LPSTR* Value, UINT* Size, UINT NewSize);
VOID StringSetSize(LPWSTR* Value, UINT* Size, UINT NewSize);
UINT StringUpperCase(LPSTR Value, UINT Start=0, UINT Length=0);
UINT StringUpperCase(LPWSTR Value, UINT Start=0, UINT Length=0);


//============
// Formatting
//============

template <class _str_t, class _fmt_t, class... _args_t>
inline UINT StringPrint(_str_t* Buffer, UINT Size, _fmt_t const* Format, _args_t... Arguments)
{
Unknown pargs[]={ Arguments... };
VariableArguments args(pargs, ARRAYSIZE(pargs));
return StringVPrint(Buffer, Size, Format, args);
}

template <class _str_t, class _fmt_t, class... _args_t>
inline UINT StringPrint(_str_t** Buffer, UINT* Size, _fmt_t const* Format, _args_t... Arguments)
{
Unknown pargs[]={ Arguments... };
VariableArguments args(pargs, ARRAYSIZE(pargs));
return StringVPrint(Buffer, Size, Format, args);
}

UINT StringVPrint(LPSTR Buffer, UINT Size, LPCSTR Format, VariableArguments& Arguments);
UINT StringVPrint(LPSTR Buffer, UINT Size, LPCWSTR Format, VariableArguments& Arguments);
UINT StringVPrint(LPSTR* Buffer, UINT* Size, LPCSTR Format, VariableArguments& Arguments);
UINT StringVPrint(LPSTR* Buffer, UINT* Size, LPCWSTR Format, VariableArguments& Arguments);
UINT StringVPrint(LPWSTR Buffer, UINT Size, LPCSTR Format, VariableArguments& Arguments);
UINT StringVPrint(LPWSTR Buffer, UINT Size, LPCWSTR Format, VariableArguments& Arguments);
UINT StringVPrint(LPWSTR* Buffer, UINT* Size, LPCSTR Format, VariableArguments& Arguments);
UINT StringVPrint(LPWSTR* Buffer, UINT* Size, LPCWSTR Format, VariableArguments& Arguments);


//==========
// Scanning
//==========

template <class _str_t, class _fmt_t, class... _args_t>
inline UINT StringScan(_str_t const* Buffer, _fmt_t const* Format, _args_t... Arguments)
{
Unknown pargs[]={ Arguments... };
VariableArguments args(pargs, ARRAYSIZE(pargs));
return StringVScan(Buffer, 0, Format, args);
}

template <class _str_t, class _fmt_t, class... _args_t>
inline UINT StringScan(UINT Length, _str_t const* Buffer, _fmt_t const* Format, _args_t... Arguments)
{
Unknown pargs[]={ Arguments... };
VariableArguments args(pargs, ARRAYSIZE(pargs));
return StringVScan(Buffer, Length, Format, args);
}

UINT StringScanDouble(LPCSTR String, UINT Length, DOUBLE* Value);
UINT StringScanDouble(LPCWSTR String, UINT Length, DOUBLE* Value);
UINT StringScanFloat(LPCSTR String, UINT Length, FLOAT* Value);
UINT StringScanFloat(LPCWSTR String, UINT Length, FLOAT* Value);
UINT StringScanInt(LPCSTR String, UINT Length, INT* Value);
UINT StringScanInt(LPCWSTR String, UINT Length, INT* Value);
UINT StringScanUInt(LPCSTR String, UINT Length, UINT* Value);
UINT StringScanUInt(LPCWSTR String, UINT Length, UINT* Value);
UINT StringVScan(LPCSTR String, UINT Length, LPCSTR Format, VariableArguments& Arguments);
UINT StringVScan(LPCSTR String, UINT Length, LPCWSTR Format, VariableArguments& Arguments);
UINT StringVScan(LPCWSTR String, UINT Length, LPCSTR Format, VariableArguments& Arguments);
UINT StringVScan(LPCWSTR String, UINT Length, LPCWSTR Format, VariableArguments& Arguments);


//============
// Comparison
//============

INT StringCompare(LPCSTR Value1, LPCSTR Value2, UINT Length=0, BOOL CaseSensitive=true);
INT StringCompare(LPCSTR Value1, LPCWSTR Value2, UINT Length=0, BOOL CaseSensitive=true);
INT StringCompare(LPCWSTR Value1, LPCSTR Value2, UINT Length=0, BOOL CaseSensitive=true);
INT StringCompare(LPCWSTR Value1, LPCWSTR Value2, UINT Length=0, BOOL CaseSensitive=true);
