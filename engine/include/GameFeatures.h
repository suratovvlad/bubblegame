#ifndef _GAMEFEATURES_H_
#define _GAMEFEATURES_H_

#include "Render/Texture.h"

bool SaveScreenshot(const std::string &name, Render::Texture **tex, const IRect &rect, const std::string &sigPath = "", const IPoint &sigPos = IPoint(0, 0));
// ��������� �������� � ���� �� �����, ���� name �������
// ��������� �������� � ��������, ���� tex �� NULL
// �������� �� �������� ������� � ������� sigPos, ���� sigPath �� ����
// ���������� true, ���� name ������� � ���� ������ ����������
// ���� �������� ���������, �� *tex �� NULL, ����� - NULL

#endif
