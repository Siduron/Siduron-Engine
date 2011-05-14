#ifndef graphtest_h
#define graphtest_h
#include "../Resources/EntityModel.h"
#include "../Resources/Terrain.h"
class ScenegraphTest
{
	public: 
		ScenegraphTest();
		void Run();
	private:
	EntityModel* middleCube;
	//Terrain* terrain;
};
#endif