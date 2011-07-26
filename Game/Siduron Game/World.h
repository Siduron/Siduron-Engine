#ifndef WORLD_H
#define WORLD_H
#include "GameObject.h"
#include "Resources/Terrain.h"
#include "Tile.h"
#include <vector>

using namespace std;

class World
{
	public:
		World();
		void Add(GameObject* gameObject);
		void CreateTerrain(int size);
		Terrain* GetTerrain() const;
		Tile* GetTileByIndex(const unsigned int y, const unsigned int x);
		const unsigned int NumTilesX() const;
		const unsigned int NumTilesY() const;

	private:
		Terrain* terrain;
		vector<vector<Tile*>> tiles;
};
#endif
