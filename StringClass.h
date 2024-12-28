//===============
// StringClass.h
//===============

#pragma once


//=======
// Using
//=======

#include <utility>
#include "Handle.h"
#include "StringHelper.h"


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
public:
	// Con-/Destructors
	~String()
		{
		if(m_Buffer)
			delete m_Buffer;
		}
	static Handle<String> Create(LPCSTR Value);
	static Handle<String> Create(LPCWSTR Value);
	static Handle<String> Create(UINT Length, nullptr_t);
	static Handle<String> Create(UINT Length, LPCSTR Value);
	static Handle<String> Create(UINT Length, LPCWSTR Value);
	static Handle<String> Create(LPCSTR Format, VariableArguments const& Arguments);
	template <class... _args_t> static Handle<String> Create(LPCSTR Format, _args_t... Arguments);

	// Access
	inline LPCTSTR Begin()const { return m_Buffer; }
	inline BOOL Contains(LPCSTR Value, BOOL CaseSensitive=true)
		{
		return StringHelper::Find(m_Buffer, Value, nullptr, CaseSensitive);
		}
	inline BOOL Contains(LPCWSTR Value, BOOL CaseSensitive=true)
		{
		return StringHelper::Find(m_Buffer, Value, nullptr, CaseSensitive);
		}
	inline UINT GetLength()const { return StringHelper::Length(m_Buffer); }
	inline BOOL IsEmpty()const { return !StringHelper::IsSet(m_Buffer); }
	template <class... _args_t> inline UINT Scan(LPCSTR Format, _args_t... Arguments)
		{
		UnknownClass args[]={ Arguments... };
		VariableArguments vargs(args, TypeHelper::ArraySize(args));
		return StringHelper::ScanArgs(m_Buffer, Format, vargs);
		}
	Handle<String> ToString()override;

	// Comparison
	inline BOOL operator==(String const& String)const { return StringHelper::Compare(m_Buffer, String.m_Buffer)==0; }
	inline BOOL operator!=(String const& String)const { return StringHelper::Compare(m_Buffer, String.m_Buffer)!=0; }
	inline BOOL operator>(String const& String)const { return StringHelper::Compare(m_Buffer, String.m_Buffer)>0; }
	inline BOOL operator>=(String const& String)const { return StringHelper::Compare(m_Buffer, String.m_Buffer)>=0; }
	inline BOOL operator<(String const& String)const { return StringHelper::Compare(m_Buffer, String.m_Buffer)<0; }
	inline BOOL operator<=(String const& String)const { return StringHelper::Compare(m_Buffer, String.m_Buffer)<=0; }

	// Operators
	Handle<String> Replace(LPCSTR Find, LPCSTR Replace, BOOL CaseSensitive=true, BOOL Repeat=false);

private:
	// Con-/Destructors
	String(UINT Length, nullptr_t): m_Buffer(new TCHAR[Length+1]) {}
	String(UINT Length, LPCSTR Value): m_Buffer(nullptr)
		{
		UINT len=StringHelper::Length(Value, Length);
		m_Buffer=new TCHAR[len+1];
		StringHelper::Copy(m_Buffer, len+1, Value);
		}
	String(UINT Length, LPCWSTR Value): m_Buffer(nullptr)
		{
		UINT len=StringHelper::Length(Value, Length);
		m_Buffer=new TCHAR[len+1];
		StringHelper::Copy(m_Buffer, len+1, Value);
		}
	String(LPCSTR Format, VariableArguments const& Arguments): m_Buffer(nullptr)
		{
		UINT len=StringHelper::PrintArgs((LPSTR)nullptr, 0, Format, Arguments);
		m_Buffer=new TCHAR[len+1];
		StringHelper::PrintArgs(m_Buffer, len+1, Format, Arguments);
		}

	// Common
	LPTSTR m_Buffer;
};


//===============
// String-Handle
//===============

