#ifndef __PATH_H__
#define __PATH_H__

#ifdef _MSC_VER
#pragma once
#endif

enum class SpecialFolder {
	LocalDocuments, ///< ���������� ��� ������ ������, ����������� �������������
	LocalData,      ///< ���������� ��� ������ ���������������� ������ ���������� (������� ��� Updates, Caches � ��.)
	LocalUpdates,   ///< ���������� ��� ������ ���������� ����������
	LocalCaches,    ///< ���������� ��� ������ �������������� ������ ���������� (������ ����� ���� �������, �� ���������� � iTunes)
};

namespace IO {

class Path {
public:
	static const std::string DirectorySeparator;
	static const std::string AltDirectorySeparator;
	static const std::string FileExtensionSeparator;

	static std::string Combine(const std::string& part1, const std::string& part2);
	static std::string RemoveExtension(const std::string& path);
	static std::string ChangeExtension(const std::string& path, const std::string& extension);
	static std::string GetDirectoryName(const std::string& path);
	static std::string GetFileName(const std::string& path);
	static void Split(const std::string& path, std::vector<std::string>& parts);
	static std::string Canonicalize(const std::string& path);
	static void MakeSlashesForward(std::string& path);
	static std::string MakeSlashesForwardCopy(const std::string& path);
	static bool MatchesWild(const std::string& path, const std::string& wild);

	/// ���������� ���� � ������ ����������
	static std::string GetSpecialFolderPath(SpecialFolder folder);
};

} // namespace IO

#endif // __PATH_H__
