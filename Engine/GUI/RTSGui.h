#ifndef RTSGUI_H
#define RTSGUI_H
#include "CEGui.h"

class RTSGui
{
	public:
		RTSGui(CEGUI::Window* newRoot);	
		bool EnableBuildBasic(const CEGUI::EventArgs& e);
		bool DisableBuildBasic(const CEGUI::EventArgs& e);
		bool BuildBasicKeyPress(const CEGUI::EventArgs& e);
		~RTSGui();
	private:
		CEGUI::Window* root;
		CEGUI::Window* mainGui;
		CEGUI::Window* buildScreen;
		CEGUI::Window* buildButton;
		CEGUI::Window* buildScreen_Basic;
		
		void SetRoot(CEGUI::Window* newRoot);
		double One( long inVal );
		void RegisterEvents();
};
#endif