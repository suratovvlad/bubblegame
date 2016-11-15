#pragma once

#include "Flash/events/FlashEvent.h"

#include <boost/function.hpp>
#include <boost/bind.hpp>

struct IFlashDisplayObject;

struct EventHandler{
	boost::function<void(FlashEvent&)> callee;
	size_t hash;

	EventHandler(){
	}

	EventHandler(boost::function<void(FlashEvent&)> callee, size_t hash):callee(callee),hash(hash){
	}
};

template<class E>
struct CallHandlerWithRTCheck{
	CallHandlerWithRTCheck(const boost::function<void(E&)>& f):f(f){
	}
	
	void operator()(FlashEvent& e){
		f(dynamic_cast<E&>(e));
	}

	boost::function<void(E&)> f;
};

template<>
struct CallHandlerWithRTCheck<FlashEvent>{
	CallHandlerWithRTCheck(const boost::function<void(FlashEvent&)>& f):f(f){
	}

	void operator()(FlashEvent& e){
		f(e);
	}

	boost::function<void(FlashEvent&)> f;
};

template<class C, class E>
EventHandler makeMemberHandler(C* c, void(C::*f)(E&)){
	size_t hash = *((size_t*)c + (sizeof(c)-sizeof(size_t))/sizeof(size_t));
	unsigned char* p = (unsigned char*)*((unsigned char**)&f);
	for ( int i = 0; i < sizeof( void(C::*)(E&) ); i++ ){
		//����� �� �������� � ������ �� ���� � ������ �������
		hash = ((hash << (sizeof(size_t) * 8 / 2 + 1) ) | (hash >> (sizeof(size_t) * 8 / 2 - 1))) ^ p[i] + (p[i] << 11);
	}
	return EventHandler(CallHandlerWithRTCheck<E>(boost::function<void(E&)>(boost::bind( f, c, _1 ))), hash);
}

#define MEMBER_HANDLER(c, f) makeMemberHandler(c, &f)

typedef unsigned int HandlerID;

struct EHStorage;

/**
* ������ ��� ����������� ���������� ������� � �������� �������
*/
class EventManager{
public:
	/**
	* ���������� ������� ����.
	* ������� �������� ���� ������� (���������� �� ����� �� ����), 
	* ����� ���� ����, �, ����
	* ���������, ���� ������� (����������� �� ���� �� �����)
	*/
	void dispatch(IFlashDisplayObject* target, FlashEvent& event);
	/**
	* ���������� ������� �������� ����, ��������� ���� ������� � �������
	*/
	void dispatchTarget(IFlashDisplayObject* target, FlashEvent& event);
	/**
	* ���������� ������� ���� root. ��� ���� �������� captureAndBubbles ���������, ����� ��
	* �������������� ���� ������� � �������. ����� ����, ��� ���� �������� �������, ����
	* ������� �� ���� �������� ��� ������ preventDefault, ������� ������������ ���� �������� 
	* ��������� ����.
	*/
	void broadcast(IFlashDisplayObject* root, FlashEvent& event, bool captureAndBubbles = false);

	/**
	* ������������� ���������� ������� handler ��� ���� type �� ���� target.
	* �������� isCapture ����������, ������������ �� ���������� � ���� ������� (true) ���� � ����
	* ���� � ������� (false).
	* ������������ HandlerID ����� ������������ ��� �������� �����������.
	* ���� ���������� handler ��� ���������� ��� ������� �������, �� �� �� ����� �������� ��������.
	*/
	HandlerID addEventListener(IFlashDisplayObject* target, const std::string& type, const EventHandler& handler, bool isCapture = false);
	
	/**
	* ������� ���������� ������� �� HandlerID
	*/
	void removeEventListener(HandlerID id);
	/**
	* ������� ���������� �������, ������������� ������� addEventListener(target, type, handler)
	*/
	void removeEventListener(IFlashDisplayObject* target, const std::string& type, EventHandler handler);
	/**
	* ������� ��� ����������� ������� �� ����
	*/
	void removeEventListeners(IFlashDisplayObject* target);
	/**
	* ����������, ���� �� ��� ���� ���������� ������� �������.
	* ���������� ����������� ��� ���� �������.
	*/
	bool willTriggerAt(IFlashDisplayObject* target, FlashEvent& event);

	/**
	* ���������� ���������� ��������� EventManager
	*/
	static EventManager& Get();
private:

	struct EventHandlerRecord
	{
		EventHandlerRecord(const bool _isCapture, const EventHandler& _handler, const HandlerID _id):
			isCapture(_isCapture),
			handler(_handler),
			id(_id)
		{
		};

		bool isCapture;
		EventHandler handler;
		HandlerID id;
	};

	typedef std::multimap<std::string, EventHandlerRecord> TargetListeners;
	std::map<IFlashDisplayObject*, TargetListeners> allListeners;
	std::map<HandlerID, IFlashDisplayObject*> handlersIndex;

	void collectHandlers(EHStorage* storage, IFlashDisplayObject* target, FlashEvent& event);
	void doDispatch(EHStorage* storage, FlashEvent& event);

	HandlerID nextId;
};
