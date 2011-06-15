#include "RTStest.h"
#include "../Core/Kernel.h"
#include "../Resources/EntityModel.h"
#include "../Resources/Terrain.h"

float timer;
float keyTimer;
Camera* camera;

RTStest::RTStest()
{
	camera = Kernel::Instance()->GetRenderer()->GetCamera();
	/*Terrain* terrain = new Terrain();
	terrain->Create(8);
	std::vector<int> terrainCenter = terrain->GetQuadtree()->GetMasterNode()->GetCenter();
	*/
	Scene* scene = Kernel::Instance()->GetScene();
	/*
	EntityModel* generator = new EntityModel();
	generator->SetModel("Content/Models/Shieldgenerator2/","towerWIP1.3DS");
	generator->SetShader("Content/Shaders/Model.fx");
	generator->SetPosition(terrainCenter[0], 0, terrainCenter[1]);
	generator->SetPosition(terrain->GetQuadtree()->GetMasterNode()->Collide(generator->GetPosition()));
	generator->SetScale(0.05f,0.05f,0.05f);

	EntityModel* dome = new EntityModel();
	dome->SetModel("Content/Models/Dome/","hollowsphere.X");
	dome->SetShader("Content/Shaders/Dome.fx");
	dome->SetPosition(generator->GetPosition());
	dome->SetScale(3.0,3.0,3.0);

	EntityModel* powerstation1 = new EntityModel();
	powerstation1->SetModel("Content/Models/Powerstation/","powerstation.3DS");
	powerstation1->SetShader("Content/Shaders/Model.fx");
	powerstation1->SetPosition(terrainCenter[0]-5, 0, terrainCenter[1]);
	powerstation1->SetPosition(terrain->GetQuadtree()->GetMasterNode()->Collide(powerstation1->GetPosition()));
	powerstation1->SetScale(0.05f,0.05f,0.05f);

	EntityModel* powerstation2 = new EntityModel();
	powerstation2->SetModel("Content/Models/Powerstation/","powerstation.3DS");
	powerstation2->SetShader("Content/Shaders/Model.fx");
	powerstation2->SetPosition(terrainCenter[0]-6, 0, terrainCenter[1]);
	powerstation2->SetPosition(terrain->GetQuadtree()->GetMasterNode()->Collide(powerstation2->GetPosition()));
	powerstation2->SetScale(0.05f,0.05f,0.05f);*/


	scene->Add(camera);
	//scene->Add(terrain);
	//scene->Add(generator);
	//scene->Add(dome);
	//scene->Add(powerstation1);
	//scene->Add(powerstation2);
	
	//camera->SetPosition(terrainCenter[0],15,terrainCenter[1]);
	camera->Pitch(80);
}

bool RTStest::Run()
{
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
				camera->MoveY(-mouseZ/100.0f);
				if(mouseZ > 0)
				{
					camera->Pitch(-1.0f);
				}
				if(mouseZ < 0)
				{
					camera->Pitch(1.0f);
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
					//Kernel::Instance()->GetGUI()->Reload();
					keyTimer = timeGetTime();
				}
				if(queue->front().key == R)
				{
					Kernel::Instance()->GetResourceManager()->ReloadShaders();
				}
				else if(queue->front().key == ESCAPE)
				{
					return false;
				}
				queue->pop();
				
			}
			
			//}
		}
	}
	return true;
}