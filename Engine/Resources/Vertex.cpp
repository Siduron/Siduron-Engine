#include "Vertex.h"

Vertex::Vertex(float xValue, float yValue, float zValue, int r, int g, int b, float n_r, float n_g, float n_b, float uValue, float vValue)
{
	this->position = Vector(xValue, yValue, zValue);
	this->u = uValue;
	this->v = vValue;
	
	CUSTOMVERTEX* tempVertex =  new CUSTOMVERTEX();
	tempVertex->X = this->position.x;
	tempVertex->Y = this->position.y;
	tempVertex->Z = this->position.z;
	tempVertex->color = D3DCOLOR_XRGB(r, g, b);
	tempVertex->n_R = n_r;
	tempVertex->n_G = n_g;
	tempVertex->n_B = n_b;
	tempVertex->U = uValue;
	tempVertex->V = vValue;
	this->vertex = tempVertex;
	//this->vertexP = &this->vertex;

}
void Vertex::SetHeight(float value)
{
	this->position.y = value;
	this->vertex->Y = value;
}
CUSTOMVERTEX* Vertex::GetCustomVertex()
{
	return this->vertex;
}
Vector Vertex::GetPosition()
{
	return this->position;
}
const float Vertex::GetHeight()
{
	return this->position.y;
}

float Vertex::GetU()
{
	return this->u;
}
float Vertex::GetV()
{
	return this->v;
}
void Vertex::SetU(float u)
{
	this->u = u;
	this->vertex->U = u;
}
void Vertex::SetV(float v)
{
	this->v = v;
	this->vertex->V = v;
}
void Vertex::SetCustomVertex(CUSTOMVERTEX* v)
{
	this->vertex = v;
}
void Vertex::DeleteCustomVertex()
{
	//delete this->vertexP;
}
Vertex::~Vertex()
{
	delete this->vertex;
}