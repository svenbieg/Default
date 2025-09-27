//==============
// CharHelper.h
//==============

#pragma once


//=======
// Using
//=======

#include "Storage/Streams/InputStream.h"
#include "Storage/Streams/OutputStream.h"
#include "TypeHelper.h"


//============
// Characters
//============

namespace Ansi
{
constexpr CHAR AE='\xC4';
constexpr CHAR ae='\xE4';
constexpr CHAR Average='\xD8';
constexpr CHAR Degree='\xB0';
constexpr CHAR Enumeration='\x95';
constexpr CHAR OE='\xD6';
constexpr CHAR oe='\xF6';
constexpr CHAR UE='\xDC';
constexpr CHAR ue='\xFC';
}

#ifdef _UNICODE
namespace Chars
{
constexpr WCHAR AE=L'\x00C4';
constexpr WCHAR ae=L'\x00E4';
constexpr WCHAR Average=L'\x00D8';
constexpr WCHAR Degree=L'\x00B0';
constexpr WCHAR Enumeration=L'\x2022';
constexpr WCHAR OE=L'\x00D6';
constexpr WCHAR oe=L'\x00F6';
constexpr WCHAR UE=L'\x00DC';
constexpr WCHAR ue=L'\x00FC';
}
#else
namespace Chars
{
constexpr CHAR AE='\xC4';
constexpr CHAR ae='\xE4';
constexpr CHAR Average='\xD8';
constexpr CHAR Degree='\xB0';
constexpr CHAR Enumeration='\x95';
constexpr CHAR OE='\xD6';
constexpr CHAR oe='\xF6';
constexpr CHAR UE='\xDC';
constexpr CHAR ue='\xFC';
}
#endif

namespace Unicode
{
constexpr WCHAR AE=L'\x00C4';
constexpr WCHAR ae=L'\x00E4';
constexpr WCHAR Average=L'\x00D8';
constexpr WCHAR Degree=L'\x00B0';
constexpr WCHAR Enumeration=L'\x2022';
constexpr WCHAR OE=L'\x00D6';
constexpr WCHAR oe=L'\x00F6';
constexpr WCHAR UE=L'\x00DC';
constexpr WCHAR ue=L'\x00FC';
}


//=============
// Char-Helper
//=============

class CharHelper
{
public:
	// Using
	using InputStream=Storage::Streams::InputStream;
	using OutputStream=Storage::Streams::OutputStream;

