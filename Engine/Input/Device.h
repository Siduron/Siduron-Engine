#ifndef DEVICE_H
#define DEVICE_H

#include <dinput.h>

class Device
{
	public:
		Device(HINSTANCE hInstance, LPDIRECTINPUT8 dinterface, HWND hWnd);
		virtual void Init();
	private:
		HINSTANCE instance;
		LPDIRECTINPUT8 dinterface;
		HWND hWnd;
	protected:
		LPDIRECTINPUTDEVICE8 device;
};

#endif