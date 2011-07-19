#include "QuadtreeNode.h"
#include "../Core/DEGTORAD.H"
#include "../Core/Kernel.h"

//Constructor
QuadtreeNode::QuadtreeNode(std::vector<std::vector<Patch*>> p, float minX, float maxX, float minZ, float maxZ, float width, float height, float depth)
{
	this->minX = minX;
	this->maxX = maxX;
	this->minZ = minZ;
	this->maxZ = maxZ;
	this->width = width;
	this->height = height;
	int size = p.size();

	if(p.size() > 1)
	{
		this->hasNodes = true;
		//Topleft Node
		std::vector<std::vector<Patch*>> newPatches;
		for(int a = 0; a < (size/2); a++)
		{
			std::vector<Patch*> newPatchesHor;
			for(int b = 0; b < (size/2); b++)
			{
				newPatchesHor.push_back(p.at(a).at(b));				
			}
			newPatches.push_back(newPatchesHor);
		}

		//Topright Node
		std::vector<std::vector<Patch*>> newPatches2;
		for(int a = 0; a < (size/2); a++)
		{
			std::vector<Patch*> newPatchesHor;
			for(int b = (size/2); b < (size); b++)
			{
				newPatchesHor.push_back(p.at(a).at(b));				
			}
			newPatches2.push_back(newPatchesHor);
		}

		//Bottomleft Node
		std::vector<std::vector<Patch*>> newPatches3;
		for(int a = (size/2); a < (size); a++)
		{
			std::vector<Patch*> newPatchesHor;
			for(int b = 0; b < (size/2); b++)
			{
				newPatchesHor.push_back(p.at(a).at(b));				
			}
			newPatches3.push_back(newPatchesHor);
		}

		//Bottomright Node
		std::vector<std::vector<Patch*>> newPatches4;
		for(int a = (size/2); a < (size); a++)
		{
			std::vector<Patch*> newPatchesHor;
			for(int b = (size/2); b < (size); b++)
			{
				newPatchesHor.push_back(p.at(a).at(b));				
			}
			newPatches4.push_back(newPatchesHor);
		}

		//Node 0 and 1
		QuadtreeNode* newNode0 = new QuadtreeNode(newPatches, minX, maxX-(width/2), minZ, maxZ+(height/2), width/2, height/2, depth+1);
		QuadtreeNode* newNode1 = new QuadtreeNode(newPatches2, minX+(width/2), maxX, minZ, maxZ+(height/2), width/2, height/2, depth+1);
		
		//Node 2 and 3
		QuadtreeNode* newNode2 = new QuadtreeNode(newPatches3, minX, maxX-(width/2), minZ-(height/2), maxZ, width/2, height/2, depth+1);
		QuadtreeNode* newNode3 = new QuadtreeNode(newPatches4, minX+(width/2), maxX, minZ-(height/2), maxZ, width/2, height/2, depth+1);

		this->node0 = newNode0;
		this->node1 = newNode1;
		this->node2 = newNode2;
		this->node3 = newNode3;
	}
	else
	{
		this->hasNodes = false;
		this->patch = p.at(0).at(0);
	}
}
//Render this Node
void QuadtreeNode::Render(Vector cameraPosition)
{
	if(this->hasNodes)
	{
		this->node0->Render(cameraPosition);
		this->node1->Render(cameraPosition);
		this->node2->Render(cameraPosition);
		this->node3->Render(cameraPosition);
	}
	else
	{
		cameraPosition.y = this->GetPatch()->GetCenter().y;
		if(this->patch->GetCenter().Proximity(cameraPosition) < 30.0f)
		{
			Scene* scene = Kernel::Instance()->GetScene();
			//dirty hax
			//float proximity = scene->atmosGen->Proximity(this->patch->GetCenter());
			//if(proximity <= scene->atmosRange)
			//{
			//	//if(proximity >= scene->atmosRange-(scene->atmosRange/3))
			//	//{
			//	//	this->patch->atmosphere = 1.0-((proximity / scene->atmosRange)/3);
			//	//}
			//	//else
			//	//{
			//		this->patch->atmosphere = 1.0;
			//	//}
			//}
			//else
			//{
			//	this->patch->atmosphere = 0.0;
			//}
			this->patch->Render();
		}
	}
}

std::vector<std::vector<QuadtreeNode*>> QuadtreeNode::GetNode()
{
	return this->nodes;
}

