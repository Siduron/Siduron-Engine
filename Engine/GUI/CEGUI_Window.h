#ifndef CEGUI_WINDOW_H
#define CEGUI_WINDOW_H
#include "CEGui.h"

class CEGUI_Window
{
	public:
		CEGUI_Window();
		~CEGUI_Window();
	private:
		CEGUI::Window* window;
};
#endif