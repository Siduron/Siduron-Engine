#ifndef VECTOR_H
#define VECTOR_H
#include "../Math/Math.h"

class Vector
{
	public:
	Vector();
	Vector(float xValue,float yValue,float zValue);
	float x, y, z;
	float Proximity(Vector v);
	Vector Add(Vector v);
	private:
		
};
#endif