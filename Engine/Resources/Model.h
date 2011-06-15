#ifndef MODEL_H
#define MODEL_H

#include "Shader.h"
#include "Mesh.h"
#include "../Renderer/Renderer.h"
#include <d3d9.h>
#include <assimp.hpp>      // C++ importer interface
#include <aiScene.h>       // Output data structure
#include <aiPostProcess.h> // Post processing flags
#include <vector>

class Model : public Resource
{
	friend class ResourceManager;
	public:
		Model(const std::string modelPath, const std::string modelName);
		void Render(D3DXMATRIX);
		std::vector<Mesh*> GetMeshes();
		void SetShader(std::string path);
		Shader* GetShader();
		static void CreateBox();
		void Reload();
		~Model();
	private:
		const aiScene* scene;
		LPDIRECT3DDEVICE9 g_pD3DDevice;
		LPDIRECT3DVERTEXBUFFER9 vertexBuffer;
		LPDIRECT3DINDEXBUFFER9 indexBuffer;
		std::vector<Mesh*> meshes;
		
		unsigned int faceAmount;
		unsigned int vertexAmount;

		void Delete();
};

#endif