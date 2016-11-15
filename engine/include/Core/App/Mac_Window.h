#ifndef _CORE_WINDOW_MAC_H_
#define _CORE_WINDOW_MAC_H_

#include "Render/RenderTypes.h"

namespace Core
{

class Window
{
public:

	Window();
	~Window();
	void Destroy();

	void SetMode(DeviceMode mode);
	DeviceMode GetWindowMode();

	IRect GetClientSizes();
	bool IsCursorIn();

	void Minimize();
	void RestoreMinimized();

	void Redraw();

private:

	DeviceMode _mode;

	int _clientWidth;
	int _clientHeight;

	void _SetMode(DeviceMode mode);

};

}

#endif // _CORE_WINDOW_MAC_H_
