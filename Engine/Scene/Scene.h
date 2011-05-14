 #ifndef SCENE_H
#define SCENE_H

#include <d3d9.h>
#include "../Renderer/Renderer.h"
#include "../Resources/Vertex.h"
#include "../Input/InputManager.h"
#include "../Resources/Vector.h"
#include "../Resources/Terrain.h"
#include <vector>
#include "../Resources/Model.h"
#include "../Resources/EntityModel.h"
#include "../Math/Math.h"
#include "../Resources/Skybox.h"
#include "../Resources/Shader.h"
#include "../Resources/Node.h"

#include <map>

class Scene
{
	public:
		Scene();
		~Scene();
		bool Init();
		void Add(Node* node);
		void Render();
		void CreateLoadingScreen();
		Terrain* GetTerrain();
		Camera* GetActiveCamera();
		//Skybox* GetSkybox();
		Node* GetMasterNode();
		Vector* atmosGen;
		float atmosRange;

	private:
		Terrain* terrain;
		float timer;
		std::vector<Entity*> entities;
		std::vector<Entity*> trees;
		Node* masterNode;
		int currentRegion;
		Camera* camera;
		int terrainSize;
		EntityModel* skybox;
		EntityModel* tehCube;
		EntityModel* leftCube;
		Shader* domeshader;
		Texture* domeTexture;

		Entity* generator;
		
};

void Sound(char*name);

#endif