#ifndef SDLWINDOW_H
#define SDLWINDOW_H
#include "SDL.h"
#include <windows.h>

class SDLWindow
{
	public:
	SDLWindow(int width, int height);
	HWND GetHandle();
	int GetWidth();
	int GetHeight();
	~SDLWindow();

	private:
	SDL_Surface* surface;
	int width, height;
};
#endif