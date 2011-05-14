#include "Entity.h"
#include "../Core/DEGTORAD.h"
#include "../Core/Kernel.h"

Entity::Entity()
{

}

Entity::~Entity()
{

}

void Entity::Render()
{
	Node::Render();
}

void Entity::SetPosition(float x, float y, float z)
{
	this->position.x = x;
	this->position.y = y;
	this->position.z = z;
	Node::SetTranslation(x,y,z);
}

void Entity::SetPosition(Vector pos)
{
	this->SetPosition(pos.x, pos.y, pos.z);
}

void Entity::SetRotation(Vector rot)
{
	this->rotation = rot;
}

void Entity::SetRotation(float x,float y, float z)
{
	this->rotation.x = x;
	this->rotation.y = y;
	this->rotation.z = z;
	Node::SetRotation(x,y,z);
}

void Entity::SetPitch(float amount)
{
	this->rotation.x = DEGTORAD(amount);
}

void Entity::SetYaw(float amount)
{
	this->rotation.y = DEGTORAD(amount);
}

void Entity::SetRoll(float amount)
{
	this->rotation.z = DEGTORAD(amount);
}

const Vector& Entity::GetPosition() const
{
	return this->position;
}

const Vector& Entity::GetRotation() const
{
	return this->rotation;
}

const float& Entity::GetPitch() const
{
	return RADTODEG(this->rotation.x);
}

const float& Entity::GetYaw() const
{
	return RADTODEG(this->rotation.y);
}

const float& Entity::GetRoll() const
{
	return RADTODEG(this->rotation.z);
}

void Entity::MoveX(float amount)
{
	this->position.x += amount;
	Node::SetTranslation(this->position.x,this->position.y,this->position.z);
}

void Entity::MoveY(float amount)
{
	this->position.y += amount;
	Node::SetTranslation(this->position.x,this->position.y,this->position.z);
}

void Entity::MoveZ(float amount)
{
	this->position.z += amount;
	Node::SetTranslation(this->position.x,this->position.y,this->position.z);
}

void Entity::Pitch(float amount)
{
	this->rotation.x += DEGTORAD(amount);
	this->Rotate(DEGTORAD(amount),0,0);
}

void Entity::Yaw(float amount)
{
	this->rotation.y += DEGTORAD(amount);
	this->Rotate(0,DEGTORAD(amount),0);
}

void Entity::Roll(float amount)
{
	this->rotation.z += DEGTORAD(amount);
	this->Rotate(0,0,DEGTORAD(amount));
}

void Entity::MoveForward(float amount)
{
	float x = sinf(this->GetRotation().y) * amount;
	float y = sinf(this->GetRotation().x) * amount;
	float z = cosf(this->GetRotation().y*this->GetRotation().x) * amount;

	this->position.x += x;
	this->position.y += y;
	this->position.z += z;
	this->Translate(x,y,z);
}

void Entity::Strafe(float amount)
{
	//float sx = sinf(this->GetRotation()->x);
	//float cx = cosf(this->GetRotation()->x);
	//float sy = sinf(this->GetRotation()->y*2 + DEGTORAD(90));
	//float cy = cosf(this->GetRotation()->y*2 + DEGTORAD(90));

	//float x = (sy*cx)*amount;
	//float z = (cy*cx)*amount;

	//this->position->x += x;
	//this->position->z += -z;
	//this->position->x += amount;
	//this->oldPosition->x = this->position->x;
	//this->oldPosition->y = this->position->y;
	//this->oldPosition->z = this->position->z;

	this->position.z += amount * cosf(this->GetRotation().y + DEGTORAD(90));
	this->position.x += amount * sinf(this->GetRotation().y + DEGTORAD(90));
}