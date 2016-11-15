#ifndef _INPUTSYSTEM_H_
#define _INPUTSYSTEM_H_

#include "MessageManager.h"
#include "Application.h"

namespace Core
{

class InputSystemImpl 
{
public:
	InputSystemImpl();
	
	// Зажата ли клавиша с кодом virtualKey.
	bool IsKeyDown(int virtualKey) const;
	// Включена ли клавиша с кодом virtualKey;
	// актуально для клавиш CapsLock, NumLock, ScrollLock.
	bool IsKeyToggledOn(int virtualKey) const;
	/// Зажат ли Shift
	bool IsShiftKeyDown() const;
	/// Зажат ли Ctrl
	bool IsControlKeyDown() const;

	void SetMousePos(int mouse_x, int mouse_y);
	void GetMousePos(int& mouse_x, int& mouse_y) const;
	IPoint GetMousePos() const;
	bool GetMouseLeftButton() const;
	bool GetMouseRightButton() const;
	bool GetKeyState(int key_code) const;
	
	// Преобразует координаты мыши в локальные координаты игры
	static IPoint TranslateMouseCoords(int mouse_x, int mouse_y);
	// Только обновляет координаны
	void SetMouseCoords(int mouse_x, int mouse_y);
	// Обновляет координаты и вызывает MouseMove
	void UpdateMouseCoords(int mouse_x, int mouse_y);
	void SetKeyState(int key_code, bool key_state);
	void KeyPressed(int key_code);
	void MouseLeftButtonDown();
	void MouseLeftButtonUp();
	void MouseRightButtonDown();
	void MouseRightButtonUp();
	void MouseCancel();
	/// Пришло событие "повёрнуто колёсико мыши"
	void MouseWheel(int delta);

	void PinchBegan(float scale, const IPoint &position );
	void PinchChanged(float scale, const IPoint &position );
	void PinchEnded();

private:
	friend class Window;

	int _mouse_x;
	int _mouse_y;

	bool _mouse_left_button;
	bool _mouse_right_button;
	bool _mouse_middle_button;

	bool _key_press[255];

	// сумма передвижений колёсика мыши
	// так-то оно должно быть кратно 120,
	// но если вдруг у кого не так -
	// то перемещения будут суммироваться
	// пока не окажутся больше 120 или меньше -120
	int _wheelSum;
};

extern InputSystemImpl mainInput;

}

#endif
