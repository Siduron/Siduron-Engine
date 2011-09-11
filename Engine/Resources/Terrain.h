#ifndef TERRAIN_H
#define TERRAIN_H

#include "../Renderer/Renderer.h"
#include "../Util/Logger.h"
#include <vector>
#include "../Scene/Node.h"
#include "Patch.h"
#include "../Util/Util.h"

using namespace std;

struct TextureSet
{
	Texture* Texture1;
	Texture* Texture2;
	Texture* Texture3;
	Texture* Texture4;
	Texture* water;
	Texture* water1;
	Texture* alt_Texture1;
	Texture* debug;
};

class Terrain : public SceneManagement::Node
{
	public:
		Terrain();
		bool Create( unsigned int size );
		void Render();
		void CreateNoise();
		Shader* GetTerrainShader();
		Vector Collide( Vector position );

		~Terrain();

	private:
		LPDIRECT3DVERTEXBUFFER9 CreateVertexBuffer( vector< vector< Vertex* > > vertices, int terrain_size );
		LPDIRECT3DVERTEXBUFFER9 vertex_buffer_terrain;
		LPDIRECT3DVERTEXBUFFER9 vertex_buffer_water;
		LPDIRECT3DINDEXBUFFER9 index_buffer;
		unsigned long vertex_buffer_terrain_size;
		unsigned long index_buffer_size;
		vector< vector < Vertex* > > vertices;
		vector< vector< float > > heightmap;
		vector< vector< Color > > color_map;
		vector< vector< Color > > normal_map;
		TextureSet currentSet;
		TextureSet greenWorld;
		Shader* terrain_shader;
		Shader* water_shader;
		int size;
		D3DXMATRIX *matWorldInverseTransponse, *matWorldInverse, *worldViewProj;
		
};
#endif