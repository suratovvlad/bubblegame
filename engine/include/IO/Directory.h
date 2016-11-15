#ifndef __DIRECTORY_H__
#define __DIRECTORY_H__

#ifdef _MSC_VER
#pragma once
#endif

#ifdef SetCurrentDirectory
#undef SetCurrentDirectory
#endif

#ifdef GetCurrentDirectory
#undef GetCurrentDirectory
#endif

#ifdef RemoveDirectory
#undef RemoveDirectory
#endif

namespace IO {

enum class SearchMode {
	TopOnly,
	All
};

class Directory {
public:
	/// ��������� ������������� ����������
	static bool Exists(const std::string& dirname);
	
	/// ������ ��� ������������� � ����, ���� �����-�� �� ��� �� ����������
	static bool CreateDirectories(const std::string& dirname);
	
	/// ������� ���������� � ��� ��������� ����� � �������������
	static bool RemoveDirectory(const std::string& dirname);

	/// �������� ���������� �� ���� ����������
	static bool CopyDirectoryWithContents(const std::string& from, const std::string& to);

	/// ��������� ���������� �� ���� ����������
	static bool MoveDirectoryWithContents(const std::string& from, const std::string& to);

	/// ������������� ������� ���������� ��������
	static bool SetCurrentDirectory(const std::string& dirname);

	/// ���������� ������� ���������� ��������
	static std::string GetCurrentDirectory();
	
	/// ����������� ����� � ���������� � �������������� ������� ��������� ������
	static void EnumerateFiles(const std::string& dirname, std::function<void(const std::string&)> callback, SearchMode mode = SearchMode::TopOnly);

	/// ����������� ������������� � ���������� � �������������� ������� ��������� ������
	static void EnumerateDirectories(const std::string& dirname, std::function<void(const std::string&)> callback, SearchMode mode = SearchMode::TopOnly);
	
	/// ���� ��� ����� � ���������� � ��������� �� ����� � ���������
	static void FindFiles(const std::string& dirname, std::vector<std::string>& files, SearchMode mode = SearchMode::TopOnly);
	
	/// ���� ����� � ���������� �� ����� � ��������� �� ����� � ���������
	static void FindFiles(const std::string& dirname, const std::string& filemask, std::vector<std::string>& files, SearchMode mode = SearchMode::TopOnly);
};

} // namespace IO

#endif // __DIRECTORY_H__
