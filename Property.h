//============
// Property.h
//============

#pragma once


//==========
// Property
//==========

template <class _owner_t, class _item_t>
class Property
{
public:
	// Con-/Destructors
	Property(_owner_t* Owner, _item_t Value): pOwner(Owner), tValue(Value) {}
	Property(Property const& Property): pOwner(Property.pOwner), tValue(Property.tValue) {}

	// Access
	operator bool()
		{
		_item_t tvalue=tValue;
		Reading(pOwner, tvalue);
		return tvalue;
		}
	operator _item_t()
		{
		_item_t tvalue=tValue;
		Reading(pOwner, tvalue);
		return tvalue;
		}
	_item_t const& GetInternal()const { return tValue; }
	Event<_owner_t, _item_t&> Reading;

	// Modification
	Property& operator=(_item_t Value)
		{
		if(tValue==Value)
			return *this;
		tValue=Value;
		Changed(pOwner, tValue);
		return *this;
		}
	Property& operator=(Property const& Property) { return operator=(Property.tValue); }
	Event<_owner_t, _item_t> Changed;
	VOID SetInternal(_item_t Value) { tValue=Value; }

private:
	// Common
	_owner_t* pOwner;
	_item_t tValue;
};


//========================
// Property without Owner
//========================

template <class _item_t>
class Property<VOID, _item_t>
{
public:
	// Con-/Destructors
	Property(_item_t Value): tValue(Value) {}
	Property(Property const& Property): tValue(Property.tValue) {}

	// Access
	operator bool()
		{
		_item_t tvalue=tValue;
		Reading(tvalue);
		return tvalue;
		}
	operator _item_t()
		{
		_item_t tvalue=tValue;
		Reading(tvalue);
		return tvalue;
		}
	_item_t const& GetInternal()const { return tValue; }
	Event<VOID, _item_t&> Reading;

	// Modification
	Property& operator=(_item_t Value)
		{
		if(tValue==Value)
			return *this;
		tValue=Value;
		Changed(tValue);
		return *this;
		}
	Property& operator=(Property const& Property) { return operator=(Property.tValue); }
	Event<VOID, _item_t> Changed;
	VOID SetInternal(_item_t Value) { tValue=Value; }

private:
	// Common
	_item_t tValue;
};
