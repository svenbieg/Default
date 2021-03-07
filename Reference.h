//=============
// Reference.h
//=============

#pragma once


//=======
// Using
//=======

#include "Object.h"


//===========
// Reference
//===========

class Reference
{
public:
	// Con-/Destructors
	Reference(Object* Object): pObject(Object) { pObject->AddReference(); }
	~Reference() { pObject->RemoveReference(); }

private:
	// Common
	Object* pObject;
};
