//==============
// CharHelper.h
//==============

#pragma once


//============
// Characters
//============

enum class Chars: BYTE
{
Average=0xD8,
Degree=0xB0
};


//========
// Common
//========

BOOL CharIsAlpha(CHAR Char);
BOOL CharIsAlpha(WCHAR Char);
BOOL CharIsBinary(CHAR Char);
BOOL CharIsBinary(WCHAR Char);
BOOL CharIsBreak(CHAR Char);
BOOL CharIsBreak(WCHAR Char);
BOOL CharIsCapital(CHAR Char);
BOOL CharIsCapital(WCHAR Char);
BOOL CharIsHex(CHAR Char);
BOOL CharIsHex(WCHAR Char);
BOOL CharIsNumber(CHAR Char);
BOOL CharIsNumber(WCHAR Char);
BOOL CharIsPrintable(CHAR Char);
BOOL CharIsPrintable(WCHAR Char);
BOOL CharIsSmall(CHAR Char);
BOOL CharIsSmall(WCHAR Char);
BOOL CharIsSpecial(CHAR Char);
BOOL CharIsSpecial(WCHAR Char);


//============
// Conversion
//============

inline CHAR CharToAnsi(WCHAR Char) { return (CHAR)Char; }
CHAR CharToCapital(CHAR Char);
WCHAR CharToCapital(WCHAR Char);
BYTE CharToHex(CHAR Char);
BYTE CharToHex(WCHAR Char);
CHAR CharToSmall(CHAR Char);
WCHAR CharToSmall(WCHAR Char);
inline TCHAR CharToTChar(CHAR Char) { return Char; }
inline TCHAR CharToTChar(WCHAR Char) { return (CHAR)Char; }
inline WCHAR CharToUnicode(CHAR Char) { return Char; }


//============
// Comparison
//============

INT CharCompare(CHAR Char1, CHAR Char2, BOOL CaseSensitive=true);
INT CharCompare(WCHAR Char1, WCHAR Char2, BOOL CaseSensitive=true);
inline INT CharCompare(CHAR Char1, WCHAR Char2, BOOL CaseSensitive=true) { return CharCompare(CharToUnicode(Char1), Char2, CaseSensitive); }
inline INT CharCompare(WCHAR Char1, CHAR Char2, BOOL CaseSensitive=true) { return CharCompare(Char1, CharToUnicode(Char2), CaseSensitive); }
inline BOOL CharEqual(CHAR Char1, CHAR Char2) { return Char1==Char2; }
inline BOOL CharEqual(WCHAR Char1, WCHAR Char2) { return Char1==Char2; }
inline BOOL CharEqual(CHAR Char1, WCHAR Char2) { return CharEqual(CharToUnicode(Char1), Char2); }
inline BOOL CharEqual(WCHAR Char1, CHAR Char2) { return CharEqual(Char1, CharToUnicode(Char2)); }
BOOL CharEqual(CHAR Char1, CHAR Char2, BOOL CaseSensitive);
BOOL CharEqual(WCHAR Char1, WCHAR Char2, BOOL CaseSensitive);
inline BOOL CharEqual(CHAR Char1, WCHAR Char2, BOOL CaseSensitive) { return CharEqual(CharToUnicode(Char1), Char2, CaseSensitive); }
inline BOOL CharEqual(WCHAR Char1, CHAR Char2, BOOL CaseSensitive) { return CharEqual(Char1, CharToUnicode(Char2), CaseSensitive); }


//============
// Assignment
//============

inline VOID CharAssign(CHAR& Destination, CHAR Char) { Destination=Char; }
inline VOID CharAssign(CHAR& Destination, WCHAR Char) { Destination=CharToAnsi(Char); }
inline VOID CharAssign(WCHAR& Destination, CHAR Char) { Destination=CharToUnicode(Char); }
inline VOID CharAssign(WCHAR& Destination, WCHAR Char) { Destination=Char; }
