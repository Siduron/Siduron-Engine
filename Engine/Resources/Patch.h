#ifndef PATCH_H
#define PATCH_H

#include "../Renderer/Renderer.h"
#include "Shader.h"
#include "Texture.h"
#include <vector>
#include <map>

enum DETAILLEVEL
{
	LOW,
	MEDIUM,
	HIGH
};
class Patch
{
	friend class Terrain;
	public:
		Patch(Renderer* r);
		void Create(std::vector<Vertex*> v);
		void Render();
		void ToggleWireframe();
		void SetNeighbours(std::map<std::string, Patch*> n);
		void SetLod(DETAILLEVEL lod);
		void SetShader(Shader* s);
		const std::map<std::string, Patch*>& GetNeighbours() const;
		Vector GetCenter() const;
		const DETAILLEVEL& GetLod() const;
		const std::vector<Vertex*>& GetVertices() const;
		float atmosphere;
	protected:
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

		Texture* texture_map;
		Texture* texture_detail1;
		Texture* texture_detail1_alternate;
		Texture* texture_detail2;
		Texture* texture_lava;
		Texture* texture_alphamap_detail1;
		Texture* texture_alphamap_detail2;
		Texture* texture_normal;
	
		Patch* left;
		Patch* right;
		Patch* up;
		Patch* down;
		
		//Terrain Matrices
		//D3DXMATRIX matWorld, matTranslate, matScale, matRotateX, matRotateY, matRotateZ;
		D3DXMATRIX *matWorldInverseTransponse, *matWorldInverse, *worldViewProj;
	private:
		Vector position;
		Vector rotation;
		Vector scale;

		Renderer* renderer;
		LPDIRECT3DDEVICE9 g_pD3DDevice;
		LPDIRECT3DVERTEXBUFFER9 t_buffer;
		std::vector<Vertex*> vertices;
		CUSTOMVERTEX Vertices[25];
		std::map<std::string, Patch*> neighbours;
		DETAILLEVEL lod;
	
		bool wireframe;
		Vector center; //The position of the center of this patch, used for level of detail
		Shader* shader;
};

#endif