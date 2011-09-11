#include "Scene.h"
#include "../Util/Logger.h"
#include "../Core/Kernel.h"
#include <mmsystem.h> 

Scene::Scene()
{
	this->atmosRange = 13;
}

bool Scene::Init()
{
	this->masterNode = new SceneManagement::Node();
	this->CreateLoadingScreen();
	this->camera = Kernel::Instance()->GetRenderer()->GetCamera();
	//this->camera->SetPosition(0.0f, 0.0f, -2.0f);
	//this->Add(this->camera);
	//this->camera->SetPosition(41.9799, 10, -39.4881);
	//this->terrain = new Terrain(Kernel::Instance()->GetRenderer());
	//this->terrain->SetCameraPosition(this->camera->GetPosition());
	//this->terrain->Create(mapName, size);
	//this->Add(this->terrain);
	
	//this->domeshader = Kernel::Instance()->GetResourceManager()->LoadShader("Content/Shaders/Dome.fx");
	//Shader* defaultShader = Kernel::Instance()->GetResourceManager()->LoadShader("Content/Shaders/Default.fx"); 
	//Shader* modelShader = Kernel::Instance()->GetResourceManager()->LoadShader("Content/Shaders/Model.fx"); 

	//Entities
	Logger::Instance()->Log("Creating Entities..", Info);
	//EntityModel* generator = new EntityModel();
	//generator->SetModel("Content/Models/Shieldgenerator2/","towerplaintexture.3DS");
	//generator->SetShader("Content/Shaders/Model.fx");
	//generator->SetPosition(41.9799, 1.8, -29.4881);
	//generator->SetPosition(this->terrain->Collide(generator->GetPosition()));
	//generator->SetScale(0.1f,0.1f,0.1f);
	//this->Add(generator);
	//this->generator = generator;

	//Entity* dome = new Entity();
	//dome->AddModel("Content/Models/Dome/","hollowsphere.3DS");
	//dome->SetShader("Content/Shaders/Dome.fx");
	//dome->SetPosition(41.9799, 1.75762, -29.4881);
	////dome->SetPosition(this->terrain->Collide(dome->GetPosition()));
	//dome->SetScale(0.5,0.5,0.5);
	////this->Add(dome);

	//EntityModel* newTree1 = new EntityModel();
	//newTree1->SetModel("Content/Models/wowtree/","treecanopy01.ms3d");
	//newTree1->SetShader("Content/Shaders/Model.fx");
	//newTree1->SetPosition(generator->GetPosition()->x+5,generator->GetPosition()->y,generator->GetPosition()->z);
	//newTree1->SetScale(0.1f,0.1f,0.1f);
	////generator->AddChildNode(newTree1);

	//EntityModel* newTree2 = new EntityModel();
	//newTree2->SetModel("Content/Models/wowtree/","treecanopy01.ms3d");
	//newTree2->SetShader("Content/Shaders/Model.fx");
	//newTree2->SetPosition(generator->GetPosition()->x-5,generator->GetPosition()->y,generator->GetPosition()->z);
	//newTree2->SetScale(0.1f,0.1f,0.1f);
	//generator->AddChildNode(newTree2);

	float rnd = rand() / 10;

	//for(int a = 0; a < 5; a++)
	//{
	//	for(int b = 0; b < 5; b++)
	//	{
	//		float spawnTree = rand()%4;
	//		if(spawnTree <= 4.0f)
	//		{
	//			Entity* newTree = new Entity();
	//			newTree->AddModel(treemodel);
	//			newTree->SetPosition(0+(a*(5.1+(rand()%10))), 0, 0-(b*(5.1+(rand()%10))));
	//			newTree->SetYaw(rand()%360);
	//			newTree->SetScale(0.1f,0.1f,0.1f);
	//			Vector* newPos = this->terrain->Collide(newTree->GetPosition());
	//			newPos->y -= 0.2;
	//			newTree->SetPosition(newPos);
	//			newTree->SetShader(modelShader);
	//			generator->AddChildNode(newTree);
	//		}
	//	}
	//}
	
	//this->atmosGen = generator->GetPosition();
	
	//Skybox
	Logger::Instance()->Log("Creating Skybox..", Info);
	//Model* sky = Kernel::Instance()->GetResourceManager()->GetModel("Content/Models/skysphere/", "skysphere.x");
	//sky->SetShader("Content/Shaders/Default.fx");

	//this->skybox = new EntityModel();
	//this->skybox->SetModel("Content/Models/skysphere/", "skysphere.x");
	//this->skybox->SetShader("Content/Shaders/Skybox.fx");
	//this->skybox->SetPosition(4, 4, 4);
	//this->Add(this->skybox);

	//EntityModel* leftCube = new EntityModel();
	//leftCube->SetModel("Content/Models/", "cube.x");
	//leftCube->SetShader("Content/Shaders/Model.fx");
	//leftCube->SetPosition(-5, 0, 0);

	//EntityModel* middleCube = new EntityModel();
	//middleCube->SetModel("Content/Models/", "cube.x");
	//middleCube->SetShader("Content/Shaders/Model.fx");
	//middleCube->SetPosition(0, 0, 0);

	//EntityModel* rightCube = new EntityModel();
	//rightCube->SetModel("Content/Models/", "cube.x");
	//rightCube->SetShader("Content/Shaders/Model.fx");
	//rightCube->SetPosition(5, 0, 0);
	
	//this->Add(middleCube);
	//middleCube->AddChildNode(leftCube);
	//middleCube->AddChildNode(rightCube);
	//this->tehCube = middleCube;
	//this->leftCube = leftCube;
	//this->skybox->BindToCamera(cam);


	this->timer = (float)timeGetTime();

	
	//Vector* newCampos = this->terrain->Collide(this->camera->GetPosition());
	//newCampos->y += 0.5;
	//this->camera->SetPosition(newCampos);
	
	return true;
}

