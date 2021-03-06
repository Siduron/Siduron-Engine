#ifndef RTSTEST_H
#define RTSTEST_H
#include "../Input/CEvent.h"
#include "../Core/Kernel.h"
#include "irrKlang.h"

using namespace irrklang;
class RTStest : public CEvent
{
	public: 
		RTStest();
		bool Run();

	private:
		void OnEvent(SDL_Event* Event);
		void OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle);
		void OnMouseWheel(bool Up, bool Down);
		void OnKeyDown(Uint8 scancode, SDLKey sym, SDLMod mod, Uint16 unicode);
		void OnKeyUp(Uint8 scancode, SDLKey sym, SDLMod mod, Uint16 unicode);
		void OnExit();
		bool scrollingLeft, scrollingRight, scrollingUp, scrollingDown;
		bool yawLeft, yawRight, forward, backward, strafeLeft, strafeRight;
		bool running;

		float timer;
		float keyTimer;
		Camera* camera;
		EntityModel* generator;
		EntityModel* dome;
		Terrain* terrain;
		ISoundEngine* engine;
		ISound* ambientsound;
		ISound* domesound;
		ISound* watersound;
};
#endif