#ifndef RENDERTARGET_H
#define RENDERTARGET_H

#include <d3d9.h>
#include <d3dx9.h>

class RenderTarget
{
public:
	RenderTarget();
	void Create();
	const LPDIRECT3DTEXTURE9& GetRenderTexture() const;
	const LPDIRECT3DSURFACE9& GetSurface() const;
	const D3DXMATRIX& GetProjectionMatrix() const;
	void SetProjectionMatrix(D3DXMATRIX proj);
	void SetSurface(LPDIRECT3DSURFACE9 surface);
	void Release();

private:
	LPDIRECT3DTEXTURE9 pRenderTexture;
	LPDIRECT3DSURFACE9 pRenderSurface;
	D3DXMATRIX matProj;
};

#endif