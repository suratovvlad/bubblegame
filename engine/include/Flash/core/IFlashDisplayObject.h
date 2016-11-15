#pragma once

#include <string>
#include <Utils/Color.h>

#include "IFlashUnknown.h"
#include "IHitTestDelegate.h"
#include "IFlashVisitor.h"

//---------------------------------------------------------------------------
class FlashRender;
class FlashUpdateListener;
struct IFlashCustomDrawOperation;
struct IFlashSprite;

//---------------------------------------------------------------------------
#if defined(__clang__) || defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnon-virtual-dtor"
#endif

struct IFlashDisplayObject: public IFlashUnknown
{
	/**
	* ��������� ������� � �������� ������ ������
	* �� �������������� ��������� � ���������� ����� ����� ��������������� ����������.
	*/
	virtual void render(FlashRender& render) = 0;
	/**
	* ��������� ��������� �������� ��������� �� �������.
	* @param x, y ������ ����� � ������� ��������� ������� �������
	* @see IHitTestDelegate
	*/
	virtual bool hitTest(float x, float y, IHitTestDelegate* hitTestDelegate) = 0;
	/**
	* �������� ���������� ��������������� �������������� � ��������� ������� ���������
	* @return true ���� ������ ����� �������������� ������������� � false - ���� ������ ����
	*/
	virtual bool getBounds(float& left, float& top, float& right, float& bottom, IFlashDisplayObject* targetCoordinateSystem) = 0;

	/**
	* ��������� ������������� another ������� ���, ����� �� �� �������� ��������� this
	*/
	virtual void applyTransform(IFlashDisplayObject* another) = 0;

	/**
	* ����������� ���������� �������� � ��������
	*/
	virtual void advance(FlashUpdateListener* updateListener, float dt) = 0;

	/**
	* �������������, �������� �� ������ ���������� ��� hitTest ���������
	*/
	virtual void setHitTestTransparent(bool value) = 0;
	virtual bool getHitTestTransparent() = 0;
	/**
	* �������������, �������� �� ������ ��������� �� ���� ��� hitTest.
	* �������� ����� ������������, ��������, ����� �� �������� ���������� �
	* ��������� �� ���������� ������ ���������� �����. ��� ���� ��� ������
	* ����� ���� ������������, � ����� ������ � ��������� ��������� ������� ���
	* ������������ �������
	*/
	virtual void setHitTestDispatcher(bool value) = 0;
	virtual bool getHitTestDispatcher() = 0;

	/**
	* ������������� ��������� �������
	*/
	virtual void setVisible(bool value) = 0;
	/**
	* ���������� ���� ��������� �������
	*/
	virtual bool getVisible() = 0;

	/**
	* ������������� ��� �������
	*/
	virtual void setName(const std::string& name) = 0;

	/**
	* ���������� ��� ������� (instance name � adobe flash)
	*/
	virtual const std::string& getName() = 0;

	/**
	* ������������� �������� alpha ��� �������
	*/
	virtual void setAlpha(float value) = 0;
	/**
	* ���������� �������� alpha ��� �����
	*/
	virtual float getAlpha() = 0;

	/**
	* ������������� ���� �������
	*/
	virtual void setColor(const Color& color) = 0;

	/**
	* ���������� ���� �������
	*/
	virtual const Color& getColor() = 0;

	/**
	* ������������� ������� ������������ ������������� ������� 
	*/
	virtual void setPosition(float x, float y) = 0;
	/**
	* �������� ������� ����� ��������(��� ����� ������ ��������� �� ������� ��� ���������, ��������� ���� ����� �������� � ��������� adobe Flash ��� �������� � Action Script) 
		������������ ������������� �������
	*/
	virtual void getPosition(float& x, float& y) = 0;
	/**
	* ������������� ���� �������� � ������������ ������� ������������� �������
	*/
	virtual void setRotation(float radians) = 0;
	/**
	* ���������� ������� � ������������ ������� ������������� �������
	*/
	virtual float getRotation() = 0;

	/**
	* ������������� ��������� � ������������ ������� ������������� �������
	*/
	virtual void setShear(float k) = 0;
	/**
	* ���������� ��������� � ������������ ������� ������������� �������
	*/
	virtual float getShear() = 0;

	/**
	* ������������� ������� � ������������ ������� ������������� �������
	*/
	virtual void setScale(float scaleX, float scaleY) = 0;
	/**
	* �������� ������� � ������������ ������� ������������� �������
	*/
	virtual void getScale(float& x, float& y) = 0;

	/**
	* ������������� ������� ������������� �������
	* ������ ���� ������������� 6 ��������:
	* a c tx
	* b d ty
	*/
	virtual void setMatrix(const float *matrix) = 0;
	/**
	* ���������� ������� ������������� �������
	* ����� �������� 6 ��������:
	* a c tx
	* b d ty
	*/
	virtual void getMatrix(float *matrix) = 0;

		/**
	* ���������� �������������� ����� � ��������� ������� ���������
	* � ������� ��������� ��������
	*/
	virtual void localToParent(float& x, float& y) = 0;
	/**
	* ���������� �������������� ����� � ������� ��������� �������� �
	* ��������� ������� ���������
	*/
	virtual void parentToLocal(float& x, float& y) = 0;
	/**
	* ��������� �������������� ����� � ��������� ������� ��������� � ����������
	*/
	virtual void localToGlobal(float &x, float &y) = 0;
	/**
	* ��������� �������������� ����� � ���������� ������� ��������� � ���������
	*/
	virtual void globalToLocal(float &x, float &y) = 0;
	/**
	* ��������� �������������� ��������� ��������� � ���������� �������� �������
	*/
	virtual void localToTarget(float &x, float& y, IFlashDisplayObject* target) = 0;

	/**
	* �������, ����������� ��������� �������. � �������� �� ������� �������������� ������ � hasUpdate
	*/
	virtual void update(float dt) = 0;
	/**
	* ������� �� ������� update. ������ ���������� ���������.
	*/
	virtual bool hasUpdate() = 0;

	/**
	* ������������� ������������ ������
	* 'Safe conditions': ���������� �� ������ ������� parent, ������� ��� 
	* �������� ������� ������ � ���� ������ ��������.
	*/
	virtual void unsafeSetParent(IFlashSprite* parent) = 0;

	/**
	* ��������� ������������� �������
	*/
	virtual IFlashSprite* getParent() = 0;
	/**
	* ����������� ���������� ��������� ������ ������
	* O(n + m), ��� n, m - ������ �������� this � another.
	*/
	virtual IFlashDisplayObject* getCommonAncestor(IFlashDisplayObject* another) = 0;
	/**
	* ��������� ��������� ������� - ������ �������� ������, �� �������� ��������
	*/
	virtual IFlashDisplayObject* getRoot() = 0;

	/**
	* ������������� �������� ���������� DisplayObject � ����� �� ����������
	*/
	virtual void setUpdateRate(float rate) = 0;
	virtual float getUpdateRate() = 0;

	/**
	* ������������� ���������������� �������� ���������
	*/
	virtual void setCustomDrawOperation(IFlashCustomDrawOperation*) = 0;
};

#if defined(__clang__) || defined(__GNUC__)
#pragma GCC diagnostic pop
#endif
