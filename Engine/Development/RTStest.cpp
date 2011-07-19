#include "RTStest.h"
#include "../Resources/EntityModel.h"
#include "../Resources/Terrain.h"



RTStest::RTStest()
{
	camera = Kernel::Instance()->GetRenderer()->GetCamera();
	Terrain* terrain = new Terrain();
	terrain->Create(4);
	std::vector<int> terrainCenter = terrain->GetQuadtree()->GetMasterNode()->GetCenter();
	Scene* scene = Kernel::Instance()->GetScene();
	//
	//EntityModel* generator = new EntityModel();
	//generator->SetModel("Content/Models/Shieldgenerator2/","towerWIP1.3DS");
	//generator->SetShader("Content/Shaders/Model.fx");
	//generator->SetPosition(terrainCenter[0], 0, terrainCenter[1]);
	//generator->SetPosition(terrain->GetQuadtree()->GetMasterNode()->Collide(generator->GetPosition()));
	//generator->SetScale(0.05f,0.05f,0.05f);
	//terrain->GetQuadtree()->GetMasterNode()->CurrentNode(generator->GetPosition())->GetPatch()->EnableWireframe(true);

	//EntityModel* dome = new EntityModel();
	//dome->SetModel("Content/Models/Dome/","hollowsphere.X");
	//dome->SetShader("Content/Shaders/Dome.fx");
	//dome->SetPosition(generator->GetPosition());
	//dome->SetScale(3.0,3.0,3.0);

	//EntityModel* powerstation1 = new EntityModel();
	//powerstation1->SetModel("Content/Models/Powerstation/","powerstation.3DS");
	//powerstation1->SetShader("Content/Shaders/Model.fx");
	//powerstation1->SetPosition(terrainCenter[0]-5, 0, terrainCenter[1]);
	//powerstation1->SetPosition(terrain->GetQuadtree()->GetMasterNode()->Collide(powerstation1->GetPosition()));
	//powerstation1->SetScale(0.05f,0.05f,0.05f);

	//EntityModel* powerstation2 = new EntityModel();
	//powerstation2->SetModel("Content/Models/Powerstation/","powerstation.3DS");
	//powerstation2->SetShader("Content/Shaders/Model.fx");
	//powerstation2->SetPosition(terrainCenter[0]-6, 0, terrainCenter[1]);
	//powerstation2->SetPosition(terrain->GetQuadtree()->GetMasterNode()->Collide(powerstation2->GetPosition()));
	//powerstation2->SetScale(0.05f,0.05f,0.05f);


	scene->Add(camera);
	scene->Add(terrain);
	//scene->Add(generator);
	//scene->Add(dome);
	//scene->Add(powerstation1);
	//scene->Add(powerstation2);
	
	camera->SetPosition(terrainCenter[0],15,terrainCenter[1]);
	camera->Pitch(80);

	this->scrollingLeft = false;
	this->scrollingRight = false;
	this->scrollingUp = false;
	this->scrollingDown = false;
	this->running = true;

}

