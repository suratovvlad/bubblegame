#pragma once

#include <Utils/Color.h>

#include "fquery.h"
#include "../core/FlashStage.h"
#include "../core/FlashMarkSweep.h"

namespace fquery {
namespace ui {

class UIElement: public IGCRef
{
public:
	UIElement()
	{
	}

	virtual ~UIElement()
	{
	}

	void setWrapedObject(IFlashDisplayObject* _displayObject)
	{
		displayObject = _displayObject;
	};

	IFlashDisplayObject* getWrapedObject()
	{
		return displayObject;
	};

protected:
	GC_BLACKEN_DECL()
	{
				//�� ����� �������� displayObject - ��� ������ ������
	}

protected:
	IFlashDisplayObject* displayObject; //weak ref
};

class Button: public UIElement
{
public:
	Button()
	{
	}

	virtual ~Button()
	{
	}

	void setWrapedObject(IFlashDisplayObject* _displayObject)
	{
		UIElement::setWrapedObject(_displayObject);
		fQuery(displayObject)
					.bind(TouchBegin, MEMBER_HANDLER(this, Button::onTouchBegin))
					.bind(TouchRollOver, MEMBER_HANDLER(this, Button::onTouchOver))
					.bind(TouchRollOut, MEMBER_HANDLER(this, Button::onTouchOut))
					.bind("disable", MEMBER_HANDLER(this, Button::onDisable))
					.bind("enable", MEMBER_HANDLER(this, Button::onEnable));

		isTouchOver = false;
		isTouching = false;
		isEnabled = true;

		active = fQuery("active", displayObject)[0];
		pressed = fQuery("pressed", displayObject)[0];
		IFlashDisplayObject* back = fQuery("hitTest", displayObject)[0];

		if(back)
		{
			back->setAlpha(0.f);
		}

		updateState();
	};

protected:
			const Color GRAY_COLOR = Color(0x88, 0x88, 0x88, 0x88);
			const Color WHITE_COLOR = Color::WHITE;

			void onTouchBegin(TouchEvent& event)
			{
				if (isEnabled)
				{
					isTouching = true;
					root = displayObject->getRoot();
					fQuery(root)
						.bind(TouchEnd, MEMBER_HANDLER(this, Button::onTouchEnd))
						.bind(TouchCancel, MEMBER_HANDLER(this, Button::onTouchCancel));
					updateState();
				}
			}

			void onTouchOver(TouchEvent& event)
			{
				if (isEnabled)
				{
					isTouchOver = true;
					updateState();
				}
			}

			void onTouchOut(TouchEvent& event)
			{
				if (isEnabled)
				{
					isTouchOver = false;
					updateState();
				}
			}

			void onTouchEnd(TouchEvent& event)
			{
				if ( isTouchOver ){
					FlashEvent event("click");
					EventManager::Get().dispatchTarget(displayObject, event);
				}
				isTouching = false;
				updateState();
				unbind();
			}

			void onTouchCancel(TouchEvent& event){
				isTouching = false;
				updateState();
				unbind();
			}

			void onDisable(FlashEvent& event)
			{
				isEnabled = false;
				updateState();
			}
			
			void onEnable(FlashEvent& event)
			{
				isEnabled = true;
				updateState();
			}

			void updateState()
			{
				if (isTouching && isTouchOver)
				{
					if (active) {
						active->setVisible(false);
					}

					if (pressed)
					{
						pressed->setVisible(true);
						if (isEnabled)
						{
							pressed->setColor(WHITE_COLOR);
						}
						else
						{
							pressed->setColor(GRAY_COLOR);
						}
					}
				}
				else
				{
					if (active)
					{
						active->setVisible(true);
						if (isEnabled)
						{
							active->setColor(WHITE_COLOR);
						}
						else
						{
							active->setColor(GRAY_COLOR);
						}

					}
					
					if (pressed) {
						pressed->setVisible(false);
					}				
				}
			}

