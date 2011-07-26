#include "World.h"
#include "Core/Kernel.h"

World::World()
{
	Camera* camera = Kernel::Instance()->GetRenderer()->GetCamera();
	Kernel::Instance()->GetScene()->Add(camera);
	
	camera->Pitch(90);
}

void World::Add(GameObject* gameObject)
{
	Kernel::Instance()->GetScene()->Add(gameObject->GetEntity());
}

void World::CreateTerrain(int size)
{
	Terrain* terrain = new Terrain();
	terrain->Create(size);
	this->terrain = terrain;
	terrain->EnableDebug(false);
	Kernel::Instance()->GetScene()->Add(terrain);
	std::vector<int> terrainCenter = terrain->GetQuadtree()->GetMasterNode()->GetCenter();
	Camera* camera = Kernel::Instance()->GetRenderer()->GetCamera();
	camera->SetPosition(terrainCenter[0],15,terrainCenter[1]);
	Kernel::Instance()->GetScene()->Add(terrain);
	
	for(int a = 0; a < terrain->NumPatchesY(); a++)
	{
		vector<Tile*> tilesHor;
		for(int b = 0; b < terrain->NumPatchesX(); b++)
		{
			Tile* newTile = new Tile(terrain->GetPatchByIndex(a,b));
			tilesHor.push_back(newTile);
		}
		this->tiles.push_back(tilesHor);
	}
	
	//this->tiles[a][b].push_back(terrain->GetPatchByIndex(y, x);
}

Terrain* World::GetTerrain() const
{
	return this->terrain;
}

Tile* World::GetTileByIndex(const unsigned int y, const unsigned int x)
{
	return this->tiles[y][x];
}

const unsigned int World::NumTilesX() const
{
	return this->terrain->NumPatchesX();
}

const unsigned int World::NumTilesY() const
{
	return this->terrain->NumPatchesY();
}