void Scene::Add(SceneManagement::Node* node)
{
	this->masterNode->AddChildNode(node);
}

void Scene::Render()
{
	this->GetMasterNode()->Update();
	this->GetMasterNode()->Render();
	//this->skybox->Render();
	//this->generator->MoveForward(0.01f);
	//this->generator->Yaw(0.01f);
	//this->tehCube->MoveX(-0.01f);
	//this->tehCube->Yaw(0.1f);
	//this->tehCube->Scale(0.01f,0.01f,0.01f);
	//this->tehCube->Roll(0.5f);

	//this->leftCube->Yaw(1.0f);

	//Vector* newCampos = this->terrain->Collide(this->camera->GetPosition());
	//newCampos->y += 0.5;
	//newCampos->y += 0.5;

	//this->camera->SetPosition(newCampos);
	//this->atmosRange += 0.01;
	//Patch* currentPatch = this->terrain->GetQuadtree()->GetMasterNode()->CurrentNode(this->camera->GetPosition())->GetPatch();
	//if(currentPatch->atmosphere < 1.0)
	//{
	//	Shader* pp = Kernel::Instance()->GetRenderer()->GetPostprocessShader();
	//	pp->GetD3DEffect()->SetFloat( "blue", -currentPatch->atmosphere/10);
	//	pp->GetD3DEffect()->SetFloat( "green", -currentPatch->atmosphere/10);
	//	pp->GetD3DEffect()->SetFloat( "contrast", 2.0f - currentPatch->atmosphere);
	//	pp->GetD3DEffect()->SetFloat( "atmosphere", 1.0);
	//}
	//else
	//{
	//	Shader* pp = Kernel::Instance()->GetRenderer()->GetPostprocessShader();
	//	pp->GetD3DEffect()->SetFloat( "blue", 0.0f);
	//	pp->GetD3DEffect()->SetFloat( "green", 0.0f);
	//	pp->GetD3DEffect()->SetFloat( "contrast", 1.0f);
	//	pp->GetD3DEffect()->SetFloat( "atmosphere", 1.0);
	//}
}

void Sound(char*name)
{
	PlaySound(name,NULL,SND_ASYNC);
}

void Scene::CreateLoadingScreen()
{
	//Texture* lscreen = Kernel::Instance()->GetResourceManager()->GetTexture("Content/Textures/gui/loadingscreen.jpg");
	//	
	//LPD3DXSPRITE sprite; //Create Sprite object
	//D3DXCreateSprite(Kernel::Instance()->GetRenderer()->GetDevice(), &sprite);    //Init Sprite object

	//D3DXVECTOR3 center(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
	//D3DXVECTOR3 position(0.0f, 0.0f, 0.0f);    // position at 50, 50 with no depth
	//
	//Kernel::Instance()->GetRenderer()->BeginScene(); //Start render
	//sprite->Begin(NULL);    // begin sprite drawing
	//sprite->Draw(lscreen->GetD3DTexture(), NULL, &center, &position, D3DCOLOR_XRGB(255, 255, 255));  // draw it!
	//sprite->End();    // end sprite drawing
	//sprite->Release(); //Release the sprite object from memory
	//Kernel::Instance()->GetRenderer()->EndScene(); //End render, present to screen
	//Kernel::Instance()->GetRenderer()->Present();
	//Kernel::Instance()->GetResourceManager()->DeleteTexture("Content/Textures/gui/loadingscreen.jpg");
}

Terrain* Scene::GetTerrain()
{
	return this->terrain;
}

Camera* Scene::GetActiveCamera()
{
	return this->camera;
}

//Skybox* Scene::GetSkybox()
//{
//	return this->skybox;
//}

SceneManagement::Node* Scene::GetMasterNode()
{
	return this->masterNode;
}

void Scene::SetSkybox( EntityModel* skybox )
{
	this->skybox = skybox;
}


Scene::~Scene()
{
	if(!this->terrain) delete this->terrain;
}