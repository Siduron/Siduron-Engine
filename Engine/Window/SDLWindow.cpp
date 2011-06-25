#include "SDLWindow.h"
#include <SDL_syswm.h>
#include "../Core/Kernel.h"

SDLWindow::SDLWindow(int width, int height)
{
	SDL_Init(SDL_INIT_VIDEO);
	if(FULLSCREEN)
		this->surface = SDL_SetVideoMode(width, height, 24, SDL_SWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
	if(!FULLSCREEN)
		this->surface = SDL_SetVideoMode(width, height, 24, SDL_SWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE | SDL_NOFRAME);
	
	SDL_SysWMinfo pInfo; 
	SDL_VERSION(&pInfo.version);
	SDL_GetWMInfo(&pInfo); 
	SDL_EnableUNICODE( 1 );
	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
	//MoveWindow(this->GetHandle(), SCREEN_WIDTH/2, SCREEN_HEIGHT/2, NULL, NULL, NULL);
}

HWND SDLWindow::GetHandle()
{
	SDL_SysWMinfo pInfo; 
	SDL_VERSION(&pInfo.version); 
	SDL_GetWMInfo(&pInfo); 
	return pInfo.window;
}

int SDLWindow::GetWidth()
{
	return this->width;
}

int SDLWindow::GetHeight()
{
	return this->height;
}

SDLWindow::~SDLWindow()
{

}