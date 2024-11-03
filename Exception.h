//=============
// Exception.h
//=============

#pragma once


//=======
// Using
//=======

#include "StatusClass.h"


//===========
// Exception
//===========

class Exception
{
public:
	// Common
	Status GetStatus()const { return m_Status; }

protected:
	// Con-/Destructors
	Exception(Status Status): m_Status(Status) {}

private:
	// Common
	Status m_Status;
};


//============
// Exceptions
//============

class AbortException: public Exception
{
public:
	// Con-/Destructors
	AbortException(): Exception(Status::Aborted) {}
};

class DeviceNotReadyException: public Exception
{
public:
	// Con-/Destructors
	DeviceNotReadyException(): Exception(Status::DeviceNotReady) {}
};

class InvalidArgumentException: public Exception
{
public:
	// Con-/Destructors
	InvalidArgumentException(): Exception(Status::InvalidArgument) {}
};

class NotImplementedException: public Exception
{
public:
	// Con-/Destructors
	NotImplementedException(): Exception(Status::NotImplemented) {}
};

class OutOfRangeException: public Exception
{
public:
	// Con-/Destructors
	OutOfRangeException(): Exception(Status::OutOfRange) {}
};

class TimeoutException: public Exception
{
public:
	// Con-/Destructors
	TimeoutException(): Exception(Status::Timeout) {}
};
