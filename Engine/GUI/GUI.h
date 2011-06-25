#ifndef GUI_H
#define GUI_H

#include "../Renderer/Renderer.h"
#include "../Input/CEvent.h"
//#include "RendererModules\Direct3D9\CEGUIDirect3D9Renderer.h"
//#include "CEGUIBase.h"
//#include "CEGUI.h"
//#include "CEGUISystem.h"
//#include "CEGUIDefaultResourceProvider.h"
//#include "CEGUIImageset.h"
//#include "CEGUIFont.h"
//#include "CEGUIScheme.h"
//#include "CEGUIWindowManager.h"
//#include "CEGUISchemeManager.h"
//#include "CEGUIFontManager.h"
//#include "falagard/CEGUIFalWidgetLookManager.h"
//#include "CEGUIScriptModule.h"
//#include "CEGUIXMLParser.h"
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "../Resources/Texture.h"

class GUI : public CEvent
{
	public:
		GUI(Renderer* r);
		~GUI();
		void Init();
		void Render();

	private:
		Renderer* renderer;
		void OnEvent(SDL_Event* Event);
		void OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle);
		void OnLButtonDown(int mX, int mY);
        void OnLButtonUp(int mX, int mY);
		void OnKeyDown(Uint8 scancode, SDLKey sym, SDLMod mod, Uint16 unicode);
		int lastUpdate;
};

#endif