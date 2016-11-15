#pragma once

#include "IGCRef.h"

//-----------------------------------------------------------------------------
struct IFlashDisplayObject;
struct IFlashSprite;
struct IPrototype;
struct IFlashRasterSprite;
struct IFlashMovieClip;
struct IFlashText;
struct IFlashParticleEffect;
struct IScrollingContainer;

//-----------------------------------------------------------------------------
#if defined(__clang__) || defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnon-virtual-dtor"
#endif

/*
	��������� ������������ ����� �������� � IUnknown(https://msdn.microsoft.com/en-us/library/windows/desktop/ms680509%28v=vs.85%29.aspx)
	��� ���������� ����� �������� ������������ ����� �����������, ����� ������� ���������� ����������� � ����� ������ ������������� ���� ��������� � ������,
	����������� ���� ������� ��� ������������
*/
struct IFlashUnknown: public IGCRef
{
	virtual IPrototype* Prototype() = 0;
	virtual IFlashDisplayObject* DisplayObject() = 0;
	virtual IFlashText* Text() = 0;
	virtual IFlashRasterSprite* RasterSprite() = 0;
	virtual IFlashSprite* Sprite() = 0;
	virtual IFlashMovieClip* MovieClip() = 0;
	virtual IFlashParticleEffect* ParticleEffect() = 0;
	virtual IScrollingContainer* ScrollingContainer() = 0;
};

#if defined(__clang__) || defined(__GNUC__)
#pragma GCC diagnostic pop
#endif
