#include "Keyboard.h"

Keyboard::Keyboard(HINSTANCE hInstance, LPDIRECTINPUT8 dinterface, HWND hWnd) : Device(hInstance, dinterface, hWnd)
{
	this->queue = new std::queue<Input>();
}
void Device::Init()
{
	
	// create the keyboard device
	this->dinterface->CreateDevice(GUID_SysKeyboard,    // the default keyboard ID being used
                      &this->device,    // the pointer to the device interface
                      NULL);    // COM stuff, so we'll set it to NULL

	this->device->SetDataFormat(&c_dfDIKeyboard); // set the data format to keyboard format

	this->device->SetCooperativeLevel(this->hWnd,
                                     DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
}

std::queue<Input>* Keyboard::GetKeyboardInput()
{
	BYTE keystate[256];

	// create a static storage for the key-states
    this->device->Acquire();    // get access if we don't have it already
    this->device->GetDeviceState(256, (LPVOID)keystate);    // fill keystate with values
	
	if(keystate[DIK_ESCAPE] & 0x80)
	{
		Input newInput;
		newInput.key = ESCAPE;
		this->queue->push(newInput);
	}
	if(keystate[DIK_W] & 0x80)
	{
		Input newInput;
		newInput.key = W;
		this->queue->push(newInput);
	}
	if(keystate[DIK_S] & 0x80)
	{
		Input newInput;
		newInput.key = S;
		this->queue->push(newInput);
	}
	if(keystate[DIK_A] & 0x80)
	{
		Input newInput;
		newInput.key = A;
		this->queue->push(newInput);
	}
	if(keystate[DIK_D] & 0x80)
	{
		Input newInput;
		newInput.key = D;
		this->queue->push(newInput);
	}
	if(keystate[DIK_T] & 0x80)
	{
		Input newInput;
		newInput.key = T;
		this->queue->push(newInput);
	}
	if(keystate[DIK_F] & 0x80)
	{
		Input newInput;
		newInput.key = F;
		this->queue->push(newInput);
	}
	if(keystate[DIK_R] & 0x80)
	{
		Input newInput;
		newInput.key = R;
		this->queue->push(newInput);
	}
	if(keystate[DIK_SPACE] & 0x80)
	{
		Input newInput;
		newInput.key = SPACE;
		this->queue->push(newInput);
	}
	if(keystate[DIK_Z] & 0x80)
	{
		Input newInput;
		newInput.key = Z;
		this->queue->push(newInput);
	}
	if(keystate[DIK_C] & 0x80)
	{
		Input newInput;
		newInput.key = C;
		this->queue->push(newInput);
	}
	return this->queue;
}