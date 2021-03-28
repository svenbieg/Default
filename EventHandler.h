//================
// EventHandler.h
//================

#pragma once


//=======
// Using
//=======

#include "User/Collections/ListItem.h"
#include "Handle.h"


//===========
// Namespace
//===========

namespace Details {


//===============
// Event-Handler
//===============

template <class _sender_t, class... _args_t>
class EventHandler: public User::Collections::ListItem<EventHandler<_sender_t, _args_t...>>
{
public:
	// Common
	inline VOID* GetReceiver()const { return pReceiver; }
	inline VOID Invalidate() { pReceiver=nullptr; }
	BOOL IsRunning()const { return uRunning>0; }
	virtual VOID Run(_sender_t* Sender, _args_t... Arguments)=0;

protected:
	// Con-/Destructors
	EventHandler(VOID* Receiver): pReceiver(Receiver), uRunning(0) {}

	// Common
	VOID* pReceiver;
	UINT uRunning;
};


//==============================
// Event-Handler with Arguments
//==============================

template <class _sender_t, class _receiver_t, class... _args_t>
class EventHandlerWithArgs: public EventHandler<_sender_t, _args_t...>
{
public:
	// Definitions
	typedef VOID (_receiver_t::*_proc_t)(_args_t...);

	// Con-/Destructors
	EventHandlerWithArgs(_receiver_t* Receiver, _proc_t Procedure): EventHandler<_sender_t, _args_t...>(Receiver), pProcedure(Procedure) {}

	// Common
	VOID Run(_sender_t* Sender, _args_t... Arguments)override
		{
		if(!this->pReceiver)
			return;
		this->uRunning++;
		auto preceiver=(_receiver_t*)this->pReceiver;
		Handle<_receiver_t> hreceiver=preceiver;
		(preceiver->*pProcedure)(Arguments...);
		this->uRunning--;
		}

private:
	// Common
	_proc_t pProcedure;
};


//===========================
// Event-Handler with Sender
//===========================

template <class _sender_t, class _receiver_t, class... _args_t>
class EventHandlerWithSender: public EventHandler<_sender_t, _args_t...>
{
public:
	// Definitions
	typedef VOID (_receiver_t::*_proc_t)(Handle<_sender_t>, _args_t...);

	// Con-/Destructors
	EventHandlerWithSender(_receiver_t* Receiver, _proc_t Procedure): EventHandler<_sender_t, _args_t...>(Receiver), pProcedure(Procedure) {}

	// Common
	VOID Run(_sender_t* Sender, _args_t... Arguments)override
		{
		if(!this->pReceiver)
			return;
		this->uRunning++;
		auto preceiver=(_receiver_t*)this->pReceiver;
		Handle<_receiver_t> hreceiver=preceiver;
		(preceiver->*pProcedure)(Sender, Arguments...);
		this->uRunning--;
		}

private:
	// Common
	_proc_t pProcedure;
};

}