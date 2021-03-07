//=====================
// VariableArguments.h
//=====================

#pragma once


//=======
// Using
//=======

#include "Unknown.h"


//====================
// Variable Arguments
//====================

class VariableArguments
{
public:
	// Con-/Destructors
	VariableArguments(Unknown* Arguments, UINT Count): pArguments(Arguments), uCount(Count), uPosition(0) {}

	// Access
	inline Unknown& operator[](UINT Id) { return pArguments[Id]; }
	template <class _item_t> BOOL Get(_item_t& Item)
		{
		if(uPosition>=uCount)
			return false;
		Item=pArguments[uPosition++];
		return true;
		}
	VOID Begin() { uPosition=0; }
	UINT GetCount()const { return uCount; }
	VOID MoveNext() { uPosition++; }
	template <class _item_t> BOOL TryGet(_item_t& Item)
		{
		if(uPosition>=uCount)
			return false;
		Item=pArguments[uPosition];
		return true;
		}

private:
	// Common
	Unknown* pArguments;
	UINT uCount;
	UINT uPosition;
};
