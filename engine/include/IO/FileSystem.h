#ifndef __FILESYSTEM_H__
#define __FILESYSTEM_H__

#ifdef _MSC_VER
#pragma once
#endif

#include "IO/Stream.h"
#include "RefCounter.h"

namespace IO {

class FileSystem : public RefCounter {
public:
	FileSystem(const std::string& root);

	const std::string& GetRoot() const { return _root; }

	virtual bool FileExists(const std::string& filename) const = 0;

	virtual void FindFiles(const std::string& filespec, std::vector<std::string>& result) const = 0;

	virtual time_t GetLastWriteTime(const std::string& filename) const = 0;

	virtual InputStreamPtr OpenRead(const std::string& filename) = 0;

	virtual OutputStreamPtr OpenWrite(const std::string& filename) = 0;

	virtual StreamPtr OpenUpdate(const std::string& filename) = 0;

	virtual void RemoveFile(const std::string& filename) = 0;

private:
	std::string _root;

private:
	DISALLOW_COPY_AND_ASSIGN(FileSystem);
};

typedef boost::intrusive_ptr<FileSystem> FileSystemPtr;


} // namespace IO

#endif // __FILESYSTEM_H__