bool RTStest::Run()
{
	SDL_Event Event;
	while(SDL_PollEvent(&Event)) 
	{
		OnEvent(&Event);
    }
	if(this->scrollingLeft)
	{
		camera->MoveX(-0.10f);
	}
	else if(this->scrollingRight)
	{
		camera->MoveX(0.10f);
	}

	if(this->scrollingUp)
	{
		camera->MoveZ(-0.10f);
	}
	else if(this->scrollingDown)
	{
		camera->MoveZ(0.10f);
	}
	//if(Kernel::Instance()->GetWindow()->IsFocused())
	//{
	//	DIMOUSESTATE mousestate = Kernel::Instance()->GetInputManager()->GetMouseInput() ;
	//	long mouseX = mousestate.lX;
	//	long mouseY = mousestate.lY;
	//	long mouseZ = mousestate.lZ;

	//	if(timeGetTime() >= (timer+1))
	//	{
	//		timer = timeGetTime();
	//		//camera->Yaw(mouseX/2.0f);
	//		//camera->Pitch(mouseY/2.0f);
	//		if(mouseZ > 0 || mouseZ < 0)
	//		{
	//			camera->MoveY(-mouseZ/100.0f);
	//			if(mouseZ > 0)
	//			{
	//				camera->Pitch(-1.0f);
	//			}
	//			if(mouseZ < 0)
	//			{
	//				camera->Pitch(1.0f);
	//			}
	//		}
	//	}

	//	std::queue<Input>* queue = Kernel::Instance()->GetInputManager()->GetKeyboardInput();
	//	if(!queue->empty())
	//	{
	//		//if(timeGetTime() >= (keyTimer+10))
	//		//{
	//		for(unsigned int i = 0; i < queue->size(); i++)
	//		{
	//			if(queue->front().key == W)
	//			{
	//				camera->MoveZ(0.05f);
	//				keyTimer = timeGetTime();
	//			}
	//			else if(queue->front().key == D)
	//			{
	//				camera->MoveX(0.05f);
	//				keyTimer = timeGetTime();
	//			}
	//			else if(queue->front().key == A)
	//			{
	//				camera->MoveX(-0.05f);
	//				keyTimer = timeGetTime();
	//			}
	//			else if(queue->front().key == S)
	//			{
	//				camera->MoveZ(-0.05f);
	//				keyTimer = timeGetTime();
	//			}
	//			else if(queue->front().key == T)
	//			{
	//				//Kernel::Instance()->GetGUI()->Reload();
	//				keyTimer = timeGetTime();
	//			}
	//			if(queue->front().key == R)
	//			{
	//				Kernel::Instance()->GetResourceManager()->ReloadShaders();
	//			}
	//			else if(queue->front().key == ESCAPE)
	//			{
	//				return false;
	//			}
	//			queue->pop();
	//			
	//		}
	//		
	//		//}
	//	//}
	//}
	return this->running;
}

void RTStest::OnEvent(SDL_Event* Event)
{
    CEvent::OnEvent(Event);
}

void RTStest::OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle)
{
	if(mX <= 0+20)
	{
		this->scrollingLeft = true;
	}
	else
	{
		this->scrollingLeft = false;
	}

	if(mX >= SCREEN_WIDTH-20)
	{
		this->scrollingRight = true;
	}
	else
	{
		this->scrollingRight = false;
	}

	if(mY >= SCREEN_HEIGHT-20)
	{
		this->scrollingUp = true;
	}
	else
	{
		this->scrollingUp = false;
	}
	
	if(mY <= 0+20)
	{
		this->scrollingDown = true;
	}
	else
	{
		this->scrollingDown = false;
	}


	//if(mX >= SCREEN_WIDTH-20)
	//{
	//	camera->MoveX(0.05f);
	//	Logger::Instance()->Log("Right", Info);
	//}
	//else if(mX <= 0+20)
	//{
	//	camera->MoveX(-0.05f);
	//	Logger::Instance()->Log("Left", Info);
	//}

	//if(mY >= SCREEN_HEIGHT-20)
	//{
	//	camera->MoveZ(-0.05f);
	//	Logger::Instance()->Log("Down", Info);
	//}
	//else if(mY <= 0+20)
	//{
	//	camera->MoveZ(0.05f);
	//	Logger::Instance()->Log("Up", Info);
	//}
}

void RTStest::OnMouseWheel(bool Up, bool Down)
{
	if(Up)
	{
		camera->Pitch(-1.0f);
		camera->MoveY(-0.5f);
	}
	else if(Down)
	{
		camera->Pitch(1.0f);
		camera->MoveY(0.5f);
	}
}
void RTStest::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
	//Get the keystates
	Uint8 *keystates = SDL_GetKeyState( NULL );
	if(keystates[SDLK_ESCAPE])
	{
		this->running = false;
		Logger::Instance()->Log("escape", Info);
	}
	if(keystates[SDLK_LCTRL]&& keystates[SDLK_1])
	{
		Logger::Instance()->Log("ctrl 1", Info);
	}

}

void RTStest::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode)
{
	Logger::Instance()->Log("key down!", Info);
}

void RTStest::OnExit() {
    Logger::Instance()->Log("event!", Info);
}