//================
// EventHandler.h
//================

#pragma once


//=======
// Using
//=======

#include "EventHandler.h"


//===========
// Namespace
//===========

namespace Details {


//===========================
// Event-Proc with Arguments
//===========================

template <class _sender_t, class _receiver_t, class... _args_t>
class EventProcWithArgs: public EventHandler<_sender_t, _args_t...>
{
public:
	// Definitions
	typedef VOID (_receiver_t::*_proc_t)(_args_t...);

	// Con-/Destructors
	EventProcWithArgs(_receiver_t* Receiver, _proc_t Procedure): EventHandler<_sender_t, _args_t...>(Receiver), pProcedure(Procedure) {}

	// Common
	VOID Run(_sender_t* Sender, _args_t... Arguments)override
		{
		if(!this->pReceiver)
			return;
		this->uRunning++;
		auto preceiver=(_receiver_t*)this->pReceiver;
		(preceiver->*pProcedure)(Arguments...);
		this->pReceiver=nullptr;
		this->uRunning--;
		}

private:
	// Common
	_proc_t pProcedure;
};


//========================
// Event-Proc with Sender
//========================

template <class _sender_t, class _receiver_t, class... _args_t>
class EventProcWithSender: public EventHandler<_sender_t, _args_t...>
{
public:
	// Definitions
	typedef VOID (_receiver_t::*_proc_t)(Handle<_sender_t>, _args_t...);

	// Con-/Destructors
	EventProcWithSender(_receiver_t* Receiver, _proc_t Procedure): EventHandler<_sender_t, _args_t...>(Receiver), pProcedure(Procedure) {}

	// Common
	VOID Run(_sender_t* Sender, _args_t... Arguments)override
		{
		if(!this->pReceiver)
			return;
		this->uRunning++;
		auto preceiver=(_receiver_t*)this->pReceiver;
		(preceiver->*pProcedure)(Sender, Arguments...);
		this->pReceiver=nullptr;
		this->uRunning--;
		}

private:
	// Common
	_proc_t pProcedure;
};

}