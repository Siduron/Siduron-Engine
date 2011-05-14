#include "Device.h"

Device::Device(HINSTANCE hInstance, LPDIRECTINPUT8 dinterface, HWND hWnd)
{
	this->instance = hInstance;
	this->dinterface = dinterface;
	this->hWnd = hWnd;
}