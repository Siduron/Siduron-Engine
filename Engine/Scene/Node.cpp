#include "Node.h"

namespace SceneManagement
{
	Node::Node()
	{
		D3DXMatrixTranslation( &this->matTranslate,0,0,0 );
		D3DXMatrixTranslation( &this->matTranslate_Relative,0,0,0 );
		D3DXMatrixRotationX( &this->matRotateX, 0 );        // Pitch
		D3DXMatrixRotationY( &this->matRotateY, 0 );        // Yaw
		D3DXMatrixRotationZ( &this->matRotateZ, 0 );        // Roll
		D3DXMatrixScaling( &this->matScale,1,1,1 );
		
		this->hasParent = false;
		this->hasChildren = false;
	}

	void Node::Render()
	{
		for(int i = 0; i < this->childNodes.size(); i++)
		{
			this->childNodes.at(i)->Render();
		}
	}

	void Node::Update()
	{
		//if(this->hasParent)
		//{
			/*float newX = this->matTranslate._41-this->parent->GetTranslationMatrix()._41;
			float newY = this->matTranslate._42-this->parent->GetTranslationMatrix()._42;
			float newZ = this->matTranslate._43-this->parent->GetTranslationMatrix()._43;
			D3DXMATRIX relativeTranslation;
			D3DXMatrixTranslation(&relativeTranslation, newX, newY, newZ);
			this->matWorld = ((this->matRotateZ * this->matRotateX * this->matRotateY) * this->matScale * relativeTranslation);*/
			//D3DXMATRIX parentWorld = this->parent->GetWorldMatrix();
 			//this->matWorld *= parentWorld;
		//}
		//else
		//{
			this->matWorld = ((this->matRotateZ * this->matRotateX * this->matRotateY) * this->matScale * this->matTranslate);
		//}
		for(int i = 0; i < this->childNodes.size(); i++)
		{
			this->childNodes.at(i)->Update();
		}
	}

	void Node::AddChildNode(Node* node)
	{
		node->parent = this;
		node->hasParent = true;
		this->hasChildren = true;
		this->childNodes.push_back(node);
	}

	void Node::Translate(float x, float y, float z)
	{
		D3DXMATRIX translation;
		D3DXMatrixTranslation(&translation, x, y, z);
		this->matTranslate *= translation;
	}

	void Node::SetTranslation(float x, float y, float z)
	{
		D3DXMatrixTranslation(&this->matTranslate, x, y, z);
	}

	void Node::Rotate(float x, float y, float z)
	{
		D3DXMATRIX rotationX;
		D3DXMATRIX rotationY;
		D3DXMATRIX rotationZ;

		D3DXMatrixRotationX( &rotationX, x );        // Pitch
		D3DXMatrixRotationY( &rotationY, y );        // Yaw
		D3DXMatrixRotationZ( &rotationZ, z );        // Roll

		this->matRotateX *= rotationX;
		this->matRotateY *= rotationY;
		this->matRotateZ *= rotationZ;
	}

	void Node::SetRotation(float x, float y, float z)
	{
		D3DXMatrixRotationX( &this->matRotateX, x );        // Pitch
		D3DXMatrixRotationY( &this->matRotateY, y );        // Yaw
		D3DXMatrixRotationZ( &this->matRotateZ, z );        // Roll
	}

	void Node::SetScale(float x, float y, float z)
	{
		D3DXMatrixScaling( &this->matScale, x, y, z);        // Pitch
	}

	std::vector<Node*> Node::GetChildNodes()
	{
		return this->childNodes;
	}

	//Return this node's rotation matrix.
	D3DXMATRIX Node::GetRotationMatrix()
	{
		return this->matRotation;
	}

	//Return this node's rotation X matrix.
	D3DXMATRIX Node::GetRotationMatrixX()
	{
		return this->matRotateX;
	}

	//Return this node's rotation Y matrix.
	D3DXMATRIX Node::GetRotationMatrixY()
	{
		return this->matRotateY;
	}

	//Return this node's rotation Z matrix.
	D3DXMATRIX Node::GetRotationMatrixZ()
	{
		return this->matRotateZ;
	}

	//Return this node's translation matrix.
	D3DXMATRIX Node::GetTranslationMatrix()
	{
		return this->matTranslate;
	}

	//Return this node's scaling matrix.
	D3DXMATRIX Node::GetScalingMatrix()
	{
		return this->matScale;
	}

	//Return this node's world matrix.
	D3DXMATRIX Node::GetWorldMatrix()
	{
		return this->matWorld;
	}
}