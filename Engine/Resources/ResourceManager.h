#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#include "../Resources/Texture.h"
#include "../Resources/Shader.h"
#include "../Resources/Model.h"
#include "../Resources/Resource.h"
#include <map>
#include <string>

//#define CONTENT_FOLDER "../../Content/"
//#define CONTENT_FOLDER "Content/"
class ResourceManager
{
public:
	ResourceManager();
	Texture* GetTexture(std::string path);
	Shader* GetShader(std::string path);
	Model* GetModel(const std::string modelPath, const std::string modelName);
	void ReloadShaders();
	void DeleteTexture(std::string path);
private:
	std::map<std::string, Texture*> textures;
	std::map<std::string, Shader*> shaders;
	std::map<std::string, Model*> models;
	~ResourceManager();
};

#endif