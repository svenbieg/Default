//=================
// StringClass.cpp
//=================

#include "pch.h"


//=======
// Using
//=======

#include <stdio.h>
#include <stdarg.h>
#include "CharHelper.h"
#include "StringClass.h"

using namespace Collections;


//========
// Access
//========

BOOL String::Contains(Handle<String> hstr, BOOL bcs)
{
if(!hstr)
	return false;
return StringContains(pBuffer, hstr->Begin(), 0, 0, bcs);
}

Handle<String> String::Get(Handle<String> hkey)
{
if(hkey==nullptr)
	return nullptr;
UINT ukeylen=hkey->GetLength();
if(ukeylen==0)
	return nullptr;
for(LPCTSTR pstr=pBuffer; pstr[0]!=0; )
	{
	UINT upos=0;
	if(!StringFind(pstr, hkey->Begin(), &upos))
		return nullptr;
	pstr+=upos+ukeylen;
	if(pstr[0]=='=')
		{
		pstr++;
		UINT ulen=0;
		while(!CharIsBreak(pstr[ulen]))
			ulen++;
		if(ulen==0)
			return new String("");
		return new String(ulen, pstr);
		}
	}
return nullptr;
}

Handle<String> String::LowerCase()const
{
Handle<String> hstr=new String(pBuffer);
StringLowerCase((LPTSTR)hstr->Begin(), 0, 0);
return hstr;
}

Handle<StringList> String::Split(CHAR c)
{
Handle<StringList> list=new StringList();
if(!pBuffer)
	return list;
UINT pos=0;
while(pBuffer[pos])
	{
	UINT len=0;
	while(pBuffer[pos+len])
		{
		if(CharCompare(pBuffer[pos+len], c)==0)
			break;
		len++;
		}
	if(len)
		{
		Handle<String> str=new String(len, &pBuffer[pos]);
		list->Append(str);
		}
	pos+=len+1;
	}
return list;
}

Handle<String> String::UpperCase()const
{
Handle<String> hstr=new String(pBuffer);
StringUpperCase((LPTSTR)hstr->Begin(), 0, 0);
return hstr;
}

SIZE_T String::WriteToStream(Handle<OutputStream> hstream)
{
UINT ulen=StringLength(pBuffer);
if(!hstream)
	return sizeof(UINT)+ulen;
SIZE_T usize=hstream->Write(&ulen, sizeof(UINT));
if(!ulen)
	return usize;
usize+=hstream->Write(pBuffer, ulen*sizeof(TCHAR));
return usize;
}


//==============
// Modification
//==============

SIZE_T String::ReadFromStream(Handle<InputStream> hstream)
{
if(pBuffer)
	return 0;
UINT ulen=0;
SIZE_T usize=hstream->Read(&ulen, sizeof(UINT));
if(!ulen)
	return usize;
StringSetSize(&pBuffer, nullptr, (ulen+1)*sizeof(TCHAR));
usize+=hstream->Read(pBuffer, ulen*sizeof(TCHAR));
pBuffer[ulen]=0;
return usize;
}
