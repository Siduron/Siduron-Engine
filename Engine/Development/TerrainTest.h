#ifndef TERRAINTEST_H
#define TERRAINTEST_H
#include "../Input/CEvent.h"
#include "../Core/Kernel.h"

class TerrainTest : public CEvent
{
	public: 
		TerrainTest();
		bool Run();
	private:
		void OnEvent(SDL_Event* Event);
		void OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle);
		void OnMouseWheel(bool Up, bool Down);
		void OnLButtonDown(int mX, int mY);
		void OnLButtonUp(int mX, int mY);
		void OnKeyDown(Uint8 scancode, SDLKey sym, SDLMod mod, Uint16 unicode);
		void OnKeyUp(Uint8 scancode, SDLKey sym, SDLMod mod, Uint16 unicode);
		void OnExit();
		bool running;
		bool mLDown;

		float timer;
		float keyTimer;
		Camera* camera;
		Terrain* terrain;

};
#endif