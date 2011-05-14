#ifndef WORLD_H
#define WORLD_H
#include "GameObject.h"
#include "Resources/Terrain.h"

class World
{
	public:
		World();
		void Add(GameObject* gameObject);
		void CreateTerrain(int size);
		Terrain* GetTerrain() const;

	private:
		Terrain* terrain;
};
#endif