Vector QuadtreeNode::Collide(Vector vec)
{
	if(this->hasNodes)
	{
		if(vec.x >= this->node0->minX && vec.x <= this->node0->maxX && vec.z <= this->node0->minZ && vec.z >= this->node0->maxZ)
		{
			this->node0->Collide(vec);
		}
		else if(vec.x >= this->node1->minX && vec.x <= this->node1->maxX && vec.z <= this->node1->minZ && vec.z >= this->node1->maxZ)
		{
			this->node1->Collide(vec);
		}
		else if(vec.x >= this->node2->minX && vec.x <= this->node2->maxX && vec.z <= this->node2->minZ && vec.z >= this->node2->maxZ)
		{
			this->node2->Collide(vec);
		}
		else if(vec.x >= this->node3->minX && vec.x <= this->node3->maxX && vec.z <= this->node3->minZ && vec.z >= this->node3->maxZ)
		{
			this->node3->Collide(vec);
		}
		else
		{
			return vec;
		}
	}
	else
	{
		std::vector<Vertex*> vertices = this->patch->GetVertices();
		Vector Topleft = Vector(0,0,0);
		Vector Topright = Vector(128,0,0);
		Vector Bottomleft = Vector(0,0,-128);
		Vector Bottomright = Vector(128,0,-128);
		for(int i = 0; i < vertices.size(); i++)
		{
			if(vertices.at(i)->GetPosition().x > Topleft.x && 
			   vertices.at(i)->GetPosition().x <= vec.x &&
			   vertices.at(i)->GetPosition().z <= Topleft.z &&
			   vertices.at(i)->GetPosition().z > vec.z)
			{
				Topleft = vertices.at(i)->GetPosition();
			}

			if(vertices.at(i)->GetPosition().x <= Topright.x && 
			   vertices.at(i)->GetPosition().x > vec.x &&
			   vertices.at(i)->GetPosition().z <= Topright.z &&
			   vertices.at(i)->GetPosition().z > vec.z)
			{
				Topright = vertices.at(i)->GetPosition();
			}

			if(vertices.at(i)->GetPosition().x > Bottomleft.x && 
			   vertices.at(i)->GetPosition().x <= vec.x &&
			   vertices.at(i)->GetPosition().z > Bottomleft.z &&
			   vertices.at(i)->GetPosition().z <= vec.z)
			{
				Bottomleft = vertices.at(i)->GetPosition();
			}

			if(vertices.at(i)->GetPosition().x <= Bottomright.x && 
			   vertices.at(i)->GetPosition().x > vec.x &&
			   vertices.at(i)->GetPosition().z > Bottomright.z &&
			   vertices.at(i)->GetPosition().z <= vec.z)
			{
				Bottomright = vertices.at(i)->GetPosition();
			}
		}
	
		float minX = Topleft.x; //0%
		float maxX = Topright.x; //100%
		float percentX = (((vec.x-minX)/(maxX-minX)))*100; 
		
		float minZ = Topright.z; //0%
		float maxZ = Bottomright.z; //100%
		float percentZ = (((vec.z-minZ)/(maxZ-minZ)))*100; 

		float HeightTL = Topleft.y;
		float HeightTR = Topright.y;
		float HeightBL = Bottomleft.y;
		float HeightBR = Bottomright.y;
		
		float heightTLTR = Math::Inst()->LinearInterpolate(HeightTL,HeightTR,percentX/100);
		float heightBLBR = Math::Inst()->LinearInterpolate(HeightBL,HeightBR,percentX/100);
		float Xlerp = Math::Inst()->LinearInterpolate(heightTLTR,heightBLBR,percentZ/100);
		float heightTLBL = Math::Inst()->LinearInterpolate(HeightTL,HeightBL,percentZ/100);
		float heightTRBR = Math::Inst()->LinearInterpolate(HeightTR,HeightBR,percentZ/100);
		float Zlerp = Math::Inst()->LinearInterpolate(heightTLBL,heightTRBR,percentX/100);
		float final = (Xlerp + Zlerp)/2;
		Vector newPosition = Vector(vec.x,final,vec.z);
		Vector v1 = vec;
		Vector v2 = newPosition;
		
		return newPosition;
	}
}	

//Calculate the level of detail to be used.
void QuadtreeNode::CalcLod(Vector cameraPosition)
{
	if(this->hasNodes)
	{
		this->node0->CalcLod(cameraPosition);
		this->node1->CalcLod(cameraPosition);
		this->node2->CalcLod(cameraPosition);
		this->node3->CalcLod(cameraPosition);
	}
	else
	{
		Vector center = this->patch->GetCenter();
		float proximity = center.Proximity(cameraPosition);
		if(proximity < 40.0f)
		{
			if(proximity < 10)
			{
				if(proximity < 6)
				{
					this->patch->SetLod(HIGH); //HIGH
				}
				else
				{
					this->patch->SetLod(MEDIUM); //MEDIUM
				}
			}
			else
			{
				this->patch->SetLod(LOW); //LOW
			}
		}
	}
}
//Compare a position with the boundaries of this node, and return the node.
QuadtreeNode* QuadtreeNode::CurrentNode(Vector vec)
{
	QuadtreeNode* tempNode;	
	if(this->hasNodes)
	{
		if(vec.x >= this->node0->minX && vec.x <= this->node0->maxX && vec.z <= this->node0->minZ && vec.z >= this->node0->maxZ)
		{
			tempNode = this->node0->CurrentNode(vec);
		}
		else if(vec.x >= this->node1->minX && vec.x <= this->node1->maxX && vec.z <= this->node1->minZ && vec.z >= this->node1->maxZ)
		{
			tempNode = this->node1->CurrentNode(vec);
		}
		else if(vec.x >= this->node2->minX && vec.x <= this->node2->maxX && vec.z <= this->node2->minZ && vec.z >= this->node2->maxZ)
		{
			tempNode = this->node2->CurrentNode(vec);
		}
		else if(vec.x >= this->node3->minX && vec.x <= this->node3->maxX && vec.z <= this->node3->minZ && vec.z >= this->node3->maxZ)
		{
			tempNode = this->node3->CurrentNode(vec);
		}
	}
	else
	{
		tempNode = this;
		return tempNode;
	}
}

//Return the patch of this node.
Patch* QuadtreeNode::GetPatch()
{
	return this->patch;
}

std::vector<int> QuadtreeNode::GetCenter()
{
	std::vector<int> center;
	int xCenter = (this->minX+this->maxX)/2;
	int zCenter = (this->minZ+this->maxZ)/2;
	center.push_back(xCenter);
	center.push_back(zCenter);
	return center;
}