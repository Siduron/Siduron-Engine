#include "Util.h"
#include "../Core/Kernel.h"

vector< vector< float > > Util::BitmapTo2dVector( string filename )
{
	//Load image from file
	HDC lhdcDest;	//Handle to Device Context (Windows GDI)
	HANDLE hbmp;	//Handle to an object (standard handle)
	HINSTANCE* hInst = new HINSTANCE();//Handle to an instance (instance of the window)

	//Create a memory device context compatible with the specified device (NULL)
	lhdcDest = CreateCompatibleDC(NULL);
	if (lhdcDest == NULL)	 
	{		  
		DeleteDC(lhdcDest);	//Delete the DC (prevents a memory leak!)
		//return false;		//Jump out of the function
	}

	//Windows GDI load image of type BMP (fileformat)
	hbmp = LoadImage(*hInst, filename.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (hbmp == NULL)	//Give a visual warning if the loading of the image failed
	{
		char s[100];
		wsprintf(s, "Can't find HeightMask %s", filename);
		MessageBox(NULL, s, "ERROR ERROR ERROR", MB_OK);
		//return false;		//Jump out of the function
	}
	//At this point it is sure that lhdcDest & hbmp are valid.

	//Load the bmp into the device context (memory space)
	SelectObject(lhdcDest, hbmp);

	//The BITMAP structure defines the type, width, height, color format, and bit values of a bitmap
	BITMAP bm;
	//The GetObject function retrieves information for the specified graphics object
	//bm is cast to a "void*" because GetObject function doesn't 'know' it's format 
	//(don't know what it is, but just put it in that buffer)
	GetObject(hbmp, sizeof(BITMAP), (void*)&bm);

	//Store the width and height of the heightmap
	int width = bm.bmWidth;
	int height = bm.bmHeight;

	//Create an array to hold all the heightdata
	BYTE* tempheightData = new BYTE[width*width*3];

	//Iterate through the BMP-file and fill the heightdata-array
	for (int lHeight = 0; lHeight < width; lHeight++)
	{
		for (int lWidth = 0; lWidth < width; lWidth++)
		{
			tempheightData[(lWidth*width*3)+lHeight*3+0] = GetRValue(GetPixel(lhdcDest, lHeight, lWidth));
			tempheightData[(lWidth*width*3)+lHeight*3+1] = GetGValue(GetPixel(lhdcDest, lHeight, lWidth));
			tempheightData[(lWidth*width*3)+lHeight*3+2] = GetBValue(GetPixel(lhdcDest, lHeight, lWidth));
		}
	}


	vector< vector< float > > data;
	for(int a = 0; a < height; a++)
	{
		vector< float > column;
		for(int b = 0; b < width * 3; b++)
		{
			column.push_back( GetRValue( GetPixel( lhdcDest, a, b ) ) );
			column.push_back( GetGValue( GetPixel( lhdcDest, a, b ) ) );
			column.push_back( GetBValue( GetPixel( lhdcDest, a, b ) ) );
		}
		data.push_back( column );
	}
	return data;
}

vector< vector< float > > Util::BitmapToHeightmap( string filename )
{
	vector< vector< float > > data = BitmapTo2dVector( filename );
	vector< vector< float > > height_map;

	for( int a = 0; a < data.size(); a++ )
	{
		vector< float > column;
		for( int b = 0; b < data[ a ].size(); b = b + 3 )
		{
			column.push_back( ( data[ a ][ b ] + data[ a ][ b + 1 ] + data[ a ][ b + 2 ] ) / 3 );
		}
		height_map.push_back( column );
	}

	return height_map;
}
vector< vector< Color > > Util::BitmapToColormap( string filename )
{
	vector< vector< float > > data = Util::BitmapTo2dVector( filename );
	vector< vector< Color > > color_map;

	for(int a = 0; a < data.size(); a++)
	{
		vector< Color > column;
		for(int b = 0; b < data[ a ].size(); b = b + 3)
		{
			Color new_color;
			new_color.r = data[ a ][ b ];
			new_color.g = data[ a ][ b + 1];
			new_color.b = data[ a ][ b + 2 ];
			column.push_back( new_color );
		}
		color_map.push_back( column );
	}
	return color_map;
}
