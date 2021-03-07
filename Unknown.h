//===========
// Unknown.h
//===========

#pragma once


//=======
// Using
//=======

#include "MemoryHelper.h"
#include "CharHelper.h"


//==============
// Unknown Type
//==============

enum class UnknownType
{
None,
Double,
DoublePtr,
Float,
FloatPtr,
Int8,
Int16,
Int32,
Int64,
Int32Ptr,
Int64Ptr,
String,
UInt8,
UInt16,
UInt32,
UInt64,
UInt32Ptr,
UInt64Ptr,
WString
};


//=========
// Unknown
//=========

class Unknown
{
public:
	// Con-/Destructors
	Unknown();
	Unknown(Unknown const& Unknown);
	Unknown(BYTE Item) { Set(Item, UnknownType::UInt8); }
	Unknown(WORD Item) { Set(Item, UnknownType::UInt16); }
	Unknown(UINT Item) { Set(Item, UnknownType::UInt32); }
	Unknown(UINT64 Item) { Set(Item, UnknownType::UInt64); }
	Unknown(UINT* Item) { Set(Item, UnknownType::UInt32Ptr); }
	Unknown(UINT64* Item) { Set(Item, UnknownType::UInt64Ptr); }
	Unknown(SHORT Item) { Set(Item, UnknownType::Int16); }
	Unknown(INT Item) { Set(Item, UnknownType::Int32); }
	Unknown(INT64 Item) { Set(Item, UnknownType::Int64); }
	Unknown(INT* Item) { Set(Item, UnknownType::Int32Ptr); }
	Unknown(INT64* Item) { Set(Item, UnknownType::Int64Ptr); }
	Unknown(FLOAT Item) { Set(Item, UnknownType::Float); }
	Unknown(FLOAT* Item) { Set(Item, UnknownType::FloatPtr); }
	Unknown(DOUBLE Item) { Set(Item, UnknownType::Double); }
	Unknown(DOUBLE* Item) { Set(Item, UnknownType::DoublePtr); }
	Unknown(CHAR Item) { Set(Item, UnknownType::UInt8); }
	Unknown(WCHAR Item) { Set(Item, UnknownType::UInt16); }
	Unknown(Chars Item) { Set(Item, UnknownType::UInt8); }
	Unknown(LPSTR Item) { Set(Item, UnknownType::String); }
	Unknown(LPCSTR Item) { Set(Item, UnknownType::String); }
	Unknown(LPWSTR Item) { Set(Item, UnknownType::WString); }
	Unknown(LPCWSTR Item) { Set(Item, UnknownType::WString); }

	// Access
	inline operator BYTE()const { return Convert<BYTE>(UnknownType::UInt8); }
	inline operator WORD()const { return Convert<WORD>(UnknownType::UInt16); }
	inline operator UINT()const { return Convert<UINT>(UnknownType::UInt32); }
	inline operator UINT64()const { return Convert<UINT64>(UnknownType::UInt64); }
	inline operator UINT*()const { return Get<UINT*>(UnknownType::UInt32Ptr); }
	inline operator UINT64*()const { return Get<UINT64*>(UnknownType::UInt64Ptr); }
	inline operator SHORT()const { return Convert<SHORT>(UnknownType::Int16); }
	inline operator INT()const { return Convert<INT>(UnknownType::Int32); }
	inline operator INT64()const { return Convert<INT64>(UnknownType::Int64); }
	inline operator INT*()const { return Get<INT*>(UnknownType::Int32Ptr); }
	inline operator INT64*()const { return Get<INT64*>(UnknownType::Int64Ptr); }
	inline operator FLOAT()const { return Convert<FLOAT>(UnknownType::Float); }
	inline operator FLOAT*()const { return Get<FLOAT*>(UnknownType::FloatPtr); }
	inline operator DOUBLE()const { return Convert<DOUBLE>(UnknownType::Double); }
	inline operator DOUBLE*()const { return Get<DOUBLE*>(UnknownType::DoublePtr); }
	inline operator CHAR()const { return Convert<CHAR>(UnknownType::UInt8); }
	inline operator WCHAR()const { return Convert<WCHAR>(UnknownType::UInt16); }
	inline operator LPSTR()const { return Get<LPSTR>(UnknownType::String); }
	inline operator LPCSTR()const { return Get<LPCSTR>(UnknownType::String); }
	inline operator LPWSTR()const { return Get<LPWSTR>(UnknownType::WString); }
	inline operator LPCWSTR()const { return Get<LPCWSTR>(UnknownType::WString); }

private:
	// Common
	template <class _item_t> _item_t Convert(UnknownType Type)const
		{
		if(Type==uType)
			{
			auto p=(_item_t*)pBuffer;
			return *p;
			}
		switch(uType)
			{
			case UnknownType::Double:
				{
				auto p=(DOUBLE*)pBuffer;
				return (_item_t)*p;
				}
			case UnknownType::Float:
				{
				auto p=(FLOAT*)pBuffer;
				return (_item_t)*p;
				}
			case UnknownType::Int8:
				{
				auto p=(CHAR*)pBuffer;
				return (_item_t)*p;
				}
			case UnknownType::Int16:
				{
				auto p=(SHORT*)pBuffer;
				return (_item_t)*p;
				}
			case UnknownType::Int32:
				{
				auto p=(INT*)pBuffer;
				return (_item_t)*p;
				}
			case UnknownType::Int64:
				{
				auto p=(INT64*)pBuffer;
				return (_item_t)*p;
				}
			case UnknownType::UInt8:
				{
				auto p=(BYTE*)pBuffer;
				return (_item_t)*p;
				}
			case UnknownType::UInt16:
				{
				auto p=(WORD*)pBuffer;
				return (_item_t)*p;
				}
			case UnknownType::UInt32:
				{
				auto p=(UINT*)pBuffer;
				return (_item_t)*p;
				}
			case UnknownType::UInt64:
				{
				auto p=(UINT64*)pBuffer;
				return (_item_t)*p;
				}
			default:
				return 0;
			}
		return 0;
		}
	template <class _item_t> _item_t Get(UnknownType Type)const
		{
		if(Type==uType)
			{
			auto p=(_item_t*)pBuffer;
			return *p;
			}
		return 0;
		}
	template <class _item_t> VOID Set(_item_t Item, UnknownType Type)
		{
		CopyMemory(pBuffer, &Item, sizeof(_item_t));
		uType=Type;
		}
	alignas(8) BYTE pBuffer[8];
	UnknownType uType;
};
