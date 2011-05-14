#include "GameObject.h"

GameObject::GameObject()
{
	this->entity = new EntityModel();
}

void GameObject::SetModel(std::string modelPath, std::string modelName)
{
	this->entity->SetModel(modelPath, modelName);
}

void GameObject::SetPosition(int x,int y,int z)
{
	this->entity->SetPosition(x,y,z);
}

void GameObject::SetPosition(Vector pos)
{
	this->entity->SetPosition(pos);
}

Vector GameObject::GetPosition() const
{
	return this->entity->GetPosition();
}

EntityModel* GameObject::GetEntity()
{
	return this->entity;
}

GameObject::~GameObject()
{
	delete this->entity;
}