#include "ResourceManager.h"
#include "../Util/Logger.h"

ResourceManager::ResourceManager()
{

}

Texture* ResourceManager::GetTexture(std::string path)
{
	if(this->textures.count(path) < 1)
	{
		Logger::Instance()->Log("Creating Texture: " + path, Info);
		Texture* newtexture = new Texture(path);
		this->textures.insert(std::make_pair(path,newtexture));
		return newtexture;
	}
	else
	{
		this->textures[path]->AddUse();
		return this->textures[path];
	}
}

Shader* ResourceManager::GetShader(std::string path)
{
	if(this->shaders.count(path) < 1)
	{
		Logger::Instance()->Log("Creating Shader: " + path, Info);
		Shader* newshader = new Shader(path);
		this->shaders.insert(std::make_pair(path,newshader));
		return newshader;
	}
	else
	{
		this->shaders[path]->AddUse();
		return this->shaders[path];
	}
}

Model* ResourceManager::GetModel(const std::string modelPath, const std::string modelName)
{
	if(this->models.count(modelPath+modelName) < 1)
	{
		Logger::Instance()->Log("Creating Model: " + modelPath + modelName, Info);
		Model* newmodel = new Model(modelPath, modelName);
		this->models.insert(std::make_pair(modelPath+modelName,newmodel));
		return newmodel;
	}
	else
	{
		this->models[modelPath+modelName]->AddUse();
		return this->models[modelPath+modelName];
	}
}
void ResourceManager::ReloadShaders()
{
	std::map<std::string, Shader*>::iterator p;
	for(p = this->shaders.begin(); p != this->shaders.end(); p++)
	{
		p->second->Reload();
	}
}

void ResourceManager::DeleteTexture(std::string path)
{
	if(this->textures.count(path) > 0)
	{
		this->textures[path]->SubtractUse();
		if(this->textures[path]->GetUses() == 0)
		{
			//this->textures[path]->Delete();
			delete this->textures[path];
			this->textures.erase(path);
			//Logger::Instance()->Log("Deleting texture: "+path, Info);
		}
	}
}

void ResourceManager::DeleteShader(std::string path)
{
	if(this->shaders.count(path) > 0)
	{
		this->shaders[path]->SubtractUse();
		if(this->shaders[path]->GetUses() == 0)
		{
			//this->textures[path]->Delete();
			delete this->shaders[path];
			this->shaders.erase(path);
			//Logger::Instance()->Log("Deleting texture: "+path, Info);
		}
	}
}
void ResourceManager::Flush()
{
	std::map<std::string, Texture*>::iterator currentTexture;
	for(currentTexture = this->textures.begin(); currentTexture != this->textures.end(); currentTexture++)
	{
		//currentTexture->second->~Texture();
		delete currentTexture->second;
	}
	this->textures.clear();

	std::map<std::string, Shader*>::iterator currentShader;
	for(currentShader = this->shaders.begin(); currentShader != this->shaders.end(); currentShader++)
	{
		//currentShader->second->~Shader();
		delete currentShader->second;
	}
	this->shaders.clear();

	std::map<std::string, Model*>::iterator currentModel;
	for(currentModel = this->models.begin(); currentModel != this->models.end(); currentModel++)
	{
		//currentModel->second->~Model();
		delete currentModel->second;
	}
	this->models.clear();
}

ResourceManager::~ResourceManager()
{
	this->Flush();
}