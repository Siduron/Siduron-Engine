#include "Camera.h"
#include "../Core/DEGTORAD.h"
//
Camera::Camera()
{
	this->lookAt = new Vector(0,0,1);
}

Vector* Camera::GetLookAt()
{
	this->Update();
	return this->lookAt;
}
void Camera::Update()
{
	this->lookAt->x = (sinf(this->rotation.y)*cosf(this->rotation.x)) + this->position.x;
	this->lookAt->y = sinf(-this->rotation.x) + this->position.y;
	this->lookAt->z = (cosf(this->rotation.y)*cosf(this->rotation.x)) + this->position.z;
}

void Camera::Pitch(float amount)
{
	Entity::Pitch(amount);
	if(RADTODEG(this->rotation.x) > 89.0f)
	{
		this->rotation.x = DEGTORAD(89.0f);
	}
	else if(RADTODEG(this->rotation.x) < -89.0f)
	{
		this->rotation.x = DEGTORAD(-89.0f);
	}
}

void Camera::MoveForward(float amount)
{
	this->position.z += amount * cosf(this->GetRotation().y);
	this->position.x += amount * sinf(this->GetRotation().y);
	this->position.y += amount * sinf(-this->GetRotation().x);
}