#include "EntityModel.h"
#include "../Core/Kernel.h"

EntityModel::EntityModel()
{
	this->scale = new Vector(1.0f,1.0f,1.0f);
}
void EntityModel::Render()
{
	this->model->Render(this->matWorld);
	Entity::Render();
}

void EntityModel::Update()
{
	Renderer* renderer = Kernel::Instance()->GetRenderer();
	Camera* cam = renderer->GetCamera();
		
	//D3DXMatrixRotationX( &this->matRotateX, this->rotation->x );        // Pitch
	//D3DXMatrixRotationY( &this->matRotateY, this->rotation->y );        // Yaw
	//D3DXMatrixRotationZ( &this->matRotateZ, this->rotation->z );        // Roll
	//D3DXMatrixTranslation( &this->matTranslate, this->position->x,this->position->y,this->position->z );
	//D3DXMatrixScaling( &this->matScale, this->scale->x,this->scale->y,this->scale->z);

	//this->matRotation = this->matRotateZ*this->matRotateX*this->matRotateY;
	//this->matWorld = this->matRotation * this->matScale * this->matTranslate;
	//this->matWorld = this->matTranslate;
	Entity::Update();
}

void EntityModel::SetScale(Vector* scale)
{
	this->SetScale(scale->x, scale->y, scale->x);
}

void EntityModel::SetScale(float x, float y, float z)
{
	this->scale->x = x;
	this->scale->y = y;
	this->scale->z = z;
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

Vector* EntityModel::GetScale()
{
	return this->scale;
}

Model* EntityModel::GetModel()
{
	return this->model;
}

void EntityModel::Scale(float x, float y, float z)
{
	this->scale->x += x;
	this->scale->y += y;
	this->scale->z += z;
	Node::SetScale(this->scale->x,this->scale->y,this->scale->z);
}