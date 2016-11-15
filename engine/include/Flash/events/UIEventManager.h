#pragma once

#include <boost/intrusive_ptr.hpp>

#include "FlashEvent.h"
#include "TouchEvents.h"

/**
* �����, ������������� ���������� � �������� � ������� 
*/
class UIEventManagerBase
{
	struct Touch
	{
		Touch(int _id):
			id(_id),
			initX(0),
			initY(0),
			x(0),
			y(0),
			captured(false),
			active(false),
			inStage(false),
			isMouse(false)
		{
		}

		int id;
		float initX, initY;
		float x, y;
		boost::intrusive_ptr<IFlashDisplayObject> relatedObject;
		bool captured;
		bool active;
		bool inStage;
		bool isMouse;
	};

public:
	UIEventManagerBase();
	UIEventManagerBase(IFlashDisplayObject* _root);
	virtual ~UIEventManagerBase();

	/**
	* ���������, �� �� ��� � ��� ������ ���� �����(��������� ����) � �������� ���������� ����,
		��� ������ ��� ��� ������� ���� ����� ����� ������������� 0
	*/
	void setMouseInputAtZero();

	int touchBegin(float x, float y);
	void touchMove(int touchId, float x, float y);
	void touchEnd(int touchId, float x, float y);
	void touchCancel(int touchId);

	void touchLeave(int touchId);
	void touchEnters(int touchId);

	void touchReset();

private:
	/**
		���������� ��������� �������(events), ����� � ������� ������ ������� ��������� �������� 
		��� ��������/�������(����� �� �� ������, �� ������� �� ������),

		����� ������� ��������� ��������� ���������� ������ leave, � ��������� enter, ����� ������� ������ ���� ���������� �� �� ��� ��������
	*/
	void __touchRelatedObjectChanged(int touchId, IFlashDisplayObject* prev, IFlashDisplayObject* next);
	Touch& __getFreeTouch(); //������� �������� Touch

protected:
	IFlashDisplayObject* root;
	/*
		��� ������� ���������� ��� ����� touch ������� ���������� ��� ��� � ������ ������� ��� ���

		�.� ���������� ���� �������� ����� ����� ����� �� �������(������� ������ �� ��������) ����� ������ ������� ��� ����� �������,
		� ���� ������� � ������ ����� ��������� ������� ������� �� ������ ������� ������, �������� ������ ��� ����� ��������� �������,
		� ��� �� ���������� ������ ������� � ������ ������ �����(��������� ����������� ������ ������������ ����� http://developer.android.com/design/patterns/gestures.html)

		��� ����� � ������ ����� �������� � ������� ���� �������
	*/
	int capturedTouches;
	std::vector<Touch> touches;

};

class UIEventManager: public UIEventManagerBase
{
public:
	UIEventManager();
	UIEventManager(IFlashDisplayObject* _root);
	virtual ~UIEventManager();

	/**
	* ������������� ������, ������� �������� ������ ��������. ������ ������ ��������
	* ������� �������, ���� ���� ��� �� ������ �� � ���� ������.
	*/
	void setRoot(IFlashDisplayObject* _root);
};
