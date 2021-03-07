//===============
// StringClass.h
//===============

#pragma once


//=======
// Using
//=======

#include "Storage/Streams/InputStream.h"
#include "Storage/Streams/OutputStream.h"
#include "HandleHelper.h"
#include "StringHelper.h"
#include "VariableHandle.h"


//======================
// Forward-Declarations
//======================

class String;
template <> class Handle<String>;


//========
// String
//========

class String: public Object
{
private:
	// Using
	using InputStream=Storage::Streams::InputStream;
	using OutputStream=Storage::Streams::OutputStream;

public:
	// Con-/Destructors
	String(): pBuffer(nullptr) {}
	String(INT Resource): pBuffer(nullptr) { StringAssign(&pBuffer, nullptr, GetResourceString(Resource)); }
	String(LPCSTR Value): pBuffer(nullptr) { StringAssign(&pBuffer, nullptr, Value); }
	String(LPCWSTR Value): pBuffer(nullptr) { StringAssign(&pBuffer, nullptr, Value); }
	String(UINT Length, decltype(nullptr)): pBuffer(nullptr) { StringSetSize(&pBuffer, nullptr, Length+1); }
	String(UINT Length, LPCSTR Value): pBuffer(nullptr) { StringAssign(&pBuffer, nullptr, Value, Length); }
	String(UINT Length, LPCWSTR Value): pBuffer(nullptr) { StringAssign(&pBuffer, nullptr, Value, Length); }
	template <class... _args_t> String(LPCSTR Format, _args_t... Arguments): pBuffer(nullptr) { StringPrint(&pBuffer, nullptr, Format, Arguments...); }
	template <class... _args_t> String(LPCWSTR Format, _args_t... Arguments): pBuffer(nullptr) { StringPrint(&pBuffer, nullptr, Format, Arguments...); }
	~String() { if(pBuffer)Free(pBuffer); }

	// Access
	inline LPCTSTR Begin()const { return pBuffer; }
	BOOL Contains(Handle<String> String, BOOL CaseSensitive=true);
	Handle<String> Get(Handle<String> Key);
	inline UINT GetLength()const { return StringLength(pBuffer); }
	BOOL IsEmpty()const { return !(pBuffer&&pBuffer[0]); }
	Handle<String> LowerCase()const;
	template <class _fmt_t, class... _args_t> UINT Scan(_fmt_t const* Format, _args_t... Arguments) { return StringScan(pBuffer, Format, Arguments...); }
	Handle<String> UpperCase()const;
	SIZE_T WriteToStream(Handle<OutputStream> Stream);

	// Modification
	SIZE_T ReadFromStream(Handle<InputStream> Stream);

	// Comparison
	inline BOOL operator==(String const& String)const { return StringCompare(pBuffer, String.pBuffer)==0; }
	inline BOOL operator!=(String const& String)const { return StringCompare(pBuffer, String.pBuffer)!=0; }
	inline BOOL operator>(String const& String)const { return StringCompare(pBuffer, String.pBuffer)>0; }
	inline BOOL operator>=(String const& String)const { return StringCompare(pBuffer, String.pBuffer)>=0; }
	inline BOOL operator<(String const& String)const { return StringCompare(pBuffer, String.pBuffer)<0; }
	inline BOOL operator<=(String const& String)const { return StringCompare(pBuffer, String.pBuffer)<=0; }

private:
	// Common
	LPTSTR pBuffer;
};


//===============
// String-Handle
//===============

template <>
class Handle<String>
{
public:
	// Friends
	template <class _friend_t> friend class Handle;
	template <class _owner_t, class _obj_t> friend class VariableHandle;

	// Con-/Destructors
	Handle(): pObject(nullptr) {}
	Handle(decltype(nullptr)): pObject(nullptr) {}
	Handle(INT Resource) { HandleCreate<String, String>(&pObject, new String(Resource)); }
	Handle(LPCSTR Value) { HandleCreate<String, String>(&pObject, new String(0, Value)); }
	Handle(LPCWSTR Value) { HandleCreate<String, String>(&pObject, new String(0, Value)); }
	Handle(UINT Length, LPCSTR Value) { HandleCreate<String, String>(&pObject, new String(Length, Value)); }
	Handle(UINT Length, LPCWSTR Value) { HandleCreate<String, String>(&pObject, new String(Length, Value)); }
	Handle(String* Value) { HandleCreate<String, String>(&pObject, Value); }
	Handle(Handle<String> const& Handle) { HandleCreate<String, String>(&pObject, Handle.pObject); }
	Handle(Handle<String>&& Handle)noexcept: pObject(Handle.pObject) { Handle.pObject=nullptr; }
	~Handle() { HandleDestroy(pObject); }

