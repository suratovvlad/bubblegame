#ifndef __STREAM_H__
#define __STREAM_H__

#ifdef _MSC_VER
#pragma once
#endif

#include "RefCounter.h"

#define DISALLOW_COPY_AND_ASSIGN(Class) \
	Class(const Class&); \
	Class& operator=(const Class&)

namespace IO {

enum class Origin {
	Beginning,
	Current,
	End
};

class OutputStream;

class Seekable : public RefCounter {
public:
	Seekable() { }

	virtual void Seek(int offset, Origin origin) = 0;

	virtual size_t Tell() const = 0;

private:
	DISALLOW_COPY_AND_ASSIGN(Seekable);
};


class InputStream : virtual public Seekable {
public:
	virtual size_t Read(void* buffer, size_t length) = 0;

	void ReadAllBytes(std::vector<uint8_t>& data);

	void ReadAllBytes(OutputStream* stream);
};

typedef boost::intrusive_ptr<InputStream> InputStreamPtr;


class OutputStream : virtual public Seekable {
public:
	virtual size_t Write(const void* buffer, size_t length) = 0;

	virtual void Flush() = 0;

	void WriteAllBytes(const std::vector<uint8_t>& data);

	void WriteAllBytes(InputStream* stream);
};

typedef boost::intrusive_ptr<OutputStream> OutputStreamPtr;


class Stream : public InputStream, public OutputStream {
public:
};

typedef boost::intrusive_ptr<Stream> StreamPtr;

} // namespace IO

#endif // __STREAM_H__
