#include "Kernel.h"

Kernel* Kernel::pInstance = NULL;

Kernel::Kernel()
{
	renderer = new Renderer();
	window = new SDLWindow(SCREEN_WIDTH, SCREEN_HEIGHT);
	input = new InputManager();
	scene = new Scene();
	resourcemanager = new ResourceManager();
	gui = new GUI(renderer);
}

Kernel* Kernel::Instance()
{
	if(pInstance == NULL)
	{
		pInstance = new Kernel();

		Logger::Instance()->Log("Initializing Engine..", Info);
		//Kernel::Instance()->GetWindow()->SetSize(800,600);

		/*if(!Kernel::Instance()->GetWindow()->MakeWindow())
		{
			Logger::Instance()->Log("Failed creating Window", Error);
		}*/
		Logger::Instance()->Log("Initializing Renderer..", Info);
		if(!Kernel::Instance()->GetRenderer()->InitDirect3D(Kernel::Instance()->GetWindow()->GetHandle()))
		{
			Logger::Instance()->Log("Failed initializing Renderer", Error);
		}
		else
		{
			/*Logger::Instance()->Log("Initializing GUI..", Info);
			Kernel::Instance()->GetGUI()->Init();*/

			//Kernel::Instance()->GetRenderer()->SetCamera(camera);
			/*Logger::Instance()->Log("Initializing Input..", Info);
			if(!Kernel::Instance()->GetInputManager()->InitInput(GetModuleHandle (0),Kernel::Instance()->GetWindow()->GetHWND()))
			{
				Logger::Instance()->Log("Failed initializing Input", Error);
			}*/
			Logger::Instance()->Log("Initializing Scene..", Info);
			if(!Kernel::Instance()->GetScene()->Init())
			{
				Logger::Instance()->Log("Failed initializing Scene", Error);
			}

			Logger::Instance()->Log("Engine running..", Info);
		}
	}
	return pInstance;
}

Renderer* Kernel::GetRenderer()
{
	return renderer;
}

SDLWindow* Kernel::GetWindow()
{
	return window;
}

InputManager* Kernel::GetInputManager()
{
	return input;
}

Scene* Kernel::GetScene()
{
	return scene;
}

GUI* Kernel::GetGUI()
{
	return gui;
}

ResourceManager* Kernel::GetResourceManager()
{
	return resourcemanager;
}

Kernel::~Kernel()
{
	delete this->renderer;
	delete this->window;
	delete this->resourcemanager;
	delete this->input;
}