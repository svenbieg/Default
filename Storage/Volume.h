//==========
// Volume.h
//==========

#pragma once


//===========
// Namespace
//===========

namespace Storage {


//========
// Volume
//========

class Volume: public Object
{
public:
	// Common
	virtual UINT GetBlockSize()=0;
	virtual FILE_SIZE GetSize()=0;
	virtual SIZE_T Read(FILE_SIZE Offset, VOID* Buffer, SIZE_T Size)=0;
	virtual BOOL SetSize(FILE_SIZE Size)=0;
	virtual SIZE_T Write(FILE_SIZE Offset, VOID const* Buffer, SIZE_T Size)=0;
};

}