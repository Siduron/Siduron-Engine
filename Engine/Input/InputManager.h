#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#define DIRECTINPUT_VERSION 0x0800
#include <windows.h>
#include <windowsx.h>
#include <dinput.h>
#include "../Util/Logger.h"
//#include "Device.h"
#include "Keyboard.h"

// include the DirectX Library files
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")

//enum Key
//{
//	NONE,
//	W,
//	S,
//	A,
//	D,
//	T,
//	F,
//	ESCAPE
//};


class InputManager
{
	public:
		InputManager();
		~InputManager();
		bool InitInput(	HINSTANCE hInstance, HWND hWnd	);
		std::queue<Input>* GetKeyboardInput();
		DIMOUSESTATE GetMouseInput();
		const float& GetMouseX() const;
		const float& GetMouseY() const;
		void Cleanup();

	private:
		// global declarations
		LPDIRECTINPUT8 dinterface;    // the pointer to our DirectInput interface
		LPDIRECTINPUTDEVICE8 dkeyboard;    // the pointer to the keyboard device
		LPDIRECTINPUTDEVICE8 dinmouse;    // the pointer to the mouse device
		HINSTANCE instance;
		HWND hwnd;
		BYTE keystate[256];
		DIMOUSESTATE mousestate; 

		Keyboard* keyboard;
};
#endif
