#ifndef _CORE_APPLICATION_MAC_H_
#define _CORE_APPLICATION_MAC_H_

#include "GUI/Cursor.h"

namespace Core
{

class EngineAppDelegate;
class Window;

void RunApplicationWithDelegate(int argc, const char * argv[], EngineAppDelegate *dlgt);

class Application
	: public ApplicationBase
	, public CursorManager
{
public:

	bool toggleFullscreenEnabled;

	Application();
	~Application();

	Window* GetMainWindow() { return wnd.get(); }

	void Init();
	void Start();

	void Stop();

	void CloseWindow();

	bool IsFullscreen() const;
	void ToggleFullscreen();

protected:

	std::unique_ptr<Window> wnd;

	virtual void RegisterTypes() override;
};

}

#endif // _CORE_APPLICATION_MAC_H_
