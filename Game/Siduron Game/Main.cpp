#include "Util/Logger.h"
#include "Core/Kernel.h"
#include "Resources/Camera.h"
#include "Resources/Model.h"
#include "GameObject.h"
#include "World.h"

Camera* camera;
float timer;
float keyTimer;
HINSTANCE hInstancez= GetModuleHandle (0);
bool SetupGame();
bool GameLoop();
GameObject* npc = new GameObject();
World* world = new World();

int main()
{
	Logger::Instance()->Log("Starting..", Info);
	if(SetupGame())
	{
		while(GameLoop());
	}
	else
	{
		std::cin.get();
	}
	return 0;
}

bool SetupGame()
{
	//Logger::Instance()->Log("Initializing Engine..", Info);
	//Kernel::Instance()->GetWindow()->SetSize(800,600);
	//	
	//if(!Kernel::Instance()->GetWindow()->MakeWindow())
	//{
	//	Logger::Instance()->Log("Failed creating Window", Error);
	//	return false;
	//}
	//Logger::Instance()->Log("Initializing Renderer..", Info);
	//if(!Kernel::Instance()->GetRenderer()->InitDirect3D(Kernel::Instance()->GetWindow()->GetHWND()))
	//{
	//	Logger::Instance()->Log("Failed initializing Renderer", Error);
	//	return false;
	//}
	//Kernel::Instance()->GetRenderer()->SetCamera(camera);
	//Logger::Instance()->Log("Initializing Input..", Info);
	//if(!Kernel::Instance()->GetInputManager()->InitInput(hInstancez,Kernel::Instance()->GetWindow()->GetHWND()))
	//{
	//	Logger::Instance()->Log("Failed initializing Input", Error);
	//	return false;
	//}
	//Logger::Instance()->Log("Initializing Scene..", Info);
	//if(!Kernel::Instance()->GetScene()->Init())
	//{
	//	Logger::Instance()->Log("Failed initializing Scene", Error);
	//	return false;
	//}

	/*Logger::Instance()->Log("Initializing GUI..", Info);
	Kernel::Instance()->GetGUI()->Init();*/
	//Logger::Instance()->Log("Running..", Info);
	camera = Kernel::Instance()->GetRenderer()->GetCamera();
	world->CreateTerrain(8);
	std::vector<int> terrainCenter = world->GetTerrain()->GetQuadtree()->GetMasterNode()->GetCenter();
	camera->SetPosition(32,5,-32);
	camera->Pitch(80);


	GameObject* generator = new GameObject();
	generator->GetEntity()->SetModel("Content/Models/Shieldgenerator2/","towerplaintexture.3DS");
	generator->GetEntity()->SetShader("Content/Shaders/Model.fx");
	generator->SetPosition(terrainCenter[0], 0, terrainCenter[1]);
	//Vector pos = generator->GetPosition();
	//Vector test = world->GetTerrain()->(generator->GetPosition());
	generator->SetPosition(world->GetTerrain()->GetQuadtree()->GetMasterNode()->Collide(generator->GetPosition()));
	generator->GetEntity()->SetScale(0.05f,0.05f,0.05f);

	world->Add(generator);
	
	Logger::Instance()->Log("Running Game", Info);
	return true;
}

bool GameLoop()
{
	Kernel::Instance()->GetRenderer()->BeginScene();
	Kernel::Instance()->GetScene()->Render();
	if(Kernel::Instance()->GetWindow()->IsFocused())
	{
		DIMOUSESTATE mousestate = Kernel::Instance()->GetInputManager()->GetMouseInput() ;
		long mouseX = mousestate.lX;
		long mouseY = mousestate.lY;
		long mouseZ = mousestate.lZ;

		if(timeGetTime() >= (timer+1))
		{
			timer = timeGetTime();
			//camera->Yaw(mouseX/2.0f);
			//camera->Pitch(mouseY/2.0f);
			if(mouseZ > 0 || mouseZ < 0)
			{
				Kernel::Instance()->GetRenderer()->GetCamera()->MoveY(-mouseZ/100.0f);
				if(mouseZ > 0)
				{
					Kernel::Instance()->GetRenderer()->GetCamera()->Pitch(-1.0f);
				}
				if(mouseZ < 0)
				{
					Kernel::Instance()->GetRenderer()->GetCamera()->Pitch(1.0f);
				}
			}
		}

		std::queue<Input>* queue = Kernel::Instance()->GetInputManager()->GetKeyboardInput();
		if(!queue->empty())
		{
			//if(timeGetTime() >= (keyTimer+10))
			//{
			for(unsigned int i = 0; i < queue->size(); i++)
			{
				if(queue->front().key == W)
				{
					camera->MoveZ(0.05f);
					keyTimer = timeGetTime();
				}
				else if(queue->front().key == D)
				{
					camera->MoveX(0.05f);
					keyTimer = timeGetTime();
				}
				else if(queue->front().key == A)
				{
					camera->MoveX(-0.05f);
					keyTimer = timeGetTime();
				}
				else if(queue->front().key == S)
				{
					camera->MoveZ(-0.05f);
					keyTimer = timeGetTime();
				}
				else if(queue->front().key == T)
				{
					Kernel::Instance()->GetScene()->GetTerrain()->ToggleWireframe();
					keyTimer = timeGetTime();
				}
				//else if(queue->front().key == C)
				//{
				//	middleCube->Yaw(0.1f);
				//}
				//else if(queue->front().key == Z)
				//{
				//	middleCube->Yaw(-0.1f);
				//}
				else if(queue->front().key == ESCAPE)
				{
					return false;
				}
				queue->pop();
				
			}
			
			//}
		}
	}
	Kernel::Instance()->GetWindow()->Update();
	Kernel::Instance()->GetGUI()->Render();
    Kernel::Instance()->GetRenderer()->EndScene();
	
	return true;
}