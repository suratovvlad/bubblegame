#ifndef __VIRTUALFILESYSTEM_H__
#define __VIRTUALFILESYSTEM_H__

#ifdef _MSC_VER
#pragma once
#endif

#include "IO/FileSystem.h"
#include "RefCounter.h"

namespace IO {

/// ����������� �������� �������.
/// ������������� ���������� ������ ������� � �������� ����������.
///
/// ��� ���� ����������� ������������ �������� ����� ������������ ������.
/// ����������� ������������t ���������� �����. ��� ������ ������������ ������ �� �����
/// ��������� /Users/xxxx/Library/... ������� ������������ fopen � ����������� �������.
class VirtualFileSystem : public RefCounter {
public:
	VirtualFileSystem();

	/// ������������� ���������� ��� ������, � ������� ����� �������� ������� OpenWrite/OpenUpdate
	void SetWriteDirectory(const std::string& dir);

	/// ���������� ���������� ��� ������
	const std::string& GetWriteDirectory() const;

	/// ��������� �������� �������.
	/// ����� ����� �������������� � ������� ������������ �������� ������.
	void Mount(FileSystem* fs);

	/// ��������� ���������� � ������� �� �����
	void MountDirectory(const std::string& path);

	/// ��������� zip �����
	void MountZip(const std::string& filename, const std::string& innerPath);

	/// ��������� ������������� �����
	bool FileExists(const std::string& filename) const;

	/// ���� ����� �� �����
	void FindFiles(const std::string& filespec, std::vector<std::string>& result) const;

	/// ���������� ����� ��������� ������ �����
	time_t GetLastWriteTime(const std::string& filename) const;

	/// ������� ���� �� ���������� ��� ������
	void RemoveFile(const std::string& filename);

	/// ��������� ���� ��� ������, ������� �������� ���������� ��� ������
	InputStreamPtr OpenRead(const std::string& filename);

	/// ��������� ���� ��� ������ � ���������� ��� ������
	OutputStreamPtr OpenWrite(const std::string& filename);

	/// ��������� ���� ��� ���������� (�� ������� ����������) � ���������� ��� ������
	StreamPtr OpenUpdate(const std::string& filename);

private:
	typedef std::list<FileSystemPtr> FileSystems;

	FileSystems _systems;

private:
	DISALLOW_COPY_AND_ASSIGN(VirtualFileSystem);
};

} // namespace IO


namespace Core {
	extern IO::VirtualFileSystem fileSystem;
}

#endif // __VIRTUALFILESYSTEM_H__
