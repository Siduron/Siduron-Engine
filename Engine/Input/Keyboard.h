#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "Device.h"
#include <queue>
#include <iostream>

enum Key
{
	NONE,
	W,
	S,
	A,
	D,
	T,
	F,
	Z,
	C,
	SPACE,
	ESCAPE
};

struct Input
{
	Key key;
};

class Keyboard : public Device
{
	public:
	Keyboard(HINSTANCE hInstance, LPDIRECTINPUT8 dinterface, HWND hWnd);
	std::queue<Input>* GetKeyboardInput();

	private:
		std::queue<Input>* queue;
	
};

#endif