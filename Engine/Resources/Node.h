#ifndef NODE_H
#define NODE_H
#include <vector>
#include <d3d9.h>
#include <d3dx9.h>

class Node
{
	public:
		Node();
		virtual void Render();
		virtual void Update();
		void AddChildNode(Node*);
		void Translate(float x, float y, float z);
		void SetTranslation(float x, float y, float z);
		void Rotate(float x, float y, float z);
		void SetRotation(float x, float y, float z);
		void SetScale(float x, float y, float z);
		std::vector<Node*> GetChildNodes();
		D3DXMATRIX GetRotationMatrix();
		D3DXMATRIX GetRotationMatrixX();
		D3DXMATRIX GetRotationMatrixY();
		D3DXMATRIX GetRotationMatrixZ();
		D3DXMATRIX GetTranslationMatrix();
		D3DXMATRIX GetScalingMatrix();
		D3DXMATRIX GetWorldMatrix();
		
	protected:
		Node* parent;
		std::vector<Node*> childNodes;
		bool hasParent;
		bool hasChildren;

		D3DXMATRIX matWorld;
		D3DXMATRIX matTranslate;
		D3DXMATRIX matTranslate_Relative;
		D3DXMATRIX matScale;
		D3DXMATRIX matRotateX;
		D3DXMATRIX matRotateY;
		D3DXMATRIX matRotateZ;
		D3DXMATRIX matRotation;
};

#endif