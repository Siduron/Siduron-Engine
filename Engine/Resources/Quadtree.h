#ifndef QUADTREE_H
#define QUADTREE_H
#include "Patch.h"
#include "QuadtreeNode.h"
class Quadtree
{
public:
	Quadtree(std::vector<std::vector<Patch*>> p, float minX, float maxX, float minZ, float maxZ, float width, float height);
	void Render();
	QuadtreeNode* GetMasterNode();
private:
	QuadtreeNode* masterNode;
};

#endif