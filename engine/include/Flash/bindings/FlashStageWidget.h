#pragma once

#include <GUI/Widget.h>
#include "../core/FlashStage.h"
#include "../core/FlashUpdateListener.hpp"

class FlashStageWidget: public GUI::Widget
{
public:
	static const std::string INITIALIZE;
	static const std::string DEINITIALIZE;

	FlashStageWidget(const std::string& name, rapidxml::xml_node<>* elem);
	virtual ~FlashStageWidget();

	//----------------------------------------------------------------------------
	//
	//                             GUI::Widget
	//
	//----------------------------------------------------------------------------
	virtual bool MouseDown(const IPoint& mouse_pos);
	virtual void MouseUp(const IPoint& mouse_pos);
	virtual void MouseMove(const IPoint& mouse_pos);
	virtual void MouseWheel(int delta);
	virtual void MouseCancel(void);
	virtual void Draw();
	virtual void Update(float);
	virtual void AcceptMessage(const Message& message);

	inline FlashStage* getFlashStage(){return __m_stage;};

private:
	FlashStage* __m_stage;

protected:
	void initialize();
	void deinitialize();

	FlashUpdateListener listener;
	bool initialized;

	float mouseX, mouseY;
	bool mouseInput, mouseDown;
	bool interceptAllTouches;
};
