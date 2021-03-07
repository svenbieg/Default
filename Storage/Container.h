//=============
// Container.h
//=============

#pragma once


//=======
// Using
//=======

#include "Storage/Streams/RandomAccessStream.h"
#include "FileSize.h"


//===========
// Namespace
//===========

namespace Storage {


//===========
// Container
//===========

class Container: public Streams::RandomAccessStream
{
public:
	// Common
	virtual FileSize GetSize()=0;
	virtual BOOL Seek(UINT64 Position)=0;

protected:
	// Con-/Destructors
	Container() {}
};

}