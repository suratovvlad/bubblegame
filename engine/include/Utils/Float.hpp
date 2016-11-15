#pragma once

//
// ����������� �����, ���������� ������� ������ �� ���������� ���� float
// � ��������� ������� � ���������������� ������� ��������
// ����� � ��������� ������������� � �������.
//
class Float
{
public:

    static std::string ToString(float value);

	//
	// ��������� ������ � ������������ ����� ���� float � ����������� (� ������� %e).
	//
	static std::string ToStringE(float value);

	//
	// ������� ����������� ������������� ����� ���� -?\d+\.\d+ � ���� �����.
	// ���������� �� �������������, �����, ����� �� � ����� �� �����������,
	// ���� �������� ������ �����. ����� ����� ���� �� ������ ���� ������ 7.
	//
	static float ParseFixed(const std::string& image);
	static float ParseFixed(const char* image);

	static double ParseDouble(const std::string& image);
	static double ParseDouble(const char* image);

	//
	// ��������� ������ � ������ �������������� ����� ���� float.
	// ������: �������������, ��� ��� ����� ������, ����� ������������
	// ����� (��� �������� � ��� ������ ���������), ����� ����� ����� -
	// ���� ������������� �����.
	//
	static std::string ToStringExact(float value);

	//
	// ��������� ����� ���� float �� ��� �����������, ����������� ToStringExact.
	//
	static float ParseExact(const std::string& image);

	//
	// ��������� ����� ���� float �� ��� �����������, �� �����:
	// ��� �� ������ � ������������� ������ (������������ ParseFixed),
	// ��� �� ������ � ������ (������������ ParseExact).
	//
	static float Parse(const std::string& image);

	//
	// ��������� ������ � ������������ ����� ���� float
	// � ������� � ������������� ������.
	// ���������� ���� ����� ����� - ������������ ��� ParseFixed.
	//
	// ����������� �� ����� �����, ����� ParseFixed ������ ��� ��������� -
	// ���� ��� �� ������ �� 0.000001 �� 999999.9.
	//
	static std::string ToStringF(float value);
};
