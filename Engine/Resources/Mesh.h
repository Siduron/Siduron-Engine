#ifndef MESH_H
#define MESH_H

#include <d3d9.h>
#include "../Renderer/Renderer.h"
#include "Texture.h"
#include "Shader.h"
#include <assimp.hpp>      // C++ importer interface
#include <aiScene.h>       // Output data structure
#include <aiPostProcess.h> // Post processing flags
#include <vector>

class Mesh
{
	friend class Model;
	public:
		Mesh(aiMesh* m, Texture* t);
		void SetShader(std::string path);
		Shader* GetShader();

	private:
		aiMesh* mesh;
		LPDIRECT3DDEVICE9 g_pD3DDevice;
		LPDIRECT3DVERTEXBUFFER9 vertexBuffer;
		LPDIRECT3DINDEXBUFFER9 indexBuffer;
		std::vector<Vertex*> verts;
		unsigned int faceAmount;
		Texture* texture;
		Shader* shader;
};

#endif