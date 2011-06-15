#ifndef VERTEX_H
#define VERTEX_H

#include <d3d9.h>
#include <D3dx9math.h>
#include "Vector.h"

struct CUSTOMVERTEX
{
	FLOAT X, Y, Z;
	FLOAT R, G, B; // Vertex normal
	FLOAT U, V;
};
#define CUSTOMFVF (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 )

struct CUSTOMVERTEX_UNTRANSFORMED
{
	FLOAT X, Y, Z, RHW;
	FLOAT U, V;
};
#define CUSTOMFVF_UNTRANSFORMED (D3DFVF_XYZRHW | D3DFVF_TEX1 )

class Vertex
{
	public:
		Vertex(float xValue, float yValue, float zValue, float r, float g, float b,float uValue, float vValue);
		void SetHeight(float value);
		CUSTOMVERTEX* GetCustomVertex();
		Vector GetPosition();
		float GetU();
		float GetV();
		void SetU(float u);
		void SetV(float v);
		void SetCustomVertex(CUSTOMVERTEX* v);
		void DeleteCustomVertex();
		~Vertex();
			
	private:
		Vector position;
		DWORD color;
		float u;
		float v;
		CUSTOMVERTEX* vertex;
};

#endif