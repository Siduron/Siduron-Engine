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
	generator->SetModel("Content/Models/Shieldgenerator2/","towerplaintexture.3DS");
	generator->SetShader("Content/Shaders/Model.fx");
	generator->SetPosition(0, 0, 0);
	generator->SetScale(0.05f,0.05f,0.05f);

	camera->SetPosition(0,2,-3);

	scene->Add(camera);
	scene->Add(generator);
}

bool ModelTest::Run()
{
	generator->Yaw(0.1f);
	return true;
}