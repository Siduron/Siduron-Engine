#ifndef MATH_H
#define MATH_H
#include <iostream>
#include <math.h>
#include "../Resources/Vector.h"

class Math
{
	public:
		static Math* Inst();
		float Min(float a, float b);
		float Max(float a, float b);
		float LinearInterpolate(float y1,float y2,float mu);
		float BilinearInterpolate(float posX, float posZ, float tlY, float trY,float blY, float brY);
	private:
		static Math* instance;

};
#endif