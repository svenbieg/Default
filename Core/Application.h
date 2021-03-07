//===============
// Application.h
//===============

#pragma once


//===========
// Namespace
//===========

namespace Core {


//=============
// Application
//=============

class Application: public Object
{
public:
	// Common
	static Handle<Application> Current;
	Event<Application> Destroyed;
	Event<Application> Initialized;
	Event<Application> Loop;
	static Handle<String> Name;
	static Handle<String> Version;

protected:
	// Con-/Destructors
	Application(Handle<String> Name);
};

}