#ifndef CAMERA_H
#define CAMERA_H
#include "Entity.h"

class Camera : public Entity
{
	public:
		void MoveForward(float amount);
		Camera();
		Vector* GetLookAt();
		void Update();
		void Pitch(float amount);

	private:
		  Vector* lookAt;
};

#endif