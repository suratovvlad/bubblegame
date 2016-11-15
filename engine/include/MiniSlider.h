#ifndef __MINISLIDER_H__
#define __MINISLIDER_H__

#pragma once

#include "Render.h"

//
// ����� ������������ - �������, ������� �������������� ��� �������.
//
class MiniSlider
{
public:
	/// �����������
	MiniSlider(IPoint pos, int size, bool isVertical, int begunWidth, int begunHeight);

	/// ������� ������������� ��������� ������� (�� 0 �� 1)
	float GetFactor();

	/// ���������� ������������� ��������� ������� (�� 0 �� 1)
	void SetFactor(float factor);

	/// ���������� �������
	void Draw();

	/// ���������� ������� ����
	bool MouseDown(const IPoint &mousePos);

	/// ���������� �������� ����
	void MouseMove(const IPoint &mousePos);

	/// ���������� ������� ����
	void MouseUp(const IPoint &mousePos);

	/// ���������� ����� ��������
	void SetSize(int size);

	/// ���������� ������� ��������
	void SetPosition(IPoint pos);

private:

	/// ������������/��������������
	bool _isVertical;

	/// ���������� ������ ������� ���� �����, ����� ������� ������������ �������
	IPoint _pos;

	/// ����� �����
	int _size;

	/// ������ �������
	int _begunHeight;

	/// ������ �������
	int _begunWidth;

	/// ������� ������� �������
	int _begunPos;

	/// ������ �� ������
	bool _isMouseDown;

};

#endif // __MINISLIDER_H__
