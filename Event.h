//=========
// Event.h
//=========

#pragma once


//=======
// Using
//=======

#include "User/Collections/SmallList.h"
#include "EventProc.h"
#include "Handle.h"


//==================
// Event Base-Class
//==================

namespace Details {

template <class _sender_t, class... _args_t>
class EventBase
{
private:
	// Using
	using _handler_t=EventHandler<_sender_t, _args_t...>;
	using _list_t=User::Collections::SmallList<_handler_t>;

public:
	// Access
	inline operator BOOL() { return cHandlers.HasItems(); }

	// Modification
	VOID Remove(VOID* Receiver)
		{
		for(auto it=cHandlers.First(); it.HasCurrent();)
			{
			auto phandler=it.GetCurrent();
			if(phandler->GetReceiver()==Receiver)
				{
				if(phandler->IsRunning())
					{
					phandler->Invalidate();
					}
				else
					{
					it.RemoveCurrent();
					continue;
					}
				}
			it.MoveNext();
			}
		}

protected:
	// Con-/Destructors
	EventBase() {}

	// Common
	VOID RunInternal(_sender_t* Sender, _args_t... Arguments)
		{
		for(auto it=cHandlers.First(); it.HasCurrent();)
			{
			auto phandler=it.GetCurrent();
			phandler->Run(Sender, Arguments...);
			if(phandler->GetReceiver()==nullptr)
				{
				it.RemoveCurrent();
				}
			else
				{
				it.MoveNext();
				}
			}
		}
	_list_t cHandlers;
};

}


//=======
// Event
//=======

template <class _sender_t, class... _args_t>
class Event: public Details::EventBase<_sender_t, _args_t...>
{
public:
	// Con-/Destructors
	Event() {}
	Event(Event const& Event)=delete;

	// Access
	VOID operator()(Handle<_sender_t> Sender, _args_t... Arguments) { this->RunInternal(Sender, Arguments...); }

	// Modification
	template <class _receiver_t> VOID Add(_receiver_t* Receiver, VOID (_receiver_t::*Proc)(_args_t...))
		{
		auto phandler=new Details::EventHandlerWithArgs<_sender_t, _receiver_t, _args_t...>(Receiver, Proc);
		this->cHandlers.Append(phandler);
		}
	template <class _receiver_t> VOID Add(_receiver_t* Receiver, VOID (_receiver_t::*Proc)(Handle<_sender_t>, _args_t...))
		{
		auto phandler=new Details::EventHandlerWithSender<_sender_t, _receiver_t, _args_t...>(Receiver, Proc);
		this->cHandlers.Append(phandler);
		}
	template <class _receiver_t> VOID AddProc(_receiver_t* Receiver, VOID (_receiver_t::*Proc)(_args_t...))
		{
		auto pproc=new Details::EventProcWithArgs<_sender_t, _receiver_t, _args_t...>(Receiver, Proc);
		this->cHandlers.Append(pproc);
		}
	template <class _receiver_t> VOID AddProc(_receiver_t* Receiver, VOID (_receiver_t::*Proc)(Handle<_sender_t>, _args_t...))
		{
		auto pproc=new Details::EventProcWithSender<_sender_t, _receiver_t, _args_t...>(Receiver, Proc);
		this->cHandlers.Append(pproc);
		}
};


//======================
// Event without Sender
//======================

template <class... _args_t>
class Event<VOID, _args_t...>: public Details::EventBase<VOID, _args_t...>
{
public:
	// Con-/Destructors
	Event() {}
	Event(Event const& Event)=delete;

	// Access
	VOID operator()(_args_t... Arguments) { this->RunInternal(nullptr, Arguments...); }

	// Modification
	template <class _receiver_t> VOID Add(_receiver_t* Receiver, VOID (_receiver_t::*Proc)(_args_t...))
		{
		auto phandler=new Details::EventHandlerWithArgs<VOID, _receiver_t, _args_t...>(Receiver, Proc);
		this->cHandlers.Append(phandler);
		}
	template <class _receiver_t> VOID AddProc(_receiver_t* Receiver, VOID (_receiver_t::*Proc)(_args_t...))
		{
		auto pproc=new Details::EventProcWithArgs<VOID, _receiver_t, _args_t...>(Receiver, Proc);
		this->cHandlers.Append(pproc);
		}
};
