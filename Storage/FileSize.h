//============
// FileSize.h
//============

#pragma once


//===========
// Namespace
//===========

namespace Storage {


//===========
// File-Size
//===========

class FileSize
{
public:
	// Con-/Destructors
	FileSize(UINT64 Size=0);
	FileSize(DWORD High, DWORD Low);

	// Access
	operator UINT64()const { return uSize; }
	Handle<String> ToString()const;
	static Handle<String> ToString(UINT64 Size);
	UINT ToUINT()const;

private:
	// Common
	UINT64 uSize;
};

}