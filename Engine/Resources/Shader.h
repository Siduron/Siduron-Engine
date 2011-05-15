#ifndef SHADER_H
#define SHADER_H

#include "Resource.h"
#include <d3dx9.h>

class Shader : public Resource
{
	friend class ResourceManager;
	public:
		Shader(const std::string path);
		void SetFloat(std::string param, float value);
		LPD3DXEFFECT GetD3DEffect();
		void Reload();
		~Shader();
	private:
		LPD3DXEFFECT effect;
		void Create(const std::string path);
		void Delete();
};

#endif