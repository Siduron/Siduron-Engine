#include "Vector.h"

Vector::Vector( float xValue, float yValue, float zValue )
{
	this->x = xValue;
	this->y = yValue;
	this->z = zValue;
}
Vector::Vector()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}
float Vector::Proximity( Vector v )
{
	return sqrt( pow( ( v.x - this->x ), 2 ) + pow( ( v.y - this->y ), 2 ) + pow( ( v.z - this->z ), 2 ) );
}

Vector Vector::Add( Vector v )
{
	Vector newVector = Vector( this->x + v.x, this->y + v.y, this->z + v.z );
	return newVector;
}

Vector Vector::Subtract( Vector v )
{
	Vector newVector = Vector(this->x - v.x, this->y - v.y, this->z - v.z);
	return newVector;
}