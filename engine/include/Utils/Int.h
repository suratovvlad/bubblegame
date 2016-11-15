#ifndef __UTILS_INT_H__
#define __UTILS_INT_H__

#pragma once

#include <stdint.h>

/// ����������� �����, ���������� ������� ������ �� ���������� ���� int
/// � ��������� ������� � ���������������� ������� ��������
/// ����� � ��������� ������������� � �������.
class Int
{
public:

	/// ������������ �������� ���� int
	static const int MAX_VALUE = 2147483647;

	/// ����������� �������� ���� int
	static const int MIN_VALUE = -2147483647 - 1;

	/// ������ � ���������� ������� ������������� �������� ���� int
	static const std::string MAX_VALUE_IMAGE;

	/// ������ � ���������� ������� ������������ �������� ���� int
	static const std::string MIN_VALUE_IMAGE;

	/// ������ ������ ����� �� ������ �� ��� ���������� ������.
	static int Parse(const std::string& image);
	static int Parse(const char* image);

	static long ParseLong(const std::string& image);
	static long ParseLong(const char* image);

	static long long ParseLongLong(const std::string& image);
	static long long ParseLongLong(const char* image);

	static uint32_t ParseUint(const std::string& image);
	static uint32_t ParseUint(const char* image);

	/// ������ ������ ����� �� ������ �� ��� ������������ ������.
	/// ������� � ������� ���� �����������.
	static int Parse8(const std::string& image);
	static int64_t Parse8_64(const std::string& image);

	/// ������ ������ ����� �� ��� ����������������� ������.
	static int ParseHex(const std::string& image);

	/// ��������� ������ � ������������ ����� ���� int.
	static std::string ToString(int value);

	/// ������� ����������������� ����� � ������ � � ������������.
	static char ToHexChar(int value);

	/// ��������� ������ � ����������������� ������� ����� ���� int.
	/// ������ ����������������� �����, �������� ��������/��������� ���.
	static std::string ToHexString(int value);

	/// ��������� ����� ���������� ������ ����� ���� int.
	static int Length(int value);

	/// ���������� ����� � ����������� ������� ������� ������
	static int Pow2(int i);
};

#endif // __UTILS_INT_H__
