//==========
// Volume.h
//==========

#pragma once


//=======
// Using
//=======

#include "Storage/Seekable.h"


//===========
// Namespace
//===========

namespace Storage {


//========
// Volume
//========

class Volume: public Seekable
{
public:
	// Common
	virtual UINT GetBlockSize()=0;
	virtual SIZE_T Read(FILE_SIZE Position, VOID* Buffer, SIZE_T Size)=0;
	virtual SIZE_T Write(FILE_SIZE Position, VOID const* Buffer, SIZE_T Size)=0;
};

}