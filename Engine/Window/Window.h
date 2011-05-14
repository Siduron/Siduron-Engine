#ifndef WINDOW_H
#define WINDOW_H

#include <windows.h>
#include "../Util/Logger.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
enum Message
{
	QUIT,
	NOMSG
};

class Window
{
	public:
		Window();
		~Window();
		bool MakeWindow();
		//Message GetMessage();
		HWND GetHWND();
		const int& GetWidth() const;
		const int& GetHeight() const;
		void SetSize(int width, int height);
		void SetFocus(bool focus);
		void SetVisible(bool visible);
		bool IsFocused();
		void Update();
		
	private:
		HWND hwnd;
		int width;
		int height;
		bool visible;
		bool focus;
};

#endif