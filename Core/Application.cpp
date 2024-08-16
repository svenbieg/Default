//=================
// Application.cpp
//=================

#include "pch.h"


//=======
// Using
//=======

#include "Application.h"


//===========
// Namespace
//===========

namespace Core {


//========
// Common
//========

Handle<Application> Application::Current;

VOID Application::HandleDispatched()
{
while(hDispatched)
	{
	DispatchedHandler::Remove(hDispatched)->Run();
	}
}

VOID Application::Quit()
{
Running=false;
hDispatched=nullptr;
}


//============================
// Con-/Destructors Protected
//============================

Application::Application(LPCSTR name, LPCSTR version):
Name(name),
Running(true),
Version(version)
{
Current=this;
}


//================
// Common Private
//================

VOID Application::Dispatch(DispatchedHandler* handler)
{
DispatchedHandler::Append(hDispatched, handler);
OnDispatched();
}

}
