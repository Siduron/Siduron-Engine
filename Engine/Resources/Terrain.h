#ifndef Terrain_H
#define Terrain_H

#include "../Renderer/Renderer.h"
#include "../Util/Logger.h"
#include "Patch.h"
#include "Texture.h"
#include "Shader.h"
#include "Quadtree.h"
#include <vector>
#include "noise/noise.h"
#include "../Scene/Node.h"

class Terrain : public SceneManagement::Node
{
	public:
		Terrain();
		void Create(int mapSize);
		void Render();
		void RenderWater();
		void ToggleWireframe();
		bool LoadBMP(std::string argFileName);
		void SmoothHeightData(int Passes);
		Vector Collide(Vector v);
		Quadtree* GetQuadtree();
		void CreateNoise();
		~Terrain();

	private:
		void CreateIndexbuffers();
		Renderer* renderer;
		LPDIRECT3DDEVICE9 g_pD3DDevice;
		LPDIRECT3DVERTEXBUFFER9 t_buffer;
		LPDIRECT3DVERTEXBUFFER9 waterbuffer;
		
		/*D3DXMATRIX matWorld, matTranslate, matScale, matRotateX, matRotateY, matRotateZ;*/
		D3DXMATRIX *matWorldInverseTransponse, *matWorldInverse, *worldViewProj;

		Vector position;
		Vector rotation;
		Vector scale;

		//std::vector<std::vector<Patch*>> patches; //vector<vertical><horizontal>
		float hmap[530][530];
		std::vector<std::vector<Vertex*>> verts2; //vector<vertical><horizontal>
		Quadtree* quadtree;

		Texture* texture_map;
		Texture* texture_detail1;
		Texture* texture_detail1_alternate;
		Texture* texture_detail2;
		Texture* texture_detail3;
		//Texture* texture_lava;
		//Texture* texture_lightmap;
		//Texture* texture_alphamap_detail1;
		//Texture* texture_alphamap_detail2;
		//Texture* texture_alphamap_lava;	
		Texture* texture_normal;
		Texture* texture_water1;
		Texture* texture_water2;
		//Texture* texture_height;
		Shader* terrainshader;
		Shader* watershader;

		//Indexbuffers
		LPDIRECT3DINDEXBUFFER9 indexbufferHigh;
		LPDIRECT3DINDEXBUFFER9 indexbufferMedium;
		LPDIRECT3DINDEXBUFFER9 indexbufferLow;

		//Restitching indexbuffers
		LPDIRECT3DINDEXBUFFER9 indexbufferMedium_stitchleft;
		LPDIRECT3DINDEXBUFFER9 indexbufferMedium_stitchtopleft;
		LPDIRECT3DINDEXBUFFER9 indexbufferMedium_stitchbottomleft;
		LPDIRECT3DINDEXBUFFER9 indexbufferMedium_stitchtop;
		LPDIRECT3DINDEXBUFFER9 indexbufferMedium_stitchbottom;
		LPDIRECT3DINDEXBUFFER9 indexbufferMedium_stitchright;
		LPDIRECT3DINDEXBUFFER9 indexbufferMedium_stitchtopright;
		LPDIRECT3DINDEXBUFFER9 indexbufferMedium_stitchbottomright;

		LPDIRECT3DINDEXBUFFER9 indexbufferLow_stitchleft;
		LPDIRECT3DINDEXBUFFER9 indexbufferLow_stitchtopleft;
		LPDIRECT3DINDEXBUFFER9 indexbufferLow_stitchbottomleft;
		LPDIRECT3DINDEXBUFFER9 indexbufferLow_stitchtop;
		LPDIRECT3DINDEXBUFFER9 indexbufferLow_stitchbottom;
		LPDIRECT3DINDEXBUFFER9 indexbufferLow_stitchright;
		LPDIRECT3DINDEXBUFFER9 indexbufferLow_stitchtopright;
		LPDIRECT3DINDEXBUFFER9 indexbufferLow_stitchbottomright;
};
#endif