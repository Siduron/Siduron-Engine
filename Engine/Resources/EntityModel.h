#ifndef ENTITYMODEL_H
#define ENTITYMODEL_H

#include "Entity.h"
#include "Model.h"

class EntityModel : public Entity
{
	public:
		EntityModel();
		void Render();
		void Update();
		void SetScale(Vector* scale);
		void SetScale(float x, float y, float z);
		void SetModel(const std::string modelPath, const std::string modelName);
		void SetShader(std::string path);
		void Scale(float amount);
		void Scale(float x, float y, float z);

		Vector* GetScale();
		Model* GetModel();

	private:
		Model* model;
		Vector* scale;
};

#endif