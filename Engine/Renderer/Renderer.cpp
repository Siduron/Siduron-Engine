#include "Renderer.h"
#include "../Core/Kernel.h"

Renderer::Renderer()
{
	this->fullscreen = false;
	this->camera = new Camera();
}

bool Renderer::InitDirect3D(HWND hWnd)
{
	this->window = hWnd;
	Logger::Instance()->Log("Creating Direct3D Interface", Info);
	this->g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	
	if(this->g_pD3D == NULL)
	{
		return false;
	}

	D3DDISPLAYMODE d3ddm;

	this->g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm);

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp)); 
	d3dpp.Windowed = !FULLSCREEN; 
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD; 
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
    d3dpp.BackBufferHeight = SCREEN_HEIGHT;
    d3dpp.EnableAutoDepthStencil = TRUE;  
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE; // vsync
	d3dpp.MultiSampleType = D3DMULTISAMPLE_8_SAMPLES;
	LPDIRECT3DSURFACE9 newDepthStencil	= NULL;

	//d3dpp.MultiSampleQuality = 0;
	//DWORD total;
	//if(SUCCEEDED(this->g_pD3D->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT,		  							              D3DDEVTYPE_HAL,
	//								      d3ddm.Format,
	//								      true,
 //                                                    D3DMULTISAMPLE_16_SAMPLES,
	//								      &total)))
	//  {
		//d3dpp.MultiSampleType = D3DMULTISAMPLE_8_SAMPLES;
	//	d3dpp.MultiSampleQuality = total - 1;
	//  }

	Logger::Instance()->Log("Creating Direct3D Device..", Info);
	// Creër Direct3D device
	HRESULT createDevice = this->g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &this->g_pD3DDevice);
	this->g_pD3DDevice->CreateDepthStencilSurface(SCREEN_WIDTH, SCREEN_HEIGHT, d3dpp.AutoDepthStencilFormat, d3dpp.MultiSampleType, d3dpp.MultiSampleQuality, FALSE, &newDepthStencil, NULL );
	this->g_pD3DDevice->SetDepthStencilSurface( newDepthStencil );
	if(createDevice != 0)
		return false;
	//Logger::Instance()->Log("Initializing Direct3D Device..", Info);	
	this->g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	this->g_pD3DDevice->SetRenderState( D3DRS_ZENABLE, D3DZB_TRUE );
	
	this->g_pD3DDevice->SetRenderState( D3DRS_LIGHTING, FALSE );
	this->g_pD3DDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(255, 255, 255));    // ambient light

	//Texture filtering
	//this->g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
	//this->g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC);
	//this->g_pD3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_ANISOTROPIC);

	// Save transformation matrices of the device
    //this->g_pD3DDevice->GetTransform(D3DTS_VIEW,       &this->matViewSave) ;
    //this->g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &this->matProjSave);

	this->backBufferTarget = new RenderTarget();
	this->renderTarget = new RenderTarget();

	D3DXMATRIX tempProj;
	this->g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &tempProj);
	this->backBufferTarget->SetProjectionMatrix(tempProj);
	LPDIRECT3DSURFACE9 tempSurface;
	this->g_pD3DDevice->GetRenderTarget(0,&tempSurface);
	this->backBufferTarget->SetSurface(tempSurface);

	this->renderTarget->Create();
	//Multisampled backbuffer
	this->g_pD3DDevice->CreateRenderTarget( SCREEN_WIDTH, SCREEN_HEIGHT, D3DFMT_A8R8G8B8, 
                                  D3DMULTISAMPLE_8_SAMPLES, 0,
                                  false, &this->multisampleSurface, NULL );	

	//Rendering quad
 //	CUSTOMVERTEX_UNTRANSFORMED Quad[] = {
	//{0.0f,SCREEN_HEIGHT,0.0f,1.0f,0.0f,1.0f},
	//{0.0f,0.0f,0.0f,1.0f,0.0f,0.0f},
	//{SCREEN_WIDTH,SCREEN_HEIGHT,0.0f,1.0f,1.0f,1.0f},
	//{SCREEN_WIDTH,0.0f,0.0f,1.0f,1.0f,0.0f}
	//};

	//HRESULT hr = this->g_pD3DDevice->CreateVertexBuffer(4*sizeof(CUSTOMVERTEX_UNTRANSFORMED),D3DUSAGE_WRITEONLY,CUSTOMFVF_UNTRANSFORMED,D3DPOOL_MANAGED,&this->t_buffer,NULL);
	//VOID* pVoid = NULL;

	//this->t_buffer->Lock(0,3*sizeof(CUSTOMVERTEX_UNTRANSFORMED), &pVoid, 0);    // locks t_buffer, the buffer we made earlier
	//memcpy(pVoid, Quad, sizeof(Quad));    // copy vertices to the vertex buffer
	//this->t_buffer->Unlock();    // unlock t_buffer

	//this->postprocess = Kernel::Instance()->GetResourceManager()->GetShader("Shaders/Postprocess.fx");
	/*HRESULT cube = this->g_pD3DDevice->CreateCubeTexture(256, 1, D3DUSAGE_RENDERTARGET, D3DFMT_R5G6B5,
								D3DPOOL_DEFAULT, &this->cubemap,0);*/

	//D3DXCreateTextureFromFile(this->g_pD3DDevice, "Textures/errortexture.bmp", &this->testtexture);
	//this->postprocessTexture1 = Kernel::Instance()->GetResourceManager()->GetTexture("Textures/Terrain/dust.jpg");

	return true;
}
void Renderer::BeginScene()
{
	//Clear the screen
	D3DCOLOR screenColor = D3DCOLOR_XRGB(0, 0, 0);
	//this->g_pD3DDevice->SetRenderTarget(0,this->renderTarget->GetSurface());
	this->g_pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET, screenColor, 1.0f, 0.0f);
	this->g_pD3DDevice->Clear(0, NULL, D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	this->g_pD3DDevice->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, TRUE);
	this->g_pD3DDevice->BeginScene(); // Begin scene
}
void Renderer::EndScene()
{
	this->g_pD3DDevice->EndScene();
}
void Renderer::Present()
{
	HRESULT rt;
	//rt = this->g_pD3DDevice->StretchRect(this->renderTarget->GetSurface(), NULL, this->multisampleSurface, NULL, D3DTEXF_LINEAR );
	//rt = this->g_pD3DDevice->StretchRect(multisampleSurface, NULL, this->backBufferTarget->GetSurface(), NULL, D3DTEXF_LINEAR );
	//rt = this->g_pD3DDevice->SetRenderTarget(0,this->backBufferTarget->GetSurface());
	//this->g_pD3DDevice->BeginScene();

	//Postprocessing
	//UINT passes;
	//this->postprocess->GetD3DEffect()->Begin(&passes,0);
	//this->postprocess->GetD3DEffect()->BeginPass(0);
	//this->g_pD3DDevice->SetStreamSource(0,this->t_buffer,0,sizeof(CUSTOMVERTEX_UNTRANSFORMED));
	//this->g_pD3DDevice->SetFVF(CUSTOMFVF_UNTRANSFORMED);
	//this->g_pD3DDevice->SetTexture(0,this->renderTarget->GetRenderTexture());
	//this->postprocess->GetD3DEffect()->SetTexture("texture1", this->postprocessTexture1->GetD3DTexture());
	//this->postprocess->GetD3DEffect()->SetFloat( "time", timeGetTime());
	//this->g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	//this->g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);
	//this->g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	//this->postprocess->GetD3DEffect()->EndPass();
	//this->postprocess->GetD3DEffect()->End();
	
	Vector* lookAt = this->camera->GetLookAt();
	D3DXMatrixLookAtLH( &this->matViewSave, &D3DXVECTOR3( this->camera->GetPosition().x, this->camera->GetPosition().y, this->camera->GetPosition().z), &D3DXVECTOR3(lookAt->x, lookAt->y, lookAt->z), &D3DXVECTOR3( 0.0f, 1.0f, 0.0f) );
	D3DXMatrixPerspectiveFovLH( &this->matProjSave, D3DX_PI/2, (float)SCREEN_WIDTH/(float)SCREEN_HEIGHT, 0.1f, 145.0f );
	this->g_pD3DDevice->SetTransform( D3DTS_VIEW, &this->matViewSave);
	this->g_pD3DDevice->SetTransform( D3DTS_PROJECTION, &this->matProjSave);

	//this->g_pD3DDevice->EndScene();
	this->g_pD3DDevice->Present(0,0,0,0);
	//this->multisampleSurface = NULL;
}

