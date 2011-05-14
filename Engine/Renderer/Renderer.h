#ifndef RENDERER_H
#define RENDERER_H

#include <d3d9.h>
#include <d3dx9.h>
#include "../Resources/Vertex.h"
#include <time.h>
#include "../Resources/Camera.h"
#include "../Resources/Vector.h"
#include "../Resources/Shader.h"
#include "../Resources/Texture.h"
#include "../Util/Logger.h"
#include "RenderTarget.h"

// include the Direct3D Library files
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

//#ifdef _DEBUG
//#   pragma comment(lib, "d3dx9d.lib")
//#else
//#   pragma comment(lib, "d3dx9.lib")
//#endif
//#pragma comment(lib, "d3d9.lib")

#if defined(DEBUG)|defined(_DEBUG)
#ifndef D3D_DEBUG_INFO
#define D3D_DEBUG_INFO
#endif
#endif
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1200


class Renderer
{
public:
	Renderer();
	bool InitDirect3D(HWND hWnd);
	void BeginScene();
	void EndScene();
	void Present();
	const D3DXMATRIX& GetWorldMatrix() const;
	const D3DXMATRIX& GetViewMatrix() const;
	const D3DXMATRIX& GetProjectionMatrix() const;
	const LPDIRECT3DDEVICE9& GetDevice() const;
	const LPDIRECT3DTEXTURE9& GetRenderTexture() const;
	const LPDIRECT3DCUBETEXTURE9& GetCubemap() const;
	const RenderTarget* GetRenderTarget() const;
	Shader* GetPostprocessShader();
	Camera* GetCamera();
	void SetCamera(Camera* cam);
	void SetRenderTarget(LPDIRECT3DSURFACE9);
	void EnableFullscreen(bool b);
	void ToggleFullScreen();
	void RenderCubemap();
	void SetRenderTarget(RenderTarget* renderTarget);
	
	~Renderer();
	
private:
	
	LPDIRECT3D9 g_pD3D; // Pointer naar Direct3D interface
	LPDIRECT3DDEVICE9 g_pD3DDevice; // Pointer naar Direct3D device
	LPDIRECT3DVERTEXBUFFER9 t_buffer;
	RenderTarget* backBufferTarget;
	RenderTarget* renderTarget;
	LPDIRECT3DCUBETEXTURE9 cubemap;
	Camera* camera;
	
	D3DXMATRIX matWorld;
	D3DXMATRIX matTranslate;
	D3DXMATRIX matTranslate_rt;
	D3DXMATRIX matScale;
	D3DXMATRIX matRotateX;
	D3DXMATRIX matRotateY;
	D3DXMATRIX matRotateZ;
	
	D3DXMATRIX matView, matViewSave;
	D3DXMATRIX matProj,matProjSave;

	IDirect3DVertexDeclaration9* m_vertexDeclaration;

	LPD3DXEFFECT m_pEffect;              // Effect object for this technique
	D3DXHANDLE m_hTPostProcess;        // PostProcess technique handle
	int m_nRenderTarget;        // Render target channel this PP outputs
	HWND window;
	bool fullscreen;
	
	Shader* postprocess;
	Texture* postprocessTexture1;
	LPDIRECT3DTEXTURE9 testtexture;
};

#endif
