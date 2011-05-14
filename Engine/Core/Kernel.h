#ifndef KERNEL_H
#define KERNEL_H

#include "../Resources/ResourceManager.h"
#include "../Renderer/Renderer.h"
#include "../Window/Window.h"
#include "../Input/InputManager.h"
#include "../Scene/Scene.h"
#include "../GUI/GUI.H"

class Kernel
{
	public:
		Kernel();
		static Kernel* Instance();
		Renderer* GetRenderer();
		InputManager* GetInputManager();
		Window* GetWindow();
		Scene* GetScene();
		GUI* GetGUI();
		ResourceManager* GetResourceManager();
	private:
		~Kernel();
		Renderer* renderer;
		Window* window;
		InputManager* input;
		Scene* scene;
		ResourceManager* resourcemanager;
		GUI* gui;
		static Kernel* pInstance;
};
#endif