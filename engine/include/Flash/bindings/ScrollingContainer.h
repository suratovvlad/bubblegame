#pragma once

#include "Scroller.h"
#include "../events/TouchEvents.h"
#include "../events/EventManager.h"
#include "../core/FlashDisplayObject.hpp"
#include "../core/IFlashSprite.h"
#include "../core/FlashUnknown.hpp"
#include "IScrollingContainer.h"

class ScrollingContainer:
	public FlashDisplayObject<IScrollingContainer>
{
BEGIN_INTERFACE_MAP()
	INTERFACE_ENTRY(IScrollingContainer)
	INTERFACE_ENTRY(IFlashSprite)
	INTERFACE_ENTRY(IFlashDisplayObject)
END_INTERFACE_MAP()

public:
	ScrollingContainer();
	virtual ~ScrollingContainer();

	enum class SpatialIndexType {
		QTree,
		Horizontal,
		Vertical,
		None
	};
    
#if defined(ENGINE_TARGET_MACOS)
    void resetScrollbar(IFlashDisplayObject* scrollbar = 0);
#endif

	/**
	* ”станавливает тип пространственного индекса дл€ контейнера.
	* ≈сли контейнер будет горизонтальным или вертикальным списком, надо выбирать тип индекса 
	* IndexHorizontal и IndexVertical соответственно
	* ≈сли контейнер будет двухмерным, надо выбирать тип IndexQTree
	* ≈сли число объектов в контейнере будет небольшим (<100), либо больша€ их часть (>25%)
	* всегда будет видна, можно выбирать тип IndexNone
	*/
	void setIndexType(SpatialIndexType indexType);

	void setScroll(bool horizontal, bool vertical);

	//----------------------------------------------------------------------------
	//
	//                          IScrollingContainer
	//
	//----------------------------------------------------------------------------
	void contentChanged();
	void setContentRect(float left, float top, float right, float bottom);
	void getContentRect(float& left, float& top, float& right, float& bottom);
	void setOverscroll(float left, float top, float right, float bottom);
	void getOverscroll(float& left, float& top, float& right, float& bottom);
	void setAutoContentRect(bool autoSize);
	bool getAutoContentRect();
	void setHorizontalKineticScroll(bool flag);
	KineticScroller* getHorizontalScroller();
	void setVerticalKineticScroll(bool flag);
	KineticScroller* getVerticalScroller();
	void setClipRect(float left, float top, float right, float bottom);
	void getClipRect(float& left, float& top, float& right, float& bottom);
	void setHorizontalScroll(float scroll);
	float getHorizontalScroll();
	void setVerticalScroll(float scroll);
	float getVerticalScroll();
	float getMaxVelocity();
	void setMaxVelocity(float velocity);
	void setContentAlign(float hAlign, float vAlign);
	void resetScrollPosition();
	void setScrollerBounceNP(int value);

	void AddMagnitPointVertical(float value);
	void AddMagnitPointHorizontal(float value);
	void SetPositionVertical(float value, float speed);
	void SetPositionHorizontal(float value, float speed);
	void StartConstantVerticalMotion(); 
	void StartConstantVerticalMotion(float MaxSpeed, float Acceleration);
	void StopConstantVerticalMotion();
	void StartConstantHorizontalMotion(); 
	void StartConstantHorizontalMotion(float MaxSpeed, float Acceleration);
	void StopConstantHorizontalMotion();
	bool IsScrollingHorizontally() const;
	bool IsScrollingVertically() const;

	void StopKineticScroll();

	//---------------------------------------------------------------------------
	//
	//                    IFlashDisplayObject
	//
	//---------------------------------------------------------------------------
	void unsafeSetParent(IFlashSprite* _parent);
	void render(FlashRender& render);
	bool hitTest(float x, float y, IHitTestDelegate* delegate);
	bool getBounds(float& left, float& top, float& right, float& bottom, IFlashDisplayObject* targetCoordinateSystem);
	
	void advance(FlashUpdateListener* updateListener, float dt);
	void update(float dt);
	bool hasUpdate() { return true; }

	void setPosition(float x, float y);
	void getPosition(float& x, float& y);

	void setMatrix(const float matrix[6]);

	//---------------------------------------------------------------------------
	//
	//                       IFlashSprite
	//
	//---------------------------------------------------------------------------
	void changeUpdateListeners(int _value);
	IFlashDisplayObject* getChildByName(const std::string& string);
	IFlashDisplayObject* addChild(IFlashDisplayObject* displayObject);
	IFlashDisplayObject* removeChild(IFlashDisplayObject* displayObject);
	IFlashDisplayObject* addChildAt(IFlashDisplayObject* displayObject, int index);
	IFlashDisplayObject* removeChildAt(int index);
	IFlashDisplayObject* getChildAt(int index);
	int getChildrenCount();
	int getChildIndex(IFlashDisplayObject* displayObject);
	void swapChildren(int _index1, int _index2);
	void visitDFS(IFlashVisitor* visitor, bool preorder);
	void visitBFS(IFlashVisitor* visitor, bool preorder);

protected:	
	GC_BLACKEN_DECL()
	{
		GC_BLACKEN_CALL(FlashDisplayObject);

		for ( auto it : children )
		{
			GC_SHOULD_MARK(it->object);
		};
	};

private:
	struct ChildContainer
	{
		float left, top, right, bottom;
		IFlashDisplayObject* object;
	};

	class SpatialIndex
	{
	public:
		SpatialIndex(ScrollingContainer* parent);
		void setIndexType(SpatialIndexType indexType);
		void update(float left, float top, float right, float bottom, std::vector<ChildContainer*>& content);
		void query(float left, float top, float right, float bottom, std::vector<ChildContainer*>& output);
	
		ScrollingContainer* parent;
		SpatialIndexType indexType;
	};

private:
	void validateVisibleChildren();
	void validateIndex();
	void updateContentSizeFromContent();
	void updateScrollParams();

	void onTouchBegin(TouchEvent& event);
	void onTouchMove(TouchEvent& event);
	void onTouchEnd(TouchEvent& event);
	void onTouchCancel(TouchEvent& event);

	void startScroll();
	void stopScroll();
	void removeListeners();

	void fireScrollEvent();

private:
	friend class SpatialIndex;

private:
	int numUpdateListeners;
	SpatialIndex spatialIndex;
	std::vector<ChildContainer*> children;
	std::vector<ChildContainer*> visibleChildren;
    
#if defined(ENGINE_TARGET_MACOS)
    IFlashDisplayObject* scrollbar_;
#endif

	float left, top, right, bottom;

	float contentLeft, contentTop, contentRight, contentBottom;
	float overscrollLeft, overscrollTop, overscrollRight, overscrollBottom;
	bool autoSize, validContentSize;
	float hAlign, vAlign;

	bool horizontalKineticScroll, verticalKineticScroll;
	KineticScroller horizontalScroller, verticalScroller;

	bool visibleChildrenValid;
	bool indexValid;

	bool horizontal;
	bool vertical;
	
	float xScroll, yScroll;

	bool selfCancelDispatch;
	bool scrollStarted;

	float grabX, grabY, lastX, lastY;
	float scrollGrabX, scrollGrabY;
	IFlashDisplayObject* root;
	HandlerID handlers[3];
};
