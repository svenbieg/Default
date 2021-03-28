//================
// MemoryHelper.h
//================

#pragma once


//========
// Macros
//========

#ifndef ARRAYSIZE
#define ARRAYSIZE(a) (sizeof(a)/sizeof((a)[0]))
#endif

#define MIN(a, b) ((a)<(b)? a: b)
#define MAX(a, b) ((a)>(b)? a: b)

#define OFFSETOF(type, element) ((SIZE_T)&(((type*)nullptr)->element))


//============
// Addressing
//============

#define ALIGN(a) __declspec(align(a))

template <class S>
inline S BlockAlign(S Size, UINT BlockSize)
{
if(Size%BlockSize)
	return Size+(BlockSize-(Size%BlockSize));
return Size;
}


//=======
// Flags
//=======

#undef ClearFlag
#undef SetFlag

template <class _flags_t, class _flag_t> inline VOID ClearFlag(_flags_t& Flags, _flag_t Flag) { UINT uflags=(UINT)Flags; UINT uflag=(UINT)Flag; uflags&=~uflag; Flags=(_flags_t)uflags; }
template <class _flags_t, class _flag_t> inline BOOL GetFlag(_flags_t const& Flags, _flag_t Flag) { UINT uflags=(UINT)Flags; UINT uflag=(UINT)Flag; return (uflags&uflag)>0; }
template <class _flags_t, class _flag_t> inline VOID SetFlag(_flags_t& Flags, _flag_t Flag) { UINT uflags=(UINT)Flags; UINT uflag=(UINT)Flag; uflags|=uflag; Flags=(_flags_t)uflags; }
template <class _flags_t, class _flag_t> inline VOID SetFlag(_flags_t& Flags, _flag_t Flag, BOOL Set) { Set? SetFlag(Flags, Flag): ClearFlag(Flags, Flag); }


//========
// Common
//========

#undef CopyMemory
#undef FillMemory
#undef MoveMemory
#undef ZeroMemory

INT CompareMemory(const VOID* Buffer1, const VOID* Buffer2, SIZE_T Size);
VOID CopyMemory(VOID* Destination, const VOID* Source, SIZE_T Size);
VOID FillMemory(VOID* Destination, SIZE_T Size, UINT Value);
VOID MoveMemory(VOID* Destination, const VOID* Source, SIZE_T Size);
VOID SetMemory(VOID* Destination, INT Value, SIZE_T Size);
VOID ZeroMemory(VOID* Destination, SIZE_T Size);


//===============
// Little Endian
//===============

template <class _value_t> _value_t Reverse(_value_t Value)
{
auto pvalue=(BYTE*)&Value;
_value_t retval=0;
auto pretval=(BYTE*)&retval;
for(UINT u=0; u<sizeof(_value_t); u++)
	pretval[u]=pvalue[sizeof(_value_t)-u-1];
return retval;
}