template <>
class Handle<String>: public HandleBase<String>
{
public:
	// Using
	using _base_t=HandleBase<String>;

	// Con-/Destructors
	Handle(): _base_t(nullptr) {}
	Handle(nullptr_t): _base_t(nullptr) {}
	Handle(String* Object): _base_t(Object) {}
	Handle(Handle const& Copy): _base_t(Copy) {}
	Handle(Handle&& Move)noexcept: _base_t(Move.m_Object) { Move.m_Object=nullptr; }
	Handle(LPCSTR Value) { Create(Value); }
	Handle(LPCWSTR Value) { Create(Value); }
	template <class... _args_t> Handle(LPCSTR Format, _args_t... Arguments)
		{
		UnknownClass args[]={ Arguments... };
		VariableArguments vargs(args, TypeHelper::ArraySize(args));
		Create(Format, vargs);
		}

	// Access
	inline operator BOOL()const override { return m_Object&&m_Object->GetLength(); }

	// Comparison
	inline BOOL operator==(nullptr_t)const override { return !operator BOOL(); }
	inline BOOL operator==(LPCSTR Value)const
		{
		auto str=m_Object? m_Object->Begin(): nullptr;
		return StringHelper::Compare(str, Value)==0;
		}
	inline BOOL operator==(LPCWSTR Value)const
		{
		auto str=m_Object? m_Object->Begin(): nullptr;
		return StringHelper::Compare(str, Value)==0;
		}
	inline BOOL operator==(String* Object)const override
		{
		auto str1=m_Object? m_Object->Begin(): nullptr;
		auto str2=Object? Object->Begin(): nullptr;
		return StringHelper::Compare(str1, str2)==0;
		}
	inline BOOL operator!=(nullptr_t)const { return !operator==(nullptr); }
	inline BOOL operator!=(LPCSTR Value)const { return !operator==(Value); }
	inline BOOL operator!=(LPCWSTR Value)const { return !operator==(Value); }
	inline BOOL operator!=(String* Object)const { return !operator==(Object); }
	inline BOOL operator>(nullptr_t)const { return (m_Object&&m_Object->GetLength()); }
	inline BOOL operator>(LPCSTR Value)const
		{
		auto str=m_Object? m_Object->Begin(): nullptr;
		return StringHelper::Compare(str, Value)>0;
		}
	inline BOOL operator>(LPCWSTR Value)const
		{
		auto str=m_Object? m_Object->Begin(): nullptr;
		return StringHelper::Compare(str, Value)>0;
		}
	inline BOOL operator>(Handle<String> const& Object)const
		{
		auto str1=m_Object? m_Object->Begin(): nullptr;
		auto str2=Object? Object->Begin(): nullptr;
		return StringHelper::Compare(str1, str2)>0;
		}
	inline BOOL operator>=(nullptr_t)const { return true; }
	inline BOOL operator>=(LPCSTR Value)const
		{
		auto str=m_Object? m_Object->Begin(): nullptr;
		return StringHelper::Compare(str, Value)>=0;
		}
	inline BOOL operator>=(LPCWSTR Value)const
		{
		auto str=m_Object? m_Object->Begin(): nullptr;
		return StringHelper::Compare(str, Value)>=0;
		}
	inline BOOL operator>=(Handle<String> const& Object)const
		{
		auto str1=m_Object? m_Object->Begin(): nullptr;
		auto str2=Object? Object->Begin(): nullptr;
		return StringHelper::Compare(str1, str2)>=0;
		}
	inline BOOL operator<(nullptr_t)const { return false; }
	inline BOOL operator<(LPCSTR Value)const
		{
		auto str=m_Object? m_Object->Begin(): nullptr;
		return StringHelper::Compare(str, Value)<0;
		}
	inline BOOL operator<(LPCWSTR Value)const
		{
		auto str=m_Object? m_Object->Begin(): nullptr;
		return StringHelper::Compare(str, Value)<0;
		}
	inline BOOL operator<(Handle<String> const& Object)const
		{
		auto str1=m_Object? m_Object->Begin(): nullptr;
		auto str2=Object? Object->Begin(): nullptr;
		return StringHelper::Compare(str1, str2)<0;
		}
	inline BOOL operator<=(nullptr_t)const { return !(m_Object&&m_Object->GetLength()); }
	inline BOOL operator<=(LPCSTR Value)const
		{
		auto str=m_Object? m_Object->Begin(): nullptr;
		return StringHelper::Compare(str, Value)<=0;
		}
	inline BOOL operator<=(LPCWSTR Value)const
		{
		auto str=m_Object? m_Object->Begin(): nullptr;
		return StringHelper::Compare(str, Value)<=0;
		}
	inline BOOL operator<=(Handle<String> const& Object)const
		{
		auto str1=m_Object? m_Object->Begin(): nullptr;
		auto str2=Object? Object->Begin(): nullptr;
		return StringHelper::Compare(str1, str2)<=0;
		}