	// Access
	operator String*()const { return pObject; }
	String* operator->()const { return pObject; }

	// Comparison
	BOOL operator==(decltype(nullptr))const { return !(pObject&&pObject->GetLength()); }
	BOOL operator==(LPCSTR Value)const
		{
		LPCTSTR pstr1=pObject? pObject->Begin(): nullptr;
		return StringCompare(pstr1, Value)==0;
		}
	BOOL operator==(LPCWSTR Value)const
		{
		LPCTSTR pstr1=pObject? pObject->Begin(): nullptr;
		return StringCompare(pstr1, Value)==0;
		}
	BOOL operator==(Handle<String> const& Handle)const
		{
		LPCTSTR pstr1=pObject? pObject->Begin(): nullptr;
		LPCTSTR pstr2=Handle? Handle->Begin(): nullptr;
		return StringCompare(pstr1, pstr2)==0;
		}
	inline BOOL operator!=(decltype(nullptr))const { return (pObject&&pObject->GetLength()); }
	inline BOOL operator!=(LPCSTR Value)const { return !operator==(Value); }
	inline BOOL operator!=(LPCWSTR Value)const { return !operator==(Value); }
	inline BOOL operator!=(Handle<String> const& Handle)const { return !operator==(Handle); }
	inline BOOL operator>(decltype(nullptr))const { return (pObject&&pObject->GetLength()); }
	BOOL operator>(LPCSTR Value)const
		{
		LPCTSTR pstr1=pObject? pObject->Begin(): nullptr;
		return StringCompare(pstr1, Value)>0;
		}
	BOOL operator>(LPCWSTR Value)const
		{
		LPCTSTR pstr1=pObject? pObject->Begin(): nullptr;
		return StringCompare(pstr1, Value)>0;
		}
	BOOL operator>(Handle<String> const& Object)const
		{
		LPCTSTR pstr1=pObject? pObject->Begin(): nullptr;
		LPCTSTR pstr2=Object? Object->Begin(): nullptr;
		return StringCompare(pstr1, pstr2)>0;
		}
	BOOL operator>=(decltype(nullptr))const { return true; }
	BOOL operator>=(LPCSTR Value)const
		{
		LPCTSTR pstr1=pObject? pObject->Begin(): nullptr;
		return StringCompare(pstr1, Value)>=0;
		}
	BOOL operator>=(LPCWSTR Value)const
		{
		LPCTSTR pstr1=pObject? pObject->Begin(): nullptr;
		return StringCompare(pstr1, Value)>=0;
		}
	BOOL operator>=(Handle<String> const& Object)const
		{
		LPCTSTR pstr1=pObject? pObject->Begin(): nullptr;
		LPCTSTR pstr2=Object? Object->Begin(): nullptr;
		return StringCompare(pstr1, pstr2)>=0;
		}
	BOOL operator<(decltype(nullptr))const { return false; }
	BOOL operator<(LPCSTR Value)const
		{
		LPCTSTR pstr1=pObject? pObject->Begin(): nullptr;
		return StringCompare(pstr1, Value)<0;
		}
	BOOL operator<(LPCWSTR Value)const
		{
		LPCTSTR pstr1=pObject? pObject->Begin(): nullptr;
		return StringCompare(pstr1, Value)<0;
		}
	BOOL operator<(Handle<String> const& Object)const
		{
		LPCTSTR pstr1=pObject? pObject->Begin(): nullptr;
		LPCTSTR pstr2=Object? Object->Begin(): nullptr;
		return StringCompare(pstr1, pstr2)<0;
		}
	BOOL operator<=(decltype(nullptr))const { return !(pObject&&pObject->GetLength()); }
	BOOL operator<=(LPCSTR Value)const
		{
		LPCTSTR pstr1=pObject? pObject->Begin(): nullptr;
		return StringCompare(pstr1, Value)<=0;
		}
	BOOL operator<=(LPCWSTR Value)const
		{
		LPCTSTR pstr1=pObject? pObject->Begin(): nullptr;
		return StringCompare(pstr1, Value)<=0;
		}
	BOOL operator<=(Handle<String> const& Object)const
		{
		LPCTSTR pstr1=pObject? pObject->Begin(): nullptr;
		LPCTSTR pstr2=Object? Object->Begin(): nullptr;
		return StringCompare(pstr1, pstr2)<=0;
		}

