#include "Math.h"

Math* Math::instance = NULL;

Math* Math::Inst()
{
	if(instance == NULL)
	{
		instance = new Math();
	}
	return instance;
}

float Math::Min(float a, float b)
{
	if(a < b) return a;
	if(b < a) return b;
	if(a == b) return a;
}

float Math::Max(float a, float b)
{
	if(a > b) return a;
	if(b > a) return b;
	if(a == b) return a;
}

float Math::LinearInterpolate(float y1,float y2,float mu)
{
   return(y1*(1-mu)+y2*mu);
}

float Math::BilinearInterpolate(float posX, float posZ, float tlY, float trY,float blY, float brY)
{
	//Player position
	int Xa = posX;
	int Xb = posX+1;

	int Za = posZ;
	int Zb = posZ+1;

	//Vertex Heights
	/*float HTL = fl.getMapY(Xa, Za);
	float HTR = fl.getMapY(Xb, Za);
	float HBL = fl.getMapY(Xa, Zb);
	float HBR = fl.getMapY(Xb, Zb);*/

	float posX_Xa = (posX - Xa);
	float Xb_Xa = (Xb - Xa);
	float dx;
	if(Xb_Xa != 0)
	{
		dx =  posX_Xa / Xb_Xa ;
	}
	else
	{
		dx = posX_Xa;
	}

	float posZ_Za = (posZ - Za);
	float Zb_Za = (Zb - Za);
    float dz;
	if(Zb_Za != 0)
	{
		dz =  posZ_Za / Zb_Za ;
	}
	else
	{
		dz =  posZ_Za;
	}
	
	//Linear Interpolating
	float lerpT = tlY + dx * (trY - tlY);
	float lerpB = blY + dx * (brY - blY); 
	float lerp  = lerpT + dz * (lerpB - lerpT);
	//std::cout << lerp << "\n";
	return lerp;
}