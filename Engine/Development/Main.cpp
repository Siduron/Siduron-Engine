#include "../Util/Logger.h"
#include "../Core/Kernel.h"
#include "../Resources/Camera.h"
#include "scenegraphTest.h"
#include "RTStest.h"
#include "ModelTest.h"

//Camera* camera = new Camera();
//
//float timer;
//float keyTimer;
//HINSTANCE hInstancez= GetModuleHandle (0);
bool SetupEngine();
bool EngineLoop();

//ScenegraphTest* graphTest;
//RTStest* rtsTest;
ModelTest* modelTest;

int main()
{
	//Logger::Instance()->Log("Starting..", Info);
	if(SetupEngine())
	{
		while(EngineLoop());
	}
	else
	{
		std::cin.get();
	}
	return 0;
}

bool SetupEngine()
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
	///*Kernel::Instance()->GetRenderer()->SetCamera(camera);*/
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
	//graphTest = new ScenegraphTest();
	Kernel::Instance();
	//rtsTest = new RTStest();
	modelTest = new ModelTest();
	//Logger::Instance()->Log("Running..", Info);
	return true;
}

bool EngineLoop()
{   
	Kernel::Instance()->GetRenderer()->BeginScene();
	Kernel::Instance()->GetScene()->Render();
	Kernel::Instance()->GetGUI()->Render();
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
	if(!modelTest->Run())
		return false;
	Kernel::Instance()->GetWindow()->Update();
	//Kernel::Instance()->GetGUI()->Render();
    Kernel::Instance()->GetRenderer()->EndScene();
	
	return true;
}