const D3DXMATRIX& Renderer::GetWorldMatrix() const
{
	return this->matWorld;
}

const D3DXMATRIX& Renderer::GetViewMatrix() const
{
	return this->matViewSave;
}

const D3DXMATRIX& Renderer::GetProjectionMatrix() const
{
	return this->matProjSave;
}

const LPDIRECT3DDEVICE9& Renderer::GetDevice() const
{
	return this->g_pD3DDevice;
}

//const LPDIRECT3DTEXTURE9& Renderer::GetRenderTexture() const
//{
//	return this->renderTexture;
//}
const LPDIRECT3DCUBETEXTURE9& Renderer::GetCubemap() const
{
	return this->cubemap;
}

//const LPDIRECT3DSURFACE9& Renderer::GetRenderSurface() const
//{
//	return this->renderSurface;
//}
//const LPDIRECT3DSURFACE9& Renderer::GetBackbuffer() const
//{
//	return this->backbuffer;
//}

void Renderer::SetCamera(Camera* cam)
{
	this->camera = cam;
}

Camera* Renderer::GetCamera()
{
	return this->camera;
}
void Renderer::EnableFullscreen(bool b)
{
	this->fullscreen = b;
}
void Renderer::ToggleFullScreen()
{
	this->fullscreen = !this->fullscreen;
	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp)); // Maak de structure leeg
	d3dpp.Windowed = FALSE; // We willen een window, geen volledig scherm
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD; // Swapeffect
	d3dpp.hDeviceWindow = this->window;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8; // Formaat van de backbuffer
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
    d3dpp.BackBufferHeight = SCREEN_HEIGHT;
    d3dpp.EnableAutoDepthStencil = TRUE;  
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	this->g_pD3DDevice->Reset(&d3dpp);
}

