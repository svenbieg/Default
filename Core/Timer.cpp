//===========
// Timer.cpp
//===========

#include "pch.h"


//=======
// Using
//=======

#include "Application.h"
#include "Timer.h"


//===========
// Namespace
//===========

namespace Core {


//==================
// Con-/Destructors
//==================

Timer::Timer():
iInterval(0),
uLastTime(0)
{}

Timer::~Timer()
{
Stop();
}


//========
// Common
//========

VOID Timer::StartOnce(UINT ums)
{
if(iInterval!=0)
	Stop();
iInterval=ums;
uLastTime=GetTickCount64();
Application::Current->Loop.Add(this, &Timer::OnLoop);
}

VOID Timer::StartPeriodic(UINT ums)
{
if(iInterval!=0)
	Stop();
iInterval=-(INT)ums;
uLastTime=GetTickCount64();
Application::Current->Loop.Add(this, &Timer::OnLoop);
}

VOID Timer::Stop()
{
if(iInterval==0)
	return;
Application::Current->Loop.Remove(this);
iInterval=0;
}


//================
// Common Private
//================

VOID Timer::OnLoop()
{
UINT64 utime=GetTickCount64();
UINT udt=iInterval>0? iInterval: -iInterval;
if(utime<uLastTime+udt)
	return;
Triggered(this);
uLastTime=utime;
if(iInterval>0)
	Stop();
}

}