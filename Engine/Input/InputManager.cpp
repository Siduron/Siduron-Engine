#include "InputManager.h"

InputManager::InputManager()
{

}

bool InputManager::InitInput( HINSTANCE hInstance, HWND hWnd )
{
	this->hwnd = hWnd;
	Logger::Instance()->Log("Creating Input Interface..", Info);
	// create the DirectInput interface
	HRESULT hr = DirectInput8Create(hInstance,    // the handle to the application
						   DIRECTINPUT_VERSION,    // the compatible version
						   IID_IDirectInput8,    // the DirectInput interface version
						   (void**)&this->dinterface,    // the pointer to the interface
						   NULL);    // COM stuff, so we'll set it to NULL

	Logger::Instance()->Log("Creating Keyboard Device..", Info);
	this->keyboard = new Keyboard(hInstance, this->dinterface, hWnd );
	this->keyboard->Init();

	Logger::Instance()->Log("Creating Mouse Device..", Info);
	// create the mouse device
	this->dinterface->CreateDevice(GUID_SysMouse,    // the default mouse ID being used
						  &this->dinmouse,    // the pointer to the device interface
						  NULL);    // COM stuff, so we'll set it to NULL


	this->dinmouse->SetDataFormat(&c_dfDIMouse);    // set the data format to mouse format

	this->dinmouse->SetCooperativeLevel(this->hwnd,
										DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);


	return true;
}

std::queue<Input>* InputManager::GetKeyboardInput()
{
	return this->keyboard->GetKeyboardInput();
}

DIMOUSESTATE InputManager::GetMouseInput()
{
	this->dinmouse->Acquire();    // Acquire the mouse only once
	this->dinmouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&this->mousestate);
	return this->mousestate;
}

const float& InputManager::GetMouseX() const
{
	//this->dinmouse->Acquire();    // Acquire the mouse only once
	this->dinmouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&this->mousestate);
	float t = this->mousestate.lX;
	return t;
}

const float& InputManager::GetMouseY() const
{
	//this->dinmouse->Acquire();    // Acquire the mouse only once
	this->dinmouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&this->mousestate);
	float t = this->mousestate.lY;
	return t;
}

// this is the function that closes DirectInput
void InputManager::Cleanup()
{
	//this->dinmouse->Unacquire();    // make sure the mouse is unacquired
 //   this->dinterface->Release();
	//this->dinmouse->Release();
    return;
}

InputManager::~InputManager()
{
	this->Cleanup();
}