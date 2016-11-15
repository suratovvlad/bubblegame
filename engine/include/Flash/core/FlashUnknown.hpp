#pragma once

#include "GCRef.h"

/*
	����� ����������� ����� ����������� ����������� ��������� ���������� ����� �����, ��� ������������� dynamic_cast,
	�� ���� ���� ��� �� ��� ���� ��� ����� ����������� ���������� ��������� ��������� IUnknown(https://msdn.microsoft.com/en-us/library/windows/desktop/ms680509%28v=vs.85%29.aspx),
	������ ������ �������������� QueryInterfeace � ���������� IFlashUnknown, ���� ������� ������� �� ��������� �� ����� �� ���,
	�������� �� ����������� ������

	IPrototype* l_objClone = l_obj->Clone();
	� ����������� ���� ������ � ���� IPrototype*, �� ���������� ��� ��� ���������� �� ����� ���������� �� IFlashUnknown,
	�� ����� ���������� ������ ��� ���������� ��� ������ ������:

	IFlashSpirte* l_objCloneSprite =  l_objClone->Sprite();
	�� ���������� ��� ����� ���� �� �������� � ���

	IFlashSpirte* l_objCloneSprite =  dynamic_cast<IFlashSpirte*>l_objClone;

	� ��� ���� ��������� ��, �� dynamic_cast ��� �� ���� ����� �� ������ �� �������, ������ ��� � ������ ���� �� �������� strcmp, � �� ������ �� ������� �� rtti
	������� ����� � �� ������������ (�������� ������ gcc ����������� -fno-rtti) ��� ���������� ������ ������������� ������


	����� ������� ��� ����� �������������� ������������ ����� ����������� � ��� ���������� ������� ������ ����� �������:

	class CFlashClass: public FlashDisplayObject<IMovieClip>, public IPrototype
	{
		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(IPrototype)
			INTERFACE_ENTRY(IFlashMovieClip)
			INTERFACE_ENTRY(IFlashSprite)
			INTERFACE_ENTRY(IFlashDisplayObject)
		END_INTERFACE_MAP()
		....
	}

	��� ���� ����� ������� ������ ������ CFlashClass, ����������� ��������� �����������:

	IFlashDisplayObject* l_obj = new CFlashUnknown<CFlashClass> 

	�� ����� ���������� ������������ ������� ���������� � ���������� ��� ������ GCRef

	��������� ������� ��������� ����������� ����� ���������� �������� �� ��������� ����, � ����� ������� ��� ��� ���� ����� ������� �� � ������������ �� � � ����� ��������,
	�� ��� ��������� ��������, ��� � ������� �������� ������������� ��� ������ �����,
	� �������� ��� ������ ���� ���������� ����� ��������� ������� ����� ����� ���������, ������ ��� ������ � ��������� ��� ����� ����������� � ����� ��� ����������, 
	� ���� �� ��� �������� ������� ������ �� ATL(https://ru.wikipedia.org/wiki/Active_Template_Library)
*/
enum FlashInterfaceIDD
{
	IDD_None = 0,
	IDD_IFlashDisplayObject,
	IDD_IFlashSprite,
	IDD_IPrototype,
	IDD_IFlashRasterSprite,
	IDD_IFlashMovieClip,
	IDD_IFlashText,
	IDD_IFlashParticleEffect,
	IDD_IScrollingContainer
};

#define BEGIN_INTERFACE_MAP() public: \
static bool __HaveInterface(FlashInterfaceIDD _intfidd) \
{\
	static const FlashInterfaceIDD _entries[] = {

#define INTERFACE_ENTRY(i) IDD_##i,

#define END_INTERFACE_MAP() IDD_None};\
	int l_i = 0;\
\
	while(_entries[l_i] != 0)\
	{\
		if(_entries[l_i++] == _intfidd)\
		{\
			return true;\
		};\
	};\
\
	return false;\
};

//-----------------------------------------------------------------------------
template<class T>
class CFlashUnknown: public CGCRef<T>
{
	IPrototype* Prototype()
	{
		if(this->__HaveInterface(IDD_IPrototype))
		{
			return (IPrototype*)this;
		};

		return NULL;
	};

	IFlashDisplayObject* DisplayObject()
	{
		if(this->__HaveInterface(IDD_IFlashDisplayObject))
		{
			return (IFlashDisplayObject*)this;
		};

		return NULL;
	};

	IFlashText* Text()
	{
		if(this->__HaveInterface(IDD_IFlashText))
		{
			return (IFlashText*)this;
		};

		return NULL;
	};

	IFlashRasterSprite* RasterSprite()
	{
		if(this->__HaveInterface(IDD_IFlashRasterSprite))
		{
			return (IFlashRasterSprite*)this;
		};

		return NULL;
	};

	IFlashSprite* Sprite()
	{
		if(this->__HaveInterface(IDD_IFlashSprite))
		{
			return (IFlashSprite*)this;
		};

		return NULL;
	};

	IFlashMovieClip* MovieClip()
	{
		if(this->__HaveInterface(IDD_IFlashMovieClip))
		{
			return (IFlashMovieClip*)this;
		};

		return NULL;
	};

	IFlashParticleEffect* ParticleEffect()
	{
		if(this->__HaveInterface(IDD_IFlashParticleEffect))
		{
			return (IFlashParticleEffect*)this;
		};

		return NULL;
	}

	IScrollingContainer* ScrollingContainer()
	{
		if(this->__HaveInterface(IDD_IScrollingContainer))
		{
			return (IScrollingContainer*)this;
		};

		return NULL;
	}
};
