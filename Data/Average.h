//===========
// Average.h
//===========

#pragma once


//===========
// Namespace
//===========

namespace Data {


//=========
// Average
//=========

template <class _value_t, UINT _count=8, UINT _ignore=0>
class Average
{
public:
	// Con-/Destructors
	Average(): tValue(0), uCount(0) {}

	// Access
	operator _value_t()const { return tValue; }
	UINT GetCount()const { return uCount; }
	_value_t const* GetValues()const { return pValues; }

	// Modification
	Average& operator=(_value_t Value)
		{
		if(uCount<_count)
			{
			pValues[uCount++]=Value;
			}
		else
			{
			MoveMemory(pValues, &pValues[1], (uCount-1)*sizeof(_value_t));
			pValues[uCount-1]=Value;
			}
		_value_t psorted[_count];
		for(UINT u=0; u<uCount; u++)
			{
			BOOL bdone=false;
			for(UINT s=0; s<u; s++)
				{
				if(pValues[u]<psorted[s])
					{
					MoveMemory(&psorted[s+1], &psorted[s], (u-s-1)*sizeof(_value_t));
					psorted[s]=pValues[u];
					bdone=true;
					break;
					}
				}
			if(bdone)
				continue;
			psorted[u]=pValues[u];
			}
		_value_t t=0;
		if(uCount>_ignore*2)
			{
			for(UINT u=_ignore; u<uCount-_ignore; u++)
				t+=pValues[u];
			tValue=t/(uCount-_ignore*2);
			}
		else
			{
			for(UINT u=0; u<uCount; u++)
				t+=pValues[u];
			tValue=t/uCount;
			}
		return *this;
		}
	VOID Reset() { tValue=0; uCount=0; }

private:
	// Common
	_value_t pValues[_count];
	_value_t tValue;
	UINT uCount;
};

}