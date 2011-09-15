#include "RTStest.h"
#include "../Resources/EntityModel.h"
#include "../Resources/Terrain.h"



RTStest::RTStest()
{
	Logger::Instance()->Log("Creating scene..", Info);
	camera = Kernel::Instance()->GetRenderer()->GetCamera();
	this->engine = createIrrKlangDevice();
	this->engine->setSoundVolume( 0.5f );
	
	this->ambientsound = this->engine->play3D("Content/Sound/courtyard_birds_loop.wav", vec3df( camera->GetPosition().x, camera->GetPosition().y, camera->GetPosition().z ), true, false, true );
	this->ambientsound->setVolume( 0.5f );

	
	Logger::Instance()->Log("Creating terrain..", Info);
	this->terrain = new Terrain();
	this->terrain->Create( 250 );

	Logger::Instance()->Log("Creating Skybox..", Info);
	Scene* scene = Kernel::Instance()->GetScene();
	Skybox* skybox = new Skybox();
	skybox->SetModel("Content/Models/skybox/", "sky.3DS");
	skybox->SetShader("Content/Shaders/Skybox.fx");

	Logger::Instance()->Log("Creating entities..", Info);
	this->generator = new EntityModel();
	generator->SetModel("Content/Models/Shieldgenerator2/","towerWIP1.3DS");
	generator->SetShader("Content/Shaders/Model.fx");
	generator->SetPosition(125.75, 0, -125);
	generator->SetPosition(terrain->Collide(generator->GetPosition()));
	generator->SetScale(0.05f,0.05f,0.05f);

	EntityModel* dome = new EntityModel();
	dome->SetModel("Content/Models/Dome/","hollowsphere.X");
	dome->SetShader("Content/Shaders/Dome.fx");
	this->dome = dome;
	dome->SetPosition(generator->GetPosition());
	dome->SetScale(3.0,3.0,3.0);

	EntityModel* powerstation1 = new EntityModel();
	powerstation1->SetModel("Content/Models/Powerstation/","powerstation.3DS");
	powerstation1->SetShader("Content/Shaders/Model.fx");
	powerstation1->SetPosition(120, 0, 125);
	powerstation1->SetScale(0.05f,0.05f,0.05f);

	EntityModel* powerstation2 = new EntityModel();
	powerstation2->SetModel("Content/Models/Powerstation/","powerstation.3DS");
	powerstation2->SetShader("Content/Shaders/Model.fx");
	powerstation2->SetPosition(119, 0, 0);
	powerstation2->SetScale(0.05f,0.05f,0.05f);


	Logger::Instance()->Log("Adding entities to scene..", Info);
	scene->Add( skybox );
	scene->Add(camera);
	scene->Add(this->terrain);
	scene->Add(this->generator);
	scene->Add(dome);
	scene->Add(powerstation1);
	scene->Add(powerstation2);
	
	skybox->SetPosition(125,10,-125);
	camera->SetPosition(125,20,-125);
	camera->Pitch(90);

	this->scrollingLeft = false;
	this->scrollingRight = false;
	this->scrollingUp = false;
	this->scrollingDown = false;

	this->yawLeft = false;
	this->yawRight = false;
	this->forward = false;
	this->backward = false;
	this->strafeLeft = false;
	this->strafeRight = false;
	this->running = true;
	
	Logger::Instance()->Log("Creating sounds..", Info);
	this->domesound = this->engine->play3D("Content/Sound/iris_atlantis_loop.wav", vec3df( dome->GetPosition().x, dome->GetPosition().y, dome->GetPosition().z ), true, false, true );
	this->domesound->setPlaybackSpeed( 0.5f );
	this->watersound = this->engine->play3D("Content/Sound/rur5b_watersedgeamb.wav", vec3df( 0, 5, 0 ), true, false, true );

	if (domesound)
	{
		domesound->setMinDistance(5.0f);
	}
	ambientsound->setMinDistance(25.0f);
	float posOnCircle = 0;
    const float radius = 5;
}

