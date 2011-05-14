#include "World.h"
#include "Core/Kernel.h"

World::World()
{

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
	Kernel::Instance()->GetScene()->Add(terrain);
}

Terrain* World::GetTerrain() const
{
	return this->terrain;
}