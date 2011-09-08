#ifndef TERRAIN_H
#define TERRAIN_H

#include "../Renderer/Renderer.h"
#include "../Util/Logger.h"
#include <vector>
#include "../Scene/Node.h"
#include "Patch.h"

using namespace std;

struct TextureSet
{
	Texture* Texture1;
	Texture* Texture2;
	Texture* Texture3;
	Texture* Texture4;
	Texture* alt_Texture1;
	Texture* debug;
};

class Terrain : public SceneManagement::Node
{
	public:
		Terrain();
		bool Create( unsigned int size );
		void Render();
		bool LoadBMP( string argFileName );
		void CreateNoise();
		Vector Collide( Vector position );

		~Terrain();

	private:
		LPDIRECT3DVERTEXBUFFER9 vertex_buffer;
		unsigned long vertex_buffer_size;
		LPDIRECT3DINDEXBUFFER9 index_buffer;
		unsigned long index_buffer_size;
		vector< vector < Vertex* > > vertices;
		//vector< Patch* > patches;
		float hmap[250][250];
		TextureSet currentSet;
		TextureSet greenWorld;
		Texture* texture_map;
		Texture* texture_normal;
		Shader* terrain_shader;
		int size;
		D3DXMATRIX *matWorldInverseTransponse, *matWorldInverse, *worldViewProj;
		
};
#endif