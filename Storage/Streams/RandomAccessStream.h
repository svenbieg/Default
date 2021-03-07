//======================
// RandomAccessStream.h
//======================

#pragma once


//=======
// Using
//=======

#include "InputStream.h"
#include "OutputStream.h"


//===========
// Namespace
//===========

namespace Storage {
	namespace Streams {


//======================
// Random-Access-Stream
//======================

class RandomAccessStream: public InputStream, public OutputStream
{
public:
	// Con-/Destructors
	virtual ~RandomAccessStream() {}

protected:
	// Con-/Destructors
	RandomAccessStream() {}
};

}}
