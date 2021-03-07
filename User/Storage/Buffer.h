//==========
// Buffer.h
//==========

#pragma once


//===========
// Namespace
//===========

namespace User {
	namespace Storage {


//========
// Buffer
//========

class Buffer
{
public:
	// Con-/Destructors
	Buffer();
	Buffer(SIZE_T Size);
	~Buffer();

	// Access
	inline BYTE* Begin()const { return pBuffer; }
	inline SIZE_T GetSize()const { return uSize; }

	// Modification
	VOID Clear();
	VOID SetSize(SIZE_T Size);
	VOID Zero();

private:
	// Common
	BYTE* pBuffer;
	SIZE_T uSize;
};

}}