	// Assignment
	Handle& operator=(decltype(nullptr)) { HandleClear(&pObject); return *this; }
	Handle& operator=(INT Resource) { return operator=(GetResourceString(Resource)); }
	Handle& operator=(LPCSTR Value)
		{
		if(pObject)
			{
			if(StringCompare(pObject->Begin(), Value)==0)
				return *this;
			pObject->Release();
			pObject=nullptr;
			}
		if(Value&&Value[0])
			{
			pObject=new String(Value);
			pObject->AddReference();
			}
		return *this;
		}
	Handle& operator=(LPCWSTR Value)
		{
		if(pObject)
			{
			if(StringCompare(pObject->Begin(), Value)==0)
				return *this;
			pObject->Release();
			pObject=nullptr;
			}
		if(Value&&Value[0])
			{
			pObject=new String(Value);
			pObject->AddReference();
			}
		return *this;
		}
	Handle& operator=(Handle const& Handle) { HandleAssign(&pObject, Handle.pObject); return *this; }

	// Operators
	Handle<String> operator+(LPCSTR Append)
		{
		if(!pObject)
			return new String(Append);
		return new String("%s%s", pObject->Begin(), Append);
		}
	Handle<String> operator+(LPCWSTR Append)
		{
		if(!pObject)
			return new String(Append);
		return new String("%s%s", pObject->Begin(), Append);
		}
	Handle<String> operator+(String* Append)
		{
		if(!pObject)
			return Append;
		if(!Append)
			return pObject;
		return new String("%s%s", pObject->Begin(), Append->Begin());
		}

private:
	String* pObject;
};


//========================
// Variable String-Handle
//========================

template <class _owner_t>
class VariableHandle<_owner_t, String>
{
public:
	// Con-/Destructors
	VariableHandle(_owner_t* Owner): pObject(nullptr), pOwner(Owner) {}
	VariableHandle(_owner_t* Owner, decltype(nullptr)): pObject(nullptr), pOwner(Owner) {}
	VariableHandle(_owner_t* Owner, INT Resource): pOwner(Owner) { HandleCreate<String, String>(&pObject, new String(Resource)); }
	VariableHandle(_owner_t* Owner, LPCSTR Value): pOwner(Owner) { HandleCreate<String, String>(&pObject, new String(0, Value)); }
	VariableHandle(_owner_t* Owner, LPCWSTR Value): pOwner(Owner) { HandleCreate<String, String>(&pObject, new String(0, Value)); }
	VariableHandle(_owner_t* Owner, UINT Length, LPCSTR Value): pOwner(Owner) { HandleCreate<String, String>(&pObject, new String(Length, Value)); }
	VariableHandle(_owner_t* Owner, UINT Length, LPCWSTR Value): pOwner(Owner) { HandleCreate<String, String>(&pObject, new String(Length, Value)); }
	VariableHandle(_owner_t* Owner, String* Value): pOwner(Owner) { HandleCreate<String, String>(&pObject, Value); }
	VariableHandle(_owner_t* Owner, Handle<String> const& Handle): pOwner(Owner) { HandleCreate<String, String>(&pObject, Handle.pObject); }
	~VariableHandle() { HandleDestroy(pObject); }

	// Access
	operator String*()const { return pObject; }
	operator Handle<String>()const { return pObject; }
	String* operator->()const { return pObject; }
	String* Get()const { return pObject; }

