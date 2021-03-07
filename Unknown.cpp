//=============
// Unknown.cpp
//=============

#include "pch.h"


//==================
// Con-/Destructors
//==================

Unknown::Unknown():
uType(UnknownType::None)
{}

Unknown::Unknown(Unknown const& unknown):
uType(unknown.uType)
{
CopyMemory(pBuffer, unknown.pBuffer, 8);
}
