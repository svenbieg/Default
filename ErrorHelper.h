//===============
// ErrorHelper.h
//===============

#pragma once


//=======
// Using
//=======

#include "StringHelper.h"


//========
// Common
//========

VOID Abort(LPCSTR Message=nullptr);

template <class... _args_t> VOID Abort(LPCSTR Format, _args_t... Arguments)
{
CHAR pmsg[256];
Unknown punknown[]={ Arguments... };
VariableArguments args(punknown, ARRAYSIZE(punknown));
StringVPrint(pmsg, 256, Format, args);
Abort(pmsg);
}


//=============
// Debug-Print
//=============

#ifdef _DEBUG

VOID DebugPrint(LPCSTR Message);

template <class... _args_t> VOID DebugPrint(LPCSTR Format, _args_t... Arguments)
{
CHAR pmsg[256];
Unknown punknown[]={ Arguments... };
VariableArguments args(punknown, ARRAYSIZE(punknown));
StringVPrint(pmsg, 256, Format, args);
DebugPrint(pmsg);
}

#else

#define DebugPrint(...)

#endif


//===========
// Assertion
//===========

#undef ASSERT
#ifdef _DEBUG
#define ASSERT(Condition) if(!(Condition))Abort("%s:%u ASSERT\n", (LPCSTR)__FILE__, (UINT)__LINE__)
#else
#define ASSERT(Condition)
#endif