	// Comparison
	BOOL operator==(decltype(nullptr))const { return !(pObject&&pObject->GetLength()); }
	BOOL operator==(LPCSTR Value)const
		{
		LPCTSTR pstr1=pObject? pObject->Begin(): nullptr;
		return StringCompare(pstr1, Value)==0;
		}
	BOOL operator==(LPCWSTR Value)const
		{
		LPCTSTR pstr1=pObject? pObject->Begin(): nullptr;
		return StringCompare(pstr1, Value)==0;
		}
	BOOL operator==(Handle<String> const& Handle)const
		{
		LPCTSTR pstr1=pObject? pObject->Begin(): nullptr;
		LPCTSTR pstr2=Handle? Handle->Begin(): nullptr;
		return StringCompare(pstr1, pstr2)==0;
		}
	inline BOOL operator!=(decltype(nullptr))const { return (pObject&&pObject->GetLength()); }
	inline BOOL operator!=(LPCSTR Value)const { return !operator==(Value); }
	inline BOOL operator!=(LPCWSTR Value)const { return !operator==(Value); }
	inline BOOL operator!=(Handle<String> const& Handle)const { return !operator==(Handle); }
	inline BOOL operator>(decltype(nullptr))const { return (pObject&&pObject->GetLength()); }
	BOOL operator>(LPCSTR Value)const
		{
		LPCTSTR pstr1=pObject? pObject->Begin(): nullptr;
		return StringCompare(pstr1, Value)>0;
		}
	BOOL operator>(LPCWSTR Value)const
		{
		LPCTSTR pstr1=pObject? pObject->Begin(): nullptr;
		return StringCompare(pstr1, Value)>0;
		}
	BOOL operator>(Handle<String> const& Object)const
		{
		LPCTSTR pstr1=pObject? pObject->Begin(): nullptr;
		LPCTSTR pstr2=Object? Object->Begin(): nullptr;
		return StringCompare(pstr1, pstr2)>0;
		}
	BOOL operator>=(decltype(nullptr))const { return true; }
	BOOL operator>=(LPCSTR Value)const
		{
		LPCTSTR pstr1=pObject? pObject->Begin(): nullptr;
		return StringCompare(pstr1, Value)>=0;
		}
	BOOL operator>=(LPCWSTR Value)const
		{
		LPCTSTR pstr1=pObject? pObject->Begin(): nullptr;
		return StringCompare(pstr1, Value)>=0;
		}
	BOOL operator>=(Handle<String> const& Object)const
		{
		LPCTSTR pstr1=pObject? pObject->Begin(): nullptr;
		LPCTSTR pstr2=Object? Object->Begin(): nullptr;
		return StringCompare(pstr1, pstr2)>=0;
		}
	BOOL operator<(decltype(nullptr))const { return false; }
	BOOL operator<(LPCSTR Value)const
		{
		LPCTSTR pstr1=pObject? pObject->Begin(): nullptr;
		return StringCompare(pstr1, Value)<0;
		}
	BOOL operator<(LPCWSTR Value)const
		{
		LPCTSTR pstr1=pObject? pObject->Begin(): nullptr;
		return StringCompare(pstr1, Value)<0;
		}
	BOOL operator<(Handle<String> const& Object)const
		{
		LPCTSTR pstr1=pObject? pObject->Begin(): nullptr;
		LPCTSTR pstr2=Object? Object->Begin(): nullptr;
		return StringCompare(pstr1, pstr2)<0;
		}
	BOOL operator<=(decltype(nullptr))const { return !(pObject&&pObject->GetLength()); }
	BOOL operator<=(LPCSTR Value)const
		{
		LPCTSTR pstr1=pObject? pObject->Begin(): nullptr;
		return StringCompare(pstr1, Value)<=0;
		}
	BOOL operator<=(LPCWSTR Value)const
		{
		LPCTSTR pstr1=pObject? pObject->Begin(): nullptr;
		return StringCompare(pstr1, Value)<=0;
		}
	BOOL operator<=(Handle<String> const& Object)const
		{
		LPCTSTR pstr1=pObject? pObject->Begin(): nullptr;
		LPCTSTR pstr2=Object? Object->Begin(): nullptr;
		return StringCompare(pstr1, pstr2)<=0;
		}

	// Modification
	VariableHandle& operator=(decltype(nullptr))
		{
		if(!pObject)
			return *this;
		HandleClear(&pObject);
		Changed(pOwner, pObject);
		return *this;
		}
	VariableHandle& operator=(INT Resource) { return operator=(GetResourceString(Resource)); }
	VariableHandle& operator=(LPCSTR Value)
		{
		if(pObject)
			{
			if(StringCompare(pObject->Begin(), Value)==0)
				return *this;
			pObject->Release();
			pObject=nullptr;
			}
		if(Value&&Value[0])
			{
			pObject=new String(Value);
			pObject->AddReference();
			}
		Changed(pOwner, pObject);
		return *this;
		}
	VariableHandle& operator=(LPCWSTR Value)
		{
		if(pObject)
			{
			if(StringCompare(pObject->Begin(), Value)==0)
				return *this;
			pObject->Release();
			pObject=nullptr;
			}
		if(Value&&Value[0])
			{
			pObject=new String(Value);
			pObject->AddReference();
			}
		Changed(pOwner, pObject);
		return *this;
		}
	VariableHandle& operator=(Handle<String> const& Handle)
		{
		if(pObject&&Handle)
			{
			if(StringCompare(pObject->Begin(), Handle->Begin())==0)
				return *this;
			}
		HandleAssign(&pObject, Handle.pObject);
		Changed(pOwner, pObject);
		return *this;
		}
	Handle<String> operator+(LPCSTR Append)
		{
		if(!pObject)
			return new String(Append);
		return new String("%s%s", pObject->Begin(), Append);
		}
	Handle<String> operator+(LPCWSTR Append)
		{
		if(!pObject)
			return new String(Append);
		return new String("%s%s", pObject->Begin(), Append);
		}
	Handle<String> operator+(String* Append)
		{
		if(!pObject)
			return Append;
		if(!Append)
			return pObject;
		return new String("%s%s", pObject->Begin(), Append->Begin());
		}
	Event<_owner_t, Handle<String>> Changed;

private:
	// Common
	String* pObject;
	_owner_t* pOwner;
};
