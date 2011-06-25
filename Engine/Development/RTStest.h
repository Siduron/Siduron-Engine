#ifndef RTSTEST_H
#define RTSTEST_H
#include "../Input/CEvent.h"

class RTStest : public CEvent
{
	public: 
		RTStest();
		bool Run();
	private:
		void OnEvent(SDL_Event* Event);
		void OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle);
		void OnMouseWheel(bool Up, bool Down);
		void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
		void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);
		void OnExit();
		bool scrollingLeft, scrollingRight, scrollingUp, scrollingDown;
		bool running;
};
#endif