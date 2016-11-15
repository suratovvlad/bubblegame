#ifndef __FILESTREAM_H__
#define __FILESTREAM_H__

#ifdef _MSC_VER
#pragma once
#endif

#include "IO/Stream.h"

namespace IO {

enum class AccessMode {
	ReadOnly,
	ReadWrite
};

enum class CreateMode {
	OpenExisting,
	OpenOrCreate,
	CreateAlways
};

class FileStream : public Stream {
public:
	FileStream(const std::string& filename, AccessMode accessMode = AccessMode::ReadOnly, CreateMode createMode = CreateMode::OpenExisting);

	~FileStream();

	void Seek(int offset, Origin origin);

	size_t Tell() const;

	size_t Read(void* buffer, size_t length);

	size_t Write(const void* buffer, size_t length);

	void Flush();

	bool IsValid() const;

private:
	FILE* Open(const std::string& filename, AccessMode accessMode, CreateMode createMode);

private:
	FILE* _fp;
};

typedef boost::intrusive_ptr<FileStream> FileStreamPtr;

} // namespace IO

#endif // __FILESTREAM_H__
