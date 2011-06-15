#include "Window.h"
#include "../Core/Kernel.h"

Window::Window()
{
	this->visible = true;
	this->focus = false;
}

bool Window::MakeWindow()
{
	Logger::Instance()->Log("Creating Window..", Info);
	LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
	static char sClassName[]  = "MyClass";
	static HINSTANCE zhInstance = NULL;
	WNDCLASSEX WndClass;
	        
    //zhInstance = hInstance;
    WndClass.cbSize        = sizeof(WNDCLASSEX);
    WndClass.style         = NULL;
    WndClass.lpfnWndProc   = WndProc;
    WndClass.cbClsExtra    = 0;
    WndClass.cbWndExtra    = 1;
    WndClass.hInstance     = zhInstance;
    WndClass.hIcon         = LoadIcon(GetModuleHandle (0), IDI_APPLICATION);
    WndClass.hCursor       = LoadCursor(NULL, IDC_ARROW);
    WndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    WndClass.lpszMenuName  = NULL;
    WndClass.lpszClassName = sClassName;
    WndClass.hIconSm       = LoadIcon(GetModuleHandle (0), IDI_APPLICATION);
		
    if(!RegisterClassEx(&WndClass)) 
	{
		Logger::Instance()->Log("Error Registering Class in Window", Error);
		MessageBox(0, "Error Registering Class!", "Error!", MB_ICONSTOP | MB_OK);
		return false;
    }
	
	this->hwnd = CreateWindowEx(
	WS_EX_STATICEDGE, sClassName, "Siduron Engine 1.0", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
	CW_USEDEFAULT,
	this->width, this->height, NULL, NULL, zhInstance, NULL);

    if(this->hwnd == NULL)
	{
		Logger::Instance()->Log("Error Creating Window", Error);
		MessageBox(0, "Error Creating Window!", "Error!", MB_ICONSTOP | MB_OK);
		return false;
    }

	ShowCursor(TRUE);
	this->SetVisible(true);
	UpdateWindow(this->hwnd);

	return true;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
              switch(Message) {
                case WM_CLOSE:
                        DestroyWindow(hwnd);
						break;
                case WM_DESTROY:
                        PostQuitMessage(0);
                        break;
				case WM_SETFOCUS :
						Kernel::Instance()->GetWindow()->SetFocus(true);
                        break;
				case WM_KILLFOCUS :
                        Kernel::Instance()->GetWindow()->SetFocus(false);
					    break;
                default:
                        return DefWindowProc(hwnd, Message, wParam, lParam);
			  }
       return 0;
}

HWND Window::GetHWND()
{
	return this->hwnd;
}

const int& Window::GetWidth() const
{
	return this->width;
}

const int& Window::GetHeight() const
{
	return this->height;
}

void Window::SetSize(int width, int height)
{
	this->width = width;
	this->height = height;
}

void Window::SetFocus(bool focus)
{
	this->focus = focus;
}

void Window::SetVisible(bool visible)
{
	this->visible = visible;
	ShowWindow(this->hwnd, visible);
}

bool Window::IsFocused()
{
	return this->focus;
}

void Window::Update()
{
	UpdateWindow(this->hwnd);
	MSG Msg;
	PeekMessage(&Msg,this->hwnd,NULL,NULL,PM_REMOVE);
	//SetCursorPos(800/2,600/2);
	TranslateMessage(&Msg);
	DispatchMessage(&Msg);
	
}

Window::~Window()
{

}