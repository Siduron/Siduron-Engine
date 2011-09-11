#include "EntityModel.h"
#include "../Core/Kernel.h"

EntityModel::EntityModel()
{
	this->scale = Vector(1.0f,1.0f,1.0f);
	this->model = NULL;
}

void EntityModel::Render()
{
	if(this->model != NULL)
	{
		this->model->Render(this->matWorld);
	}
	Entity::Render();
}

void EntityModel::Update()
{
	Entity::Update();
}

void EntityModel::SetScale(Vector scale)
{
	this->SetScale(scale.x, scale.y, scale.x);
}

void EntityModel::SetScale(float x, float y, float z)
{
	this->scale.x = x;
	this->scale.y = y;
	this->scale.z = z;
	Node::SetScale(x,y,z);
}

void EntityModel::SetModel(const std::string modelPath, const std::string modelName)
{
	this->model = Kernel::Instance()->GetResourceManager()->GetModel(modelPath, modelName);
}

void EntityModel::SetShader(std::string path)
{
	this->model->SetShader(path);
}

Vector EntityModel::GetScale()
{
	return this->scale;
}

Model* EntityModel::GetModel()
{
	return this->model;
}

void EntityModel::Scale(float x, float y, float z)
{
	this->scale.x += x;
	this->scale.y += y;
	this->scale.z += z;
	Node::SetScale(this->scale.x,this->scale.y,this->scale.z);
}