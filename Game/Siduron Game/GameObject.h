#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "Resources/EntityModel.h"
#include "Resources/Model.h"
class GameObject
{
public:
	GameObject();
	void SetModel(std::string modelPath, std::string modelName);
	void SetPosition(int x,int y,int z);
	void SetPosition(Vector pos);
	Vector GetPosition() const;
	EntityModel* GetEntity();
	~GameObject();
private:
	int health;
	EntityModel* entity;

};
#endif