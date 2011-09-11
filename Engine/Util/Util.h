#ifndef UTIL_H
#define UTIL_H
#include <vector>
using namespace std;

struct Color
{
	int r, g, b;
};

class Util
{
	public:
		static vector< vector< float > > BitmapTo2dVector( string filename );
		static vector< vector< float > > BitmapToHeightmap( string filename );
		static vector< vector< Color > > BitmapToColormap( string filename );
};
#endif