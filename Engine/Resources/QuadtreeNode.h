#ifndef QUADTREENODE_H
#define QUADTREENODE_H
#include "Patch.h"

class QuadtreeNode
{
	friend class QuadtreeNode;
	public:
		QuadtreeNode(std::vector<std::vector<Patch*>> p, float minX, float maxX, float minZ, float maxZ, float width, float height, float depth);
		void Render(Vector cameraPosition);
		std::vector<std::vector<QuadtreeNode*>> GetNode();
		Vector Collide(Vector vec);
		void CalcLod();
		QuadtreeNode* CurrentNode(Vector vec);
		Patch* GetPatch();
		std::vector<int> GetCenter();

	protected:
		std::vector<std::vector<QuadtreeNode*>> nodes; //vector<vertical><horizontal>
		QuadtreeNode* node0;
		QuadtreeNode* node1;
		QuadtreeNode* node2;
		QuadtreeNode* node3;
		std::vector<std::vector<Patch*>> patches; //vector<vertical><horizontal>
		Patch* patch;
		float minX, maxX, minZ, maxZ;
		float width, height;

	private:
		bool hasNodes;

};

#endif