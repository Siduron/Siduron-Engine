#include "ModelTest.h"
#include "../Core/Kernel.h"
#include "../Resources/EntityModel.h"

//Camera* camera;
EntityModel* generator;

ModelTest::ModelTest()
{
	Camera* camera = Kernel::Instance()->GetRenderer()->GetCamera();
	Scene* scene = Kernel::Instance()->GetScene();
	generator = new EntityModel();
	generator->SetModel("Content/Models/Shieldgenerator2/","towerWIP1.3DS");
	generator->SetShader("Content/Shaders/Model.fx");
	generator->SetPosition(0, 0, 0);
	generator->SetScale(0.05f,0.05f,0.05f);

	camera->SetPosition(0,2,-3);

	scene->Add(camera);
	scene->Add(generator);
}

bool ModelTest::Run()
{
	SDL_Event Event;
	while(SDL_PollEvent(&Event)) 
	{
		OnEvent(&Event);
    }
	/*if(Kernel::Instance()->GetWindow()->IsFocused())
	{
		std::queue<Input>* queue = Kernel::Instance()->GetInputManager()->GetKeyboardInput();
		if(!queue->empty())
		{
			for(unsigned int i = 0; i < queue->size(); i++)
			{
				if(queue->front().key == R)
				{
					Kernel::Instance()->GetResourceManager()->ReloadShaders();
				}
				queue->pop();
			}
		}
	}*/
	generator->Yaw(0.1f);
	return true;
}

void ModelTest::OnEvent(SDL_Event* Event)
{
    CEvent::OnEvent(Event);
}

void ModelTest::OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle)
{

}

void ModelTest::OnMouseWheel(bool Up, bool Down)
{

}

void ModelTest::OnLButtonDown(int mX, int mY)
{

}

void ModelTest::OnLButtonUp(int mX, int mY)
{

}

void ModelTest::OnKeyDown(Uint8 scancode, SDLKey sym, SDLMod mod, Uint16 unicode)
{

}

void ModelTest::OnKeyUp(Uint8 scancode, SDLKey sym, SDLMod mod, Uint16 unicode)
{

}

void ModelTest::OnExit() 
{

}