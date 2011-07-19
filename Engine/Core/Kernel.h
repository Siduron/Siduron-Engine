#ifndef KERNEL_H
#define KERNEL_H

#include "../Resources/ResourceManager.h"
#include "../Renderer/Renderer.h"
#include "../Window/SDLWindow.h"
#include "../Input/InputManager.h"
#include "../Scene/Scene.h"
#include "../GUI/GUI.H"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 1020
#define FULLSCREEN false

class Kernel
{
	public:
		Kernel();
		static Kernel* Instance();
		Renderer* GetRenderer();
		InputManager* GetInputManager();
		SDLWindow* GetWindow();
		Scene* GetScene();
		GUI* GetGUI();
		ResourceManager* GetResourceManager();
		~Kernel();

	private:
		Renderer* renderer;
		SDLWindow* window;
		InputManager* input;
		Scene* scene;
		ResourceManager* resourcemanager;
		GUI* gui;
		static Kernel* pInstance;
};
#endif