#ifndef __FILE_FILEMETHODS_H__
#define __FILE_FILEMETHODS_H__

#pragma once

#include "IO/Stream.h"

#include <string>

#ifdef CopyFile
#undef CopyFile
#endif

#ifdef MoveFile
#undef MoveFile
#endif

enum class FileNameOp {
	Resolve,
	DontResolve
};

enum class ErrorMode {
	ReturnCode,
	ThrowException
};

namespace File {

/// ��������� ������������� ����� � �������� �������
bool ExistsInFs(const std::string& filename);

/// �������� ���� � �������� �������.
/// ���� ���� ����������, �� �� �� ���������������� � ������������ false.
bool CopyFile(const std::string& from, const std::string& to);

/// ���������� ���� � �������� �������.
/// ���� ���� ����������, �� �� �� ���������������� � ������������ false.
bool MoveFile(const std::string& from, const std::string& to);

/// ������� ���� � �������� �������
bool RemoveFile(const std::string& file);

/// ����������� ��� ����� � ����������� �������� ������� � ������ �������� ���������� �����
std::string ResolveFileName(const std::string& filename);

/// ��������� ���� ��� ������ � ����������� �������� �������
IO::InputStreamPtr OpenRead(const std::string& filename, FileNameOp op = FileNameOp::DontResolve, ErrorMode err = ErrorMode::ThrowException);

/// ��������� ���������� ����� �� ����������� �������� �������
bool LoadFile(const std::string& filename, std::vector<uint8_t>& contents, FileNameOp op = FileNameOp::DontResolve);

} // namespace File

#endif // __FILE_FILEMETHODS_H__