			void unbind(){
				fQuery(root)
					.unbind(TouchEnd, MEMBER_HANDLER(this, Button::onTouchEnd))
					.unbind(TouchCancel, MEMBER_HANDLER(this, Button::onTouchCancel));
			}

			bool isEnabled;
			bool isTouchOver;
			bool isTouching;

	IFlashDisplayObject* root;
	IFlashDisplayObject* active;
	IFlashDisplayObject* pressed;
};

class Checkbox: public UIElement
{
public:
	Checkbox()
	{
	}

	virtual ~Checkbox()
	{
	}

	void setWrapedObject(IFlashDisplayObject* _displayObject)
	{
		UIElement::setWrapedObject(_displayObject);
		fQuery(displayObject)
			.bind(TouchBegin, MEMBER_HANDLER(this, Checkbox::onTouchBegin))
			.bind("check", MEMBER_HANDLER(this, Checkbox::onCheck))
			.bind("uncheck", MEMBER_HANDLER(this, Checkbox::onUncheck))
			.bind("queryBoolValue", MEMBER_HANDLER(this, Checkbox::onQueryValue));

		check = fQuery("check", displayObject)[0];
		state = false;

		IFlashDisplayObject* back = fQuery("hitTest", displayObject)[0];

		if(back)
		{
			back->setAlpha(0.f);
		}
		
		updateState();
	};

protected:
			void onTouchBegin(TouchEvent& /*event*/){
				state = !state;
				if ( state ){
					FlashEvent event("toggledOn");
					EventManager::Get().dispatchTarget(displayObject, event);
				}else{
					FlashEvent event("toggledOff");
					EventManager::Get().dispatchTarget(displayObject, event);
				}
				updateState();
			}

			void onQueryValue(QueryEvent<bool>& event){
				event.respond(state);
			}

			void onCheck(FlashEvent& event){
				state = true;
				updateState();
			}

			void onUncheck(FlashEvent& event){
				state = false;
				updateState();
			}

			void updateState(){
				if ( state ){
					if ( check ){
						check->setVisible(true);
					}
				}else{
					if ( check ){
						check->setVisible(false);
					}
				}
			};

protected:
	bool state;
	IFlashDisplayObject* root;
	IFlashDisplayObject* check;
};

class ToggleButton: public UIElement
{
public:
	ToggleButton()
	{
	}

	virtual ~ToggleButton()
	{
	}

	void setWrapedObject(IFlashDisplayObject* _displayObject)
	{
		UIElement::setWrapedObject(_displayObject);
		fQuery(displayObject)
			.bind(TouchBegin, MEMBER_HANDLER(this, ToggleButton::onTouchBegin))
			.bind("check", MEMBER_HANDLER(this, ToggleButton::onCheck))
			.bind("uncheck", MEMBER_HANDLER(this, ToggleButton::onUncheck))
			.bind("queryBoolValue", MEMBER_HANDLER(this, ToggleButton::onQueryValue));

		active = fQuery("active", displayObject)[0];
		pressed = fQuery("pressed", displayObject)[0];
		state = false;
		updateState();
	};

protected:
			void onTouchBegin(TouchEvent& event){
				state = !state;
				if ( state ){
					FlashEvent event("toggledOn");
					EventManager::Get().dispatchTarget(displayObject, event);
				}else{
					FlashEvent event("toggledOff");
					EventManager::Get().dispatchTarget(displayObject, event);
				}
				updateState();
			}

			void onQueryValue(QueryEvent<bool>& event){
				event.respond(state);
			}

			void onCheck(FlashEvent& event){
				state = true;
				updateState();
			}

			void onUncheck(FlashEvent& event){
				state = false;
				updateState();
			}