	// Assignment
	inline Handle& operator=(nullptr_t) { Clear(); return *this; }
	inline Handle& operator=(LPCSTR Value) { Set(Value); return *this; }
	inline Handle& operator=(LPCWSTR Value) { Set(Value); return *this; }
	inline Handle& operator=(Handle const& Copy) { HandleBase::Set(Copy.m_Object); return *this; }
	VOID Set(LPCSTR Value)
		{
		if(m_Object)
			{
			if(StringHelper::Compare(m_Object->Begin(), Value)==0)
				return;
			Clear();
			}
		if(Value&&Value[0])
			Create(Value);
		}
	VOID Set(LPCWSTR Value)
		{
		if(m_Object)
			{
			if(StringHelper::Compare(m_Object->Begin(), Value)==0)
				return;
			Clear();
			}
		if(Value&&Value[0])
			Create(Value);
		}

	// Operators
	inline Handle<String> operator+(LPCSTR Append)
		{
		if(!m_Object)
			return String::Create(Append);
		return String::Create("%s%s", m_Object->Begin(), Append);
		}
	inline Handle<String> operator+(LPCWSTR Append)
		{
		if(!m_Object)
			return String::Create(Append);
		return String::Create("%s%s", m_Object->Begin(), Append);
		}
	inline Handle<String> operator+(String* Append)
		{
		if(!m_Object)
			return Append;
		if(!Append)
			return m_Object;
		return String::Create("%s%s", m_Object->Begin(), Append->Begin());
		}

private:
	// Con-/Destructors
	inline VOID Create(LPCSTR Value)
		{
		auto str=String::Create(Value);
		_base_t::Create(str);
		}
	inline VOID Create(LPCWSTR Value)
		{
		auto str=String::Create(Value);
		_base_t::Create(str);
		}
	inline VOID Create(LPCSTR Format, VariableArguments const& Arguments)
		{
		auto str=String::Create(Format, Arguments);
		_base_t::Create(str);
		}
};


//==================
// Con-/Destructors
//==================

inline Handle<String> String::Create(LPCSTR Value)
{
return new String(0, Value);
}

inline Handle<String> String::Create(LPCWSTR Value)
{
return new String(0, Value);
}

inline Handle<String> String::Create(UINT Length, nullptr_t)
{
return new String(Length, nullptr);
}

inline Handle<String> String::Create(UINT Length, LPCSTR Value)
{
return new String(Length, Value);
}

inline Handle<String> String::Create(UINT Length, LPCWSTR Value)
{
return new String(Length, Value);
}

inline Handle<String> String::Create(LPCSTR Format, VariableArguments const& Arguments)
{
return new String(Format, Arguments);
}

template <class... _args_t> inline Handle<String> String::Create(LPCSTR Format, _args_t... Arguments)
{
UnknownClass args[]={ Arguments... };
VariableArguments vargs(args, TypeHelper::ArraySize(args));
return new String(Format, vargs);
}
