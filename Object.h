//==========
// Object.h
//==========

#pragma once


//========
// Object
//========

class Object
{
public:
	// Friends
	template <class _item_t> friend class Handle;

	// Common
	VOID AddReference() { uRefCount++; }
	SIZE_T GetRefCount() { return uRefCount; }
	VOID Release()
		{
		if(--uRefCount==0)
			delete this;
		}
	VOID RemoveReference() { uRefCount--; }

protected:
	// Con-/Destructors
	Object(): uRefCount(0) {}
	virtual ~Object() {}

private:
	// Common
	volatile SIZE_T uRefCount;
};
