#include "Shader.h"
#include "../Core/Kernel.h"

Shader::Shader(const std::string path)
{
	this->path = path;
	this->Create(path);
}

void Shader::SetFloat(std::string param, float value)
{
	this->effect->SetFloat( param.c_str(), value);
}

LPD3DXEFFECT Shader::GetD3DEffect()
{
	return this->effect;
}

void Shader::Create(const std::string path)
{
	DWORD dwShaderFlags = D3DXFX_NOT_CLONEABLE; 
	LPD3DXBUFFER pBufferErrors;
	HRESULT hr = D3DXCreateEffectFromFile( Kernel::Instance()->GetRenderer()->GetDevice(), path.c_str(), NULL, NULL, dwShaderFlags, NULL, &this->effect, &pBufferErrors ); 
	if(hr == E_FAIL)Logger::Instance()->Log("Failed to load shader: " + path + "\n" + (const char *)pBufferErrors->GetBufferPointer(), Error);
}

void Shader::Delete()
{
	if(this->effect != NULL)
	{
		this->effect->Release();
		this->effect = 0;
		delete this->effect;
	}
}

void Shader::Reload()
{
	this->Delete();
	this->Create(this->path);
}

Shader::~Shader()
{
	this->Delete();
}