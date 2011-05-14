#include "scenegraphTest.h"
#include "../Core/Kernel.h"
ScenegraphTest::ScenegraphTest()
{
	Scene* scene = Kernel::Instance()->GetScene();


	EntityModel* leftCube = new EntityModel();
	leftCube->SetModel("Content/Models/", "cube.x");
	leftCube->SetShader("Content/Shaders/Model.fx");
	leftCube->SetPosition(10, 0, 0);

	this->middleCube = new EntityModel();
	this->middleCube->SetModel("Content/Models/", "cube.x");
	this->middleCube->SetShader("Content/Shaders/Model.fx");
	this->middleCube->SetPosition(5, 0, 0);

	EntityModel* rightCube = new EntityModel();
	rightCube->SetModel("Content/Models/", "cube.x");
	rightCube->SetShader("Content/Shaders/Model.fx");
	rightCube->SetPosition(15, 0, 0);

	//leftCube->AddChildNode(middleCube);
	middleCube->AddChildNode(rightCube);

	//terrain = new Terrain();
	//terrain->Create("Tropical", 8);
	scene->Add(middleCube);
	//scene->Add(terrain);
}
void ScenegraphTest::Run()
{
	std::queue<Input>* queue = Kernel::Instance()->GetInputManager()->GetKeyboardInput();
	if(!queue->empty())
	{
		for(unsigned int i = 0; i < queue->size(); i++)
		{
			if(queue->front().key == Z)
			{
				this->middleCube->MoveX(0.01f);
			}
			else if(queue->front().key == C)
			{
				this->middleCube->MoveX(-0.01f);
			}
		}
	}

	
}