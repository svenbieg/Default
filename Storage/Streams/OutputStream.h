//================
// OutputStream.h
//================

#pragma once


//===========
// Namespace
//===========

namespace Storage {
	namespace Streams {


//===============
// Output-Stream
//===============

class OutputStream: public virtual Object
{
public:
	// Con-/Destructors
	virtual ~OutputStream() {}

	// Common
	virtual VOID Flush()=0;
	virtual SIZE_T Write(VOID const* Buffer, SIZE_T Size)=0;

protected:
	// Con-/Destructors
	OutputStream() {}
};

}}
