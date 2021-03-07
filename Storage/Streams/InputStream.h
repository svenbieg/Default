//===============
// InputStream.h
//===============

#pragma once


//===========
// Namespace
//===========

namespace Storage {
	namespace Streams {


//==============
// Input-Stream
//==============

class InputStream: public virtual Object
{
public:
	// Con-/Destructors
	virtual ~InputStream() {}

	// Common
	virtual SIZE_T Available()=0;
	virtual SIZE_T Read(VOID* Buffer, SIZE_T Size)=0;

protected:
	// Con-/Destructors
	InputStream() {}
};

}}
