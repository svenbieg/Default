//==============
// ScopedLock.h
//==============

#pragma once


//=======
// Using
//=======

#include "CriticalSection.h"


//=============
// Scoped Lock
//=============

class ScopedLock
{
public:
	// Con-/Destructors
	ScopedLock(CriticalSection& CriticalSection): pCriticalSection(&CriticalSection) { pCriticalSection->Lock(); }
	~ScopedLock()
		{
		if(pCriticalSection)
			pCriticalSection->Unlock();
		}

	// Common
	VOID Destroy()
		{
		pCriticalSection=nullptr;
		}
	VOID Release()
		{
		if(pCriticalSection)
			{
			pCriticalSection->Unlock();
			pCriticalSection=nullptr;
			}
		}

private:
	// Common
	CriticalSection* pCriticalSection;
};
