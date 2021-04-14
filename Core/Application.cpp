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
Handle<String> Application::Name;
Handle<String> Application::Version;


//============================
// Con-/Destructors Protected
//============================

Application::Application(Handle<String> hname)
{
Current=this;
Name=hname;
Loop.Add(this, &Application::OnLoop);
}


//================
// Common Private
//================

VOID Application::OnLoop()
{
cDispatcher.Run();
}

}