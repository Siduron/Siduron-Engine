#ifndef MODELTEST_H
#define MODELTEST_H
#include "../Input/CEvent.h"

class ModelTest : public CEvent
{
	public: 
		ModelTest();
		bool Run();
		void OnEvent(SDL_Event* Event);
		void OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle);
		void OnMouseWheel(bool Up, bool Down);
		void OnLButtonDown(int mX, int mY);
		void OnLButtonUp(int mX, int mY);
		void OnKeyDown(Uint8 scancode, SDLKey sym, SDLMod mod, Uint16 unicode);
		void OnKeyUp(Uint8 scancode, SDLKey sym, SDLMod mod, Uint16 unicode);
		void OnExit();
		bool running;
};
#endif