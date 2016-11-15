#pragma once

#include "IFlashDisplayObject.h"

#if defined(__clang__) || defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnon-virtual-dtor"
#endif

//TODO ������������� � IFlashDisplayObjectContainer
struct IFlashSprite : public IFlashDisplayObject
{
	/**
	* �������� ����� �������� � ��������, �������� �������� ������� update.
	*/
	virtual void changeUpdateListeners(int value) = 0;

	virtual IFlashDisplayObject* getChildByName(const std::string& name) = 0;
	virtual IFlashDisplayObject* addChild(IFlashDisplayObject* displayObject) = 0;
	virtual IFlashDisplayObject* removeChild(IFlashDisplayObject* displayObject) = 0;
	virtual IFlashDisplayObject* addChildAt(IFlashDisplayObject* displayObject, int index) = 0;
	virtual IFlashDisplayObject* removeChildAt(int index) = 0;
	virtual IFlashDisplayObject* getChildAt(int index) = 0;
	virtual int getChildrenCount() = 0;
	virtual int getChildIndex(IFlashDisplayObject* displayObject) = 0;
	virtual void swapChildren(int _index1, int _index2) = 0;

		/**
	* ����������� ����� �������� � �������.
	* @param preorder ����������, ����� �� ������� ������� �������� �� (true) ���� ����� (false) ��������
	*/
	virtual void visitDFS(IFlashVisitor* visitor, bool preorder) = 0;
	/**
	* ����������� ����� �������� � ������.
	* @param preorder ����������, ����� �� ������� ������� �������� �� (true) ���� ����� (false) ��������
	*/
	virtual void visitBFS(IFlashVisitor* visitor, bool preorder) = 0;
};

#if defined(__clang__) || defined(__GNUC__)
#pragma GCC diagnostic pop
#endif