void Renderer::RenderCubemap()
{
	// Save transformation matrices of the device
	//D3DXMATRIX matProjSave, matViewSave;
	//this->g_pD3DDevice->GetTransform(D3DTS_VIEW, &this->matViewSave);
	//this->g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &this->matProjSave);

	D3DCOLOR screenColor = D3DCOLOR_XRGB(0, 0, 0);
	this->g_pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET, screenColor, 1.0f, 0.0f);
	this->g_pD3DDevice->Clear(0, NULL, D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	// Use 90-degree field of view in the projection
	D3DXMATRIX matProj2;
	D3DXMatrixPerspectiveFovLH(&matProj2, D3DX_PI/2, 1.0f, 0.5f, 1000.0f);
	this->g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj2);

	D3DXVECTOR3 vLookatPt = D3DXVECTOR3( 1.0f, 0.0f, 1.0f);
	D3DXVECTOR3 vUpVec = D3DXVECTOR3( 0.0f, 1.0f, 0.0f);
	D3DXMATRIX matView2;
	D3DXMatrixLookAtLH( &matView2, &D3DXVECTOR3( 0.0f, 0.0f, 0.0f), &vLookatPt, &vUpVec );
	this->g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView2);

	LPDIRECT3DSURFACE9 pFace2;
	this->cubemap->GetCubeMapSurface(D3DCUBEMAP_FACE_POSITIVE_Z, 0, &pFace2);
	

	this->g_pD3DDevice->SetRenderTarget(0,pFace2);
	this->g_pD3DDevice->BeginScene();
	Kernel::Instance()->GetScene()->GetTerrain()->Render();
	this->g_pD3DDevice->EndScene();



	// Restore the original transformation matrices
    //this->g_pD3DDevice->SetTransform(D3DTS_VIEW,       &matViewSave);
   // this->g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProjSave);
}

Shader* Renderer::GetPostprocessShader()
{
	return this->postprocess;
}

const RenderTarget* Renderer::GetRenderTarget() const
{
	return this->renderTarget;
}
void Renderer::SetRenderTarget(RenderTarget* renderTarget)
{
	this->renderTarget = renderTarget;
}

Renderer::~Renderer()
{
	this->g_pD3DDevice->Release();    // close and release the 3D device
    this->g_pD3D->Release();    // close and release Direct3D
	//this->t_buffer->Release();
	delete this->backBufferTarget;
	delete this->renderTarget;
	delete this->camera;
	//delete this->postprocess;
	//delete this->postprocessTexture1;
}