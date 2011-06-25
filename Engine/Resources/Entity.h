#ifndef ENTITY_H
#define ENTITY_H
#include "Vector.h"
#include <vector>
#include "../Scene/Node.h"

class Entity : public SceneManagement::Node
{
	public:
		Entity(); //Constructor
		~Entity(); //Destructor
		virtual void Render(); //Renders all the meshes of this entity
		void SetPosition(float x, float y, float z); //Sets the position of the entity
		void SetPosition(Vector pos); //Sets the position of the entity
		void SetRotation(Vector rot);
		void SetRotation(float x,float y, float z);
		void SetPitch(float amount);
		void SetYaw(float amount);	
		void SetRoll(float amount);
		const Vector& GetPosition() const;
		const Vector& GetRotation() const;
		const float& GetPitch() const;
		const float& GetYaw() const;
		const float& GetRoll() const;
		void MoveX(float amount);
		void MoveY(float amount);
		void MoveZ(float amount);
		virtual void Pitch(float amount);
		void Yaw(float amount);
		void Roll(float amount);
		virtual void MoveForward(float amount);
		void Strafe(float amount);

	protected:
		Vector position; //Position of the entity.
		Vector rotation; //Rotation of the entity.
};

#endif