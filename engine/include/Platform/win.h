#ifndef _PLATFORM_WIN_H_
#define _PLATFORM_WIN_H_

#include <string>

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX 1
#include <windows.h>

namespace utils
{

void MakeWindowForeground(HWND window);

void CenterWindow(HWND window);

float GetScreenDpiScale();

//Класс для проверки существования окна приложения.
//Мютекс создается в конструкторе и хранится до самого закрытия.
class SingleInstance {
public:
	SingleInstance(const std::string &name, const std::string &wndClass, const std::string &wndCaption);
	~SingleInstance();

	bool Check() const;

private:
	HANDLE _mutex;
	std::string _name;
	std::string _wndClass;
	std::string _wndCaption;
	bool _alreadyRunnging;
};

}
#endif
