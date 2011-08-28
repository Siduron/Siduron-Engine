#include "TerrainTest.h"
#include "../Resources/EntityModel.h"
#include "../Resources/Terrain.h"

TerrainTest::TerrainTest()
{
	camera = Kernel::Instance()->GetRenderer()->GetCamera();
	this->terrain = new Terrain();
	terrain->Create(4);
	std::vector<int> terrainCenter = terrain->GetQuadtree()->GetMasterNode()->GetCenter();

	terrain->EnableDebug(false);
	Scene* scene = Kernel::Instance()->GetScene();
		
	scene->Add(camera);
	scene->Add(terrain);

	camera->SetPosition(terrainCenter[0],15,terrainCenter[1]);
	camera->Pitch(90);
	this->running = true;
	this->mLDown = false;

}

bool TerrainTest::Run()
{
	SDL_Event Event;
	while(SDL_PollEvent(&Event)) 
	{
		OnEvent(&Event);
    }
	
	//if(this->mLDown)
	//{
	//	this->terrain->Rotate(0,0.001,0);
	//}
	return this->running;
}

void TerrainTest::OnEvent(SDL_Event* Event)
{
    CEvent::OnEvent(Event);
}

void TerrainTest::OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle)
{

}

void TerrainTest::OnMouseWheel(bool Up, bool Down)
{
	if(Up)
	{
		camera->MoveY(-0.5f);
	}
	else if(Down)
	{
		camera->MoveY(0.5f);
	}
}

void TerrainTest::OnLButtonDown(int mX, int mY)
{
	this->mLDown = true;
}

void TerrainTest::OnLButtonUp(int mX, int mY)
{
	this->mLDown = false;
}

void TerrainTest::OnKeyDown(Uint8 scancode, SDLKey sym, SDLMod mod, Uint16 unicode)
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

void TerrainTest::OnKeyUp(Uint8 scancode, SDLKey sym, SDLMod mod, Uint16 unicode)
{

}

void TerrainTest::OnExit() 
{

}