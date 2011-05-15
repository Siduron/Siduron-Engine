#include "RenderTarget.h"
#include "../Core/Kernel.h" 

RenderTarget::RenderTarget()
{
	this->matProj = matProj;
}

void RenderTarget::Create()
{
	//Render target for backbuffer
	LPDIRECT3DDEVICE9 g_pD3DDevice = Kernel::Instance()->GetRenderer()->GetDevice();
	g_pD3DDevice->CreateTexture(SCREEN_WIDTH,
                                 SCREEN_HEIGHT,
                                 2,
                                 D3DUSAGE_RENDERTARGET,
                                 D3DFMT_A8R8G8B8,
                                 D3DPOOL_DEFAULT,
								 &this->renderTexture,
                                 NULL);
	this->renderTexture->GetSurfaceLevel(0,&this->surface);

	g_pD3DDevice->CreateRenderTarget( SCREEN_WIDTH, SCREEN_HEIGHT, D3DFMT_A8R8G8B8, 
                                  D3DMULTISAMPLE_2_SAMPLES, 0,
                                  false, &this->multisampleSurface, NULL );	
	g_pD3DDevice->StretchRect(this->multisampleSurface, NULL, this->surface, NULL, D3DTEXF_ANISOTROPIC);
	//D3DXLoadSurfaceFromSurface(
	//this->g_pD3DDevice->GetTransform(D3DTS_PROJECTION,&this->matProj);
	//g_pD3DDevice->GetRenderTarget(0,&this->pRenderSurface);
}

const LPDIRECT3DTEXTURE9& RenderTarget::GetRenderTexture() const
{
	return this->renderTexture;
}

const LPDIRECT3DSURFACE9& RenderTarget::GetSurface() const
{
	return this->surface;
}

const D3DXMATRIX& RenderTarget::GetProjectionMatrix() const
{
	return this->matProj;
}

void RenderTarget::SetProjectionMatrix(D3DXMATRIX proj)
{
	this->matProj = proj;
}

void RenderTarget::SetSurface(LPDIRECT3DSURFACE9 surface)
{
	this->surface = surface;
}

void RenderTarget::Release()
{
	this->surface->Release();
	this->renderTexture->Release();
}