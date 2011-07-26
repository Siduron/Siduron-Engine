#include "../Util/Logger.h"
#include "../Core/Kernel.h"
#include "../Resources/Camera.h"
#include "scenegraphTest.h"
#include "RTStest.h"
#include "ModelTest.h"
#include "TerrainTest.h"

//Camera* camera = new Camera();
//
//float timer;
//float keyTimer;
//HINSTANCE hInstancez= GetModuleHandle (0);
bool SetupEngine();
bool EngineLoop();

//ScenegraphTest* graphTest;
//RTStest* rtsTest;
//ModelTest* modelTest;
TerrainTest* terrainTest;

int main(int argc, char *argv[])
{
	//Logger::Instance()->Log("Starting..", Info);
	if(SetupEngine())
	{
		while(EngineLoop());
		delete Kernel::Instance();
	}
	else
	{
		std::cin.get();
	}
	return 0;
}

void LoadingScreen()
{
	Texture* lscreen = Kernel::Instance()->GetResourceManager()->GetTexture("Content/Textures/gui/loadingscreen.jpg");
		
	LPD3DXSPRITE sprite; //Create Sprite object
	D3DXCreateSprite(Kernel::Instance()->GetRenderer()->GetDevice(), &sprite);    //Init Sprite object

	D3DXVECTOR3 center(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
	D3DXVECTOR3 position(0.0f, 0.0f, 0.0f);    // position at 50, 50 with no depth
	
	Kernel::Instance()->GetRenderer()->BeginScene();
	sprite->Begin(NULL);    // begin sprite drawing
	sprite->Draw(lscreen->GetD3DTexture(), NULL, &center, &position, D3DCOLOR_XRGB(255, 255, 255));  // draw it!
	sprite->End();    // end sprite drawing
	sprite->Release(); //Release the sprite object from memory
	Kernel::Instance()->GetRenderer()->Present();
	Kernel::Instance()->GetRenderer()->EndScene();
	Kernel::Instance()->GetResourceManager()->DeleteTexture("Content/Textures/gui/loadingscreen.jpg");
}

bool SetupEngine()
{
	//graphTest = new ScenegraphTest();
	
	//LoadingScreen();

	Kernel::Instance();
	//rtsTest = new RTStest();
	//modelTest = new ModelTest();
	terrainTest = new TerrainTest();
	//Logger::Instance()->Log("Running..", Info);
	return true;
}

bool EngineLoop()
{   
	Kernel::Instance()->GetRenderer()->BeginScene();
	Kernel::Instance()->GetScene()->Render();
	//Kernel::Instance()->GetGUI()->Render();
	Kernel::Instance()->GetRenderer()->EndScene();
	Kernel::Instance()->GetRenderer()->Present();
	
	//if(Kernel::Instance()->GetWindow()->IsFocused())
	//{
	//	DIMOUSESTATE mousestate = Kernel::Instance()->GetInputManager()->GetMouseInput() ;
	//	long mouseX = mousestate.lX;
	//	long mouseY = mousestate.lY;
	//		   
	//	if(timeGetTime() >= (timer+1))
	//	{
	//		timer = timeGetTime();
	//		camera->Yaw(mouseX/2.0f);
	//		camera->Pitch(mouseY/2.0f);
	//	}
	//}
	//
	//if(Kernel::Instance()->GetWindow()->IsFocused())
	//{
	//	std::queue<Input>* queue = Kernel::Instance()->GetInputManager()->GetKeyboardInput();
	//	if(!queue->empty())
	//	{
	//		if(timeGetTime() >= (keyTimer+10))
	//		{
	//		for(unsigned int i = 0; i < queue->size(); i++)
	//		{
	//			if(queue->front().key == W)
	//			{
	//				camera->MoveForward(0.05f);
	//				keyTimer = timeGetTime();
	//			}
	//			else if(queue->front().key == D)
	//			{
	//				camera->Strafe(0.05f);
	//				keyTimer = timeGetTime();
	//			}
	//			else if(queue->front().key == A)
	//			{
	//				camera->Strafe(-0.05f);
	//				keyTimer = timeGetTime();
	//			}
	//			else if(queue->front().key == S)
	//			{
	//				camera->MoveForward(-0.05f);
	//				keyTimer = timeGetTime();
	//			}
	//			else if(queue->front().key == T)
	//			{
	//				Kernel::Instance()->GetScene()->GetTerrain()->ToggleWireframe();
	//				keyTimer = timeGetTime();
	//			}
	//			//else if(queue->front().key == C)
	//			//{
	//			//	middleCube->Yaw(0.1f);
	//			//}
	//			//else if(queue->front().key == Z)
	//			//{
	//			//	middleCube->Yaw(-0.1f);
	//			//}
	//			else if(queue->front().key == ESCAPE)
	//			{
	//				return false;
	//			}
	//			queue->pop();
	//			
	//		}
	//		
	//		}
	//	}
	//}
	//graphTest->Run();
	if(!terrainTest->Run())
		return false;
	//Kernel::Instance()->GetWindow()->Update();
	//Kernel::Instance()->GetGUI()->Render();
    
	
	return true;
}