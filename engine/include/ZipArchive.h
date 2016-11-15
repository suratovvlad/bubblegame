#ifndef __ZIPARCHIVE_H__
#define __ZIPARCHIVE_H__

#pragma once

///
/// ����� ��� ������ Zip �������.
///
/// � ������ ������ ������� ���������� std::runtime_error.
///
class ZipArchive {
public:
	ZipArchive();
	ZipArchive(const std::string& filename);
    ZipArchive(const IO::InputStreamPtr& stream);
	
	virtual ~ZipArchive();
	
	void Open(const std::string& filename);
    void Open(const IO::InputStreamPtr& stream);
		/// ��������� �����. �������� ����� ����� ������������� �����������

	void Close();
		/// ��������� �����. ��� �� ���������� � �����������
	bool IsOpen() const;
		/// ���������, ������ �� �����
	
	void ListFiles(std::vector<std::string>& vec);
		/// ���������� ������ ���� ������, ������������ � ������
	bool FileExists(const std::string& filename);
		/// ���������, ���������� �� ���� � ������
	void ReadFile(const std::string& filename, std::vector<uint8_t>& data);
		/// ������ ���������� ����� � �����. ��������� � ������ ��������� ���������� �����

private:	
	ZipArchive(const ZipArchive&);
	ZipArchive& operator=(const ZipArchive&);
		// ��������� ����������� � ������������ ����������� ������

private:
	struct Impl;
	std::auto_ptr<Impl> _pimpl;
		// ���������� ����������
};

#endif // __ZIPARCHIVE_H__
