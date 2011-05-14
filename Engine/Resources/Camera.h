#ifndef CAMERA_H
#define CAMERA_H

#include "Entity.h"
//#include "Vector.h"
//#include <d3d9.h>
//#include <d3dx9.h>

class Camera : public Entity
{
	public:
		void MoveForward(float amount);
		Camera();
		//~Camera();
		//Vector* GetPosition();
		//Vector* GetOldPosition();
		//void SetPosition(Vector* pos);
		//void SetPosition(float x,float y, float z);
		//Vector* GetRotation();
		//float GetPitch();
		//float GetYaw();
		//float GetRoll();
		Vector* GetLookAt();
		void Update();
		void Pitch(float amount);
		//void Yaw(float amount);
		//void Roll(float amount);
		//void MoveForward(float amount);
		//void StrafeCamera(float amount);

	private:
		//Vector* position;
		//Vector* oldPosition;
		//Vector* rotation;
		  Vector* lookAt;
};

#endif