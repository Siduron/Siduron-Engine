#include "Camera.h"
#include "../Core/DEGTORAD.h"
//
Camera::Camera()
{
//	this->position = new Vector(0,0,0);
//	this->position->x = 0.0f;
//	this->position->y = 0.0f;
//	this->position->z = 0.0f;
//
//	this->oldPosition = new Vector(0,0,0);
//	this->oldPosition->x = 0.0f;
//	this->oldPosition->y = 0.0f;
//	this->oldPosition->z = 0.0f;
//
//	this->rotation = new Vector(0,0,0);
//	this->rotation->x = 0.0f;
//	this->rotation->y = 0.0f;
//	this->rotation->z = 0.0f;
	this->lookAt = new Vector(0,0,1);
}

Vector* Camera::GetLookAt()
{
	this->Update();
	return this->lookAt;
}
void Camera::Update()
{
	//D3DXMatrixRotationX( &this->matRotateX, this->rotation->x );        // Pitch
	//D3DXMatrixRotationY( &this->matRotateY, this->rotation->y );        // Yaw
	//D3DXMatrixRotationZ( &this->matRotateZ, this->rotation->z );        // Roll
	//D3DXMatrixTranslation( &this->matTranslate, this->position->x,this->position->y,this->position->z);
	//this->matWorld = (this->matRotateZ * matRotateX *matRotateY) * this->matTranslate;
	//this->matWorld = this->matTranslate;

	this->lookAt->x = (sinf(this->rotation.y)*cosf(this->rotation.x)) + this->position.x;
	this->lookAt->y = sinf(-this->rotation.x) + this->position.y;
	this->lookAt->z = (cosf(this->rotation.y)*cosf(this->rotation.x)) + this->position.z;
}
//
//Vector* Camera::GetPosition()
//{
//	return this->position;
//}
//
//Vector* Camera::GetOldPosition()
//{
//	return this->oldPosition;
//}
//
//void Camera::SetPosition(Vector* pos)
//{
//	this->oldPosition->x = this->position->x;
//	this->oldPosition->y = this->position->y;
//	this->oldPosition->z = this->position->z;
//
//	this->position->x = pos->x;
//	this->position->y = pos->y;
//	this->position->z = pos->z;
//}
//void Camera::SetPosition(float x,float y, float z)
//{
//	this->oldPosition->x = this->position->x;
//	this->oldPosition->y = this->position->y;
//	this->oldPosition->z = this->position->z;
//
//	this->position->x = x;
//	this->position->y = y;
//	this->position->z = z;
//}
//Vector* Camera::GetRotation()
//{
//	return this->rotation;
//}
//float Camera::GetPitch()
//{
//	return RADTODEG(this->rotation->x);
//}
//
//float Camera::GetYaw()
//{
//	return RADTODEG(this->rotation->y);
//}
//
//float Camera::GetRoll()
//{
//	return RADTODEG(this->rotation->z);
//}
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
//
//void Camera::Yaw(float amount)
//{
//	this->rotation->y += DEGTORAD(amount);
//}
//
//void Camera::Roll(float amount)
//{
//	this->rotation->z += DEGTORAD(amount);
//}
//
void Camera::MoveForward(float amount)
{
	//float sx = sinf(this->GetRotation()->x);
	//float cx = cosf(this->GetRotation()->x);
	//float sy = sinf(this->GetRotation()->y*2);
	//float cy = cosf(this->GetRotation()->y*2);

	//float x =  (sy*cx)*amount;
	//float y = -sx*amount;
	//float z =  (cy*cx)*amount;

	//this->position->x += x;
	//this->position->y += y;
	//this->position->z += z;

	//this->lookAt->x = (sinf(camRot->y)*cosf(camRot->x));
	//this->lookAt->y = sinf(-camRot->x);
	//this->oldPosition->x = this->position->x;
	//this->oldPosition->y = this->position->y;
	//this->oldPosition->z = this->position->z;

	this->position.z += amount * cosf(this->GetRotation().y);
	this->position.x += amount * sinf(this->GetRotation().y);
	this->position.y += amount * sinf(-this->GetRotation().x);
}
//
//
//void Camera::StrafeCamera(float amount)
//{
//	//float sx = sinf(this->GetRotation()->x);
//	//float cx = cosf(this->GetRotation()->x);
//	//float sy = sinf(this->GetRotation()->y*2 + DEGTORAD(90));
//	//float cy = cosf(this->GetRotation()->y*2 + DEGTORAD(90));
//
//	//float x = (sy*cx)*amount;
//	//float z = (cy*cx)*amount;
//
//	//this->position->x += x;
//	//this->position->z += -z;
//	//this->position->x += amount;
//	this->oldPosition->x = this->position->x;
//	this->oldPosition->y = this->position->y;
//	this->oldPosition->z = this->position->z;
//
//	this->position->z += amount * cosf(this->GetRotation()->y + DEGTORAD(90));
//	this->position->x += amount * sinf(this->GetRotation()->y + DEGTORAD(90));
//}