	// Common
	static INT Compare(CHAR Char1, CHAR Char2, BOOL CaseSensitive=true);
	static INT Compare(WCHAR Char1, WCHAR Char2, BOOL CaseSensitive=true);
	static INT Compare(CHAR Char1, WCHAR Char2, BOOL CaseSensitive=true);
	static INT Compare(WCHAR Char1, CHAR Char2, BOOL CaseSensitive=true);
	static BOOL Equal(CHAR Char1, CHAR Char2, BOOL CaseSensitive=true);
	static BOOL Equal(CHAR Char1, WCHAR Char2, BOOL CaseSensitive=true);
	static BOOL Equal(WCHAR Char1, CHAR Char2, BOOL CaseSensitive=true);
	static BOOL Equal(WCHAR Char1, WCHAR Char2, BOOL CaseSensitive=true);
	static BOOL Equal(CHAR Char1, LPCSTR Chars, BOOL CaseSensitive=true);
	static BOOL Equal(WCHAR Char1, LPCSTR Chars, BOOL CaseSensitive=true);
	static BOOL Equal(WCHAR Char1, LPCWSTR Chars, BOOL CaseSensitive=true);
	static BOOL IsAlpha(CHAR Char);
	static BOOL IsAlpha(WCHAR Char);
	static BOOL IsBreak(CHAR Char);
	static BOOL IsBreak(WCHAR Char);
	static BOOL IsCapital(CHAR Char);
	static BOOL IsCapital(WCHAR Char);
	static inline BOOL IsDigit(CHAR Char, UINT Base=10) { return ToDigit(Char, nullptr, Base); }
	static inline BOOL IsDigit(WCHAR Char, UINT Base=10) { return ToDigit(Char, nullptr, Base); }
	static BOOL IsPrintable(CHAR Char);
	static BOOL IsPrintable(WCHAR Char);
	static BOOL IsSmall(CHAR Char);
	static BOOL IsSmall(WCHAR Char);
	static BOOL IsSpecial(CHAR Char);
	static BOOL IsSpecial(WCHAR Char);
	static UINT ReadAnsi(InputStream* Stream, CHAR* Char);
	static UINT ReadAnsi(InputStream* Stream, WCHAR* Char);
	static UINT ReadUnicode(InputStream* Stream, CHAR* Char);
	static UINT ReadUnicode(InputStream* Stream, WCHAR* Char);
	static UINT ReadUtf8(InputStream* Stream, CHAR* Char);
	static UINT ReadUtf8(InputStream* Stream, WCHAR* Char);
	static CHAR ToAnsi(WCHAR Char);
	template<class _dst_t> static _dst_t ToCapital(CHAR Char) {}
	template<> static inline CHAR ToCapital(CHAR Char) { return ToCapitalAnsi(Char); }
	template<> static inline WCHAR ToCapital(CHAR Char) { return ToCapitalUnicode(Char); }
	template<class _dst_t> static _dst_t ToCapital(WCHAR Char) {}
	template<> static inline CHAR ToCapital(WCHAR Char) { return ToCapitalAnsi(Char); }
	template<> static inline WCHAR ToCapital(WCHAR Char) { return ToCapitalUnicode(Char); }
	static CHAR ToCapitalAnsi(CHAR Char);
	static CHAR ToCapitalAnsi(WCHAR Char);
	static WCHAR ToCapitalUnicode(CHAR Char);
	static WCHAR ToCapitalUnicode(WCHAR Char);
	template<class _dst_t> static _dst_t ToChar(CHAR Char) {}
	template<> static inline CHAR ToChar(CHAR Char) { return Char; }
	template<> static inline WCHAR ToChar(CHAR Char) { return ToUnicode(Char); }
	template<class _dst_t> static _dst_t ToChar(WCHAR Char) {}
	template<> static inline CHAR ToChar(WCHAR Char) { return ToAnsi(Char); }
	template<> static inline WCHAR ToChar(WCHAR Char) { return Char; }
	static BOOL ToDigit(CHAR Char, UINT* Digit, UINT Base=10);
	static BOOL ToDigit(WCHAR Char, UINT* Digit, UINT Base=10);
	template<class _dst_t> static _dst_t ToSmall(CHAR Char) {}
	template<> static inline CHAR ToSmall(CHAR Char) { return ToSmallAnsi(Char); }
	template<> static inline WCHAR ToSmall(CHAR Char) { return ToSmallUnicode(Char); }
	template<class _dst_t> static _dst_t ToSmall(WCHAR Char) {}
	template<> static inline CHAR ToSmall(WCHAR Char) { return ToSmallAnsi(Char); }
	template<> static inline WCHAR ToSmall(WCHAR Char) { return ToSmallUnicode(Char); }
	static CHAR ToSmallAnsi(CHAR Char);
	static CHAR ToSmallAnsi(WCHAR Char);
	static WCHAR ToSmallUnicode(CHAR Char);
	static WCHAR ToSmallUnicode(WCHAR Char);
	static WCHAR ToUnicode(CHAR Char);
	static UINT WriteAnsi(OutputStream* Stream, CHAR Char);
	static UINT WriteAnsi(OutputStream* Stream, WCHAR Char);
	static UINT WriteUnicode(OutputStream* Stream, CHAR Char);
	static UINT WriteUnicode(OutputStream* Stream, WCHAR Char);
	static UINT WriteUtf8(OutputStream* Stream, CHAR Char);
	static UINT WriteUtf8(OutputStream* Stream, WCHAR Char);
};