			void updateState(){
				if ( state ){
					if ( active ){
						active->setVisible(false);
					}
					if ( pressed ){
						pressed->setVisible(true);
					}
				}else{
					if ( active ){
						active->setVisible(true);
					}
					if ( pressed ){
						pressed->setVisible(false);
					}
				}
			}

protected:
	bool state;
	// IFlashDisplayObject* root; // not in use
	IFlashDisplayObject* active;
	IFlashDisplayObject* pressed;
};

/// �����, ����������� ��������� �������� ������� � �����
class Anchor : public UIElement
{
public:
	enum Type
	{
		None,
		Left = 1 << 0,
		Top = 1 << 1,
		Right = 1 << 2,
		Bottom = 1 << 3
	};

	Anchor()
	{
	}

	virtual ~Anchor()
	{
	}

	void setWrapedObject(IFlashDisplayObject* _displayObject)
	{
		UIElement::setWrapedObject(_displayObject);
		FlashStage* stage = dynamic_cast<FlashStage*>(displayObject->getRoot());

		if (!stage)
		{
			Halt("display object must be put into the stage");
			return;
		}

		stage->getOrigin(initStageX, initStageY);
		stage->getStageSize(initStageWidth, initStageHeight);

		displayObject->getBounds(left, top, right, bottom, NULL);

		fQuery(displayObject).bind(Resize, MEMBER_HANDLER(this, Anchor::onResize));
	};

	void setAnchor(unsigned int _anchor)
	{
		anchor = _anchor;
	};

	unsigned int getAnchor()
	{
		return anchor;
	};

protected:
	void onResize(ResizeEvent& event) {
		FlashStage* stage = dynamic_cast<FlashStage*>(displayObject->getRoot());
		if (!stage) {
			Halt("display object must be put into the stage");
			return;
		}

		// �������� � ����� ����� ����� ������ � ������ ��� ���������������
		if (stage->getScaleMode() != FlashStage::ScaleMode::NoScale) {
			return;
		}

		float origX, origY;
		stage->getOrigin(origX, origY);

		float stageWidth, stageHeight;
		stage->getStageSize(stageWidth, stageHeight);

		float dx0 = initStageX - origX;
		float dx1 = initStageX - origX + initStageWidth - stageWidth;
		float dy0 = initStageY - origY;
		float dy1 = initStageY - origY + initStageHeight - stageHeight;

		float newLeft = left, newTop = top, newRight = right, newBottom = bottom;

		if (anchor & Left || anchor & Right) {
			if (anchor & Left && anchor & Right) {
				newLeft -= dx0;
				newRight -= dx1;
			} else if (anchor & Left) {
				newLeft -= dx0;
				newRight -= dx0;
			} else if (anchor & Right) {
				newLeft -= dx1;
				newRight -= dx1;
			}
		}

		if (anchor & Top || anchor & Bottom) {
			if (anchor & Top && anchor & Bottom) {
				newTop -= dy0;
				newBottom -= dy1;
			} else if (anchor & Top) {
				newTop -= dy0;
				newBottom -= dy0;
			} else if (anchor & Bottom) {
				newTop -= dy1;
				newBottom -= dy1;
			}
		}

		displayObject->setPosition(left, top);
		displayObject->setScale((newRight - newLeft) / (right - left), (newBottom - newTop) / (bottom - top));
	}

protected:
	unsigned int anchor;
	float initStageX, initStageY, initStageWidth, initStageHeight;
	float left, top, right, bottom;
};

void makeButton(IFlashDisplayObject* displayObject);
void makeCheckbox(IFlashDisplayObject* displayObject);
void makeToggleButton(IFlashDisplayObject* displayObject);
void makeAnchor(IFlashDisplayObject* displayObject, unsigned int anchor);

FQuerySelector& button(FQuerySelector& selector);
FQuerySelector& checkbox(FQuerySelector& selector);
FQuerySelector& toggleButton(FQuerySelector& selector);
FQuerySelector& anchor(FQuerySelector& selector, unsigned int anchor);

} // namespace ui
} // namespace fquery

#include "fquery_ui_press.h"
#include "fquery_ui_radio.h"
#include "fquery_ui_scroller.h"