bool RTStest::Run()
{
	Camera* cam = Kernel::Instance()->GetRenderer()->GetCamera();
	Vector lookAt = cam->GetLookAt();
	Vector relative_lookat = lookAt.Subtract( cam->GetPosition() );
	this->engine->setListenerPosition( vec3df( cam->GetPosition().x, cam->GetPosition().y, cam->GetPosition() .z ), vec3df( relative_lookat.x, relative_lookat.y, relative_lookat.z ) );
	this->watersound->setPosition( vec3df( cam->GetPosition().x, 5, cam->GetPosition().z ) );
	this->ambientsound->setPosition( vec3df( cam->GetPosition().x, 0, cam->GetPosition().z ) );

	SDL_Event Event;
	while(SDL_PollEvent(&Event)) 
	{
		OnEvent(&Event);
    }
/*	if(this->scrollingLeft)
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

	if( this->yawLeft )
	{
		this->camera->Yaw(0.5f);
	}
*/
	//else if( this->yawRight )
	//{
	//	this->camera->Yaw(-0.5f);
	//}

	if( this->forward )
	{
		this->camera->MoveForward(0.05f);
	}
	else if( this->backward )
	{
		this->camera->MoveForward(-0.05f);
	}

	if( this->strafeLeft )
	{
		this->camera->Strafe( -0.05f );
	}
	else if( this->strafeRight )
	{
		this->camera->Strafe( 0.05f );
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
	this->camera->Yaw( relX );
	this->camera->Pitch( relY );
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
void RTStest::OnKeyDown(Uint8 scancode, SDLKey sym, SDLMod mod, Uint16 unicode)
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
	if(keystates[SDLK_w])
	{
		this->forward = true;
	}
	else if(keystates[SDLK_s])
	{
		this->backward = true;
	}
	if(keystates[SDLK_d])
	{
		this->yawLeft = true;
		this->strafeRight = true;
	}
	if(keystates[SDLK_a])
	{
		this->yawRight = true;
		this->strafeLeft = true;
	}
	if(keystates[SDLK_1])
	{
		this->terrain->GetTerrainShader()->GetD3DEffect()->SetInt( "render_mode", 0 );
	}
	else if(keystates[SDLK_2])
	{
		this->terrain->GetTerrainShader()->GetD3DEffect()->SetInt( "render_mode", 1 );
	}
	else if(keystates[SDLK_3])
	{
		this->terrain->GetTerrainShader()->GetD3DEffect()->SetInt( "render_mode", 2 );
	}
	else if(keystates[SDLK_4])
	{
		this->terrain->GetTerrainShader()->GetD3DEffect()->SetInt( "render_mode", 3 );
	}
	else if(keystates[SDLK_EQUALS])
	{
		this->domesound->setPlaybackSpeed(this->domesound->getPlaybackSpeed() + 0.001f );
		this->dome->Scale( 0.01f, 0.01f, 0.01f);
	}
	else if(keystates[SDLK_MINUS])
	{
		this->domesound->setPlaybackSpeed(this->domesound->getPlaybackSpeed() - 0.001f );
		this->dome->Scale( -0.01f, -0.01f, -0.01f);
	}

}

void RTStest::OnKeyUp(Uint8 scancode, SDLKey sym, SDLMod mod, Uint16 unicode)
{
	//Get the keystates
	Uint8 *keystates = SDL_GetKeyState( NULL );
	if(!keystates[SDLK_w])
	{
		this->forward = false;
	}
	if(!keystates[SDLK_s])
	{
		this->backward = false;
	}
	if(!keystates[SDLK_d])
	{
		this->yawLeft = false;
		this->strafeRight = false;
	}
	if(!keystates[SDLK_a])
	{
		this->yawRight = false;
		this->strafeLeft = false;
	}
}

void RTStest::OnExit() {

}