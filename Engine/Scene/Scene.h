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
#include "Node.h"

#include <map>

class Scene
{
	public:
		Scene();
		bool Init();
		void Add(SceneManagement::Node* node);
		void Render();
		void CreateLoadingScreen();
		Terrain* GetTerrain();
		Camera* GetActiveCamera();
		void SetSkybox( EntityModel* skybox );
		//Skybox* GetSkybox();
		SceneManagement::Node* GetMasterNode();
		Vector* atmosGen;
		float atmosRange;
		~Scene();

	private:
		Terrain* terrain;
		float timer;
		std::vector<Entity*> entities;
		std::vector<Entity*> trees;
		SceneManagement::Node* masterNode;
		int currentRegion;
		Camera* camera;
		int terrainSize;
		EntityModel* skybox;
		Shader* domeshader;
		Texture* domeTexture;

		Entity* generator;
		
};

void Sound(char*name);

#endif