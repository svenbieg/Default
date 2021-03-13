//==========
// Vector.h
//==========

#pragma once


//=======
// Using
//=======

#include "Storage/Streams/InputStream.h"
#include "Storage/Streams/OutputStream.h"
#include "Storage/Streams/StreamReader.h"
#include "Storage/Streams/StreamWriter.h"
#include "ArrayHelper.h"
#include "VectorIterator.h"


//===========
// Namespace
//===========

namespace Collections {


//========
// Vector
//========

template <class _item_t>
class Vector: public virtual Object
{
private:
	// Using
	using InputStream=::Storage::Streams::InputStream;
	using OutputStream=::Storage::Streams::OutputStream;
	using StreamReader=::Storage::Streams::StreamReader;
	using StreamWriter=::Storage::Streams::StreamWriter;

public:
	// Iterator
	using Iterator=VectorIterator<_item_t>;
	friend Iterator;

	// Con-/Destructors
	Vector(Handle<Vector> Vector): uCount(Vector->GetCount())
		{
		pItems=operator new(uCount*sizeof(_item_t));
		for(SIZE_T u=0; u<uCount; u++)
			new (&pItems[u]) _item_t(Vector->GetAt(u));
		}
	Vector(SIZE_T Count): pItems(nullptr), uCount(Count)
		{
		if(uCount>0)
			pItems=new _item_t[uCount];
		}
	~Vector()
		{
		if(pItems)
			delete [] pItems;
		}

	// Access
	inline _item_t* Begin() { return pItems; }
	inline _item_t const* Begin()const { return pItems; }
	inline Handle<Iterator> First() { return new Iterator(this, 0); }
	inline _item_t& GetAt(SIZE_T Position) { return pItems[Position]; }
	inline _item_t const& GetAt(SIZE_T Position)const { return pItems[Position]; }
	inline SIZE_T GetCount()const { return uCount; }
	SIZE_T PrintToStream(Handle<OutputStream> Stream, LPCSTR Format="%i")
		{
		StreamWriter writer(Stream);
		SIZE_T usize=0;
		usize+=writer.Print("[ ");
		for(SIZE_T u=0; u<uCount; u++)
			{
			if(usize>2)
				usize+=writer.Print(", ");
			usize+=writer.Print(Format, pItems[u]);
			}
		usize+=writer.Print(" ]");
		return usize;
		}
	SIZE_T WriteToStream(Handle<OutputStream> Stream)
		{
		StreamWriter writer(Stream);
		return writer.Write(pItems, uCount*sizeof(_item_t));
		}

	// Modification
	virtual VOID Clear()
		{
		ZeroMemory(pItems, uCount*sizeof(_item_t));
		}
	virtual VOID Fill(_item_t const& Item)
		{
		for(SIZE_T u=0; u<uCount; u++)
			pItems[u]=Item;
		}
	SIZE_T ReadFromStream(Handle<InputStream> Stream)
		{
		StreamReader reader(Stream);
		SIZE_T usize=0;
		usize+=reader.Read(pItems, uCount*sizeof(_item_t));
		return usize;
		}
	virtual BOOL SetAt(SIZE_T Position, _item_t const& Item)
		{
		if(Position>=uCount)
			return false;
		pItems[Position]=Item;
		return true;
		}

protected:
	// Common
	_item_t* pItems;
	SIZE_T uCount;
};

}