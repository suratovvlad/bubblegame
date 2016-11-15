#pragma once

#include "Flash/core/FlashCommon.h"

struct IFlashDisplayObject;
class EventManager;

/**
* ���� ��������������� �������.
* ���� ������� - ����� ������� �� ����� �������� �� �������� ����.
* ���� ���� - ��������� ������� � ������� ����.
* ���� ������� - ������ ������� �� �������� ���� �� ����� ��������.
*/
enum class EventPhaseType {
	Capture,
	Target,
	Bubbles
};

/**
* ������� ����� ��� �������.
* ��� ����������� ������� ����� ������������� �� ����� ������.
*/
class FlashEvent {
public:
	/**
	* @param bubbles ����������, ������ �� ��� ������� ����������� ���� �������
	*/
	FlashEvent(const std::string& type, bool bubbles = true);
	virtual ~FlashEvent() { }

	const std::string& getType() const;
	/**
	* �������� ������� ���� ��������������� �������
	*/
	EventPhaseType getPhase() const;
	
	/**
	* ������������� ��������������� �������.
	* �������� ���������� ��������������� ������� �� ������� ����, � ������� �� �������������� � ������ ������.
	*/
	void stopPropagation();
	/**
	* ������������� ��������������� �������, ������� ���������� ����������� � ������� ����.
	*/
	void stopImmediatePropagation();

	/**
	* ���������� ������� ���� �������.
	*/
	IFlashDisplayObject* getTarget();
	/**
	* ���������� ��� �������� ���� ������� ���� ����������.
	*/
	const std::string getTargetName();
	/**
	* ���������� ������� ����, � ������� ������� ��������� �������.
	*/
	IFlashDisplayObject* getCurrentTarget();

	/**
	* ���������� ��� ����� �������� ���� �������
	*/
	virtual void visitNode(IFlashDisplayObject* node){}

	/**
	* �������� ��������� �� ��������� ��� �������.
	* ��� ������ ������� ��������� �� ��������� ����� ����� ������ �����
	*/
	void preventDefault();
	/**
	* ����������, ��� �� ������ ����� preventDefault �����
	*/
	bool isDefaultPrevented();
private:
	FlashEvent(const FlashEvent& event);

	const FlashEvent& operator=(const FlashEvent& event);

	std::string type;
	EventPhaseType phase;

	IFlashDisplayObject* target;
	IFlashDisplayObject* currentTarget;

	bool bubbles, propagationStopped, propagationStoppedImmediatly;
	bool defaultPrevented;

	friend class EventManager;
};