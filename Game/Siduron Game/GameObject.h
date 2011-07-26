#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "Resources/EntityModel.h"
#include "Resources/Model.h"

class GameObject
{
public:
	GameObject();
	void SetModel(std::string modelPath, std::string modelName);
	virtual void SetPosition(int x,int y,int z);
	virtual void SetPosition(Vector pos);
	void SetScale(const float newScale);
	void SetShader(const std::string shader);
	Vector GetPosition() const;
	EntityModel* GetEntity();
	~GameObject();
private:
	int health;
	EntityModel* entity;

};
#endif