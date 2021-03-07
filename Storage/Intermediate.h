//================
// Intermediate.h
//================

#pragma once


//=======
// Using
//=======

#include "Clusters/list.hpp"
#include "Container.h"


//===========
// Namespace
//===========

namespace Storage {


//==============
// Intermediate
//==============

class Intermediate: public Container
{
public:
	// Con-/Destructors
	Intermediate();

	// Access
	SIZE_T Available()override;
	FileSize GetSize()override;
	SIZE_T Read(VOID* Buffer, SIZE_T Size)override;
	BOOL Seek(UINT64 Position)override;

	// Modification
	VOID Flush()override;
	SIZE_T Write(VOID const* Buffer, SIZE_T Size)override;

private:
	// Common
	Clusters::list<BYTE, 64> cList;
	SIZE_T uPosition;
};

}