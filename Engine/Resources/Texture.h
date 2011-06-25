#ifndef TEXTURE_H
#define TEXTURE_H

#include "Resource.h"
#include <d3d9.h>
class Texture : public Resource
{
	friend class ResourceManager;
	public:
		Texture(const std::string path);
		LPDIRECT3DTEXTURE9 GetD3DTexture();
		void Reload();
		std::string GetPath();
		~Texture();
	private:
		LPDIRECT3DTEXTURE9 d3dtexture;
		std::string path;
		void Delete();
};

#endif