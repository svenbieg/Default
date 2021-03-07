//=================
// ErrorHelper.cpp
//=================

#include "pch.h"


//=======
// Using
//=======

#include <stdio.h>
#include <stdlib.h>


//========
// Common
//========

VOID Abort(LPCSTR pmsg)
{
if(pmsg)
	{
	DebugPrint(pmsg);
	}
Sleep(100);
abort();
}


//=============
// Debug-Print
//=============

#ifdef _DEBUG

VOID DebugPrint(LPCSTR pmsg)
{
fputs(pmsg, stdout);
}

#endif
