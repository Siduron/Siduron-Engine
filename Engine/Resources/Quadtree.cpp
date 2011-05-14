#include "Quadtree.h"

Quadtree::Quadtree(std::vector<std::vector<Patch*>> p, float minX, float maxX, float minZ, float maxZ, float width, float height)
{
	this->masterNode = new QuadtreeNode(p, minX, maxX, minZ, maxZ, width, height, 0);
}

void Quadtree::Render()
{
	//this->masterNode->Render();
}

QuadtreeNode* Quadtree::GetMasterNode()
{
	return this->masterNode;
}