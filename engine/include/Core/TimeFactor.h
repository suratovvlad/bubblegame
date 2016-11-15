#ifndef _TIMEFACTOR_H_
#define _TIMEFACTOR_H_

namespace Core {

//
// �����-��������� �������, ������� ��������� � �������� �����.
//
class TimeFactor {

public:

	//
	// ����������� �� ���������
	// 
	TimeFactor();

	//
	// ���������� �������� ��������� �������
	//
	float GetValue();

	//
	// ������� ��������� �������� ��������� �������
	// 
	std::string ToString();

	//
	// ��������� ��������� ������� (�������� ��)
	//
	void Increase();

	//
	// ��������� ��������� ������� (��������� ��)
	//
	void Decrease();

	//
	// ������� � ��������� � �������� �� ��������� (1)
	//
	void Reset();

private:

	size_t DEFAULT_SCALE_INDEX;
		// ������ ������� ���������� �� ���������

	size_t _currentScaleIndex;
		// ������� ������ ������� ����������

	std::vector<float> _scales;
		// ������ ���������� �������

};

extern TimeFactor timeFactor;

} // namespace Core

#endif