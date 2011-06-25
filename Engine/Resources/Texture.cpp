#include "Texture.h"
#include "../Core/Kernel.h"

Texture::Texture(const std::string path)
{
	this->d3dtexture = NULL;
	this->path = path;
	HRESULT hr = D3DXCreateTextureFromFile(Kernel::Instance()->GetRenderer()->GetDevice(), path.c_str(), &this->d3dtexture); //Load texture from file
	if(hr != D3D_OK)
	{
		Logger::Instance()->Log("Failed to load texture: " + path, Error);
		HRESULT hr = D3DXCreateTextureFromFile(Kernel::Instance()->GetRenderer()->GetDevice(), std::string("Content/Textures/errortexture.bmp").c_str(), &this->d3dtexture);
	}
}

LPDIRECT3DTEXTURE9 Texture::GetD3DTexture()
{
	return this->d3dtexture;
}

void Texture::Delete()
{
	this->d3dtexture->Release();
	this->d3dtexture = 0;
	delete this->d3dtexture;
}

void Texture::Reload()
{

}

std::string Texture::GetPath()
{
	return this->path;
}

Texture::~Texture()
{
	this->Delete();
}