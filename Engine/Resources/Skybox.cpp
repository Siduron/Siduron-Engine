//#include "Skybox.h"
//#include "../Core/Kernel.h"
//#include "../Core/DEGTORAD.h"
//
//Skybox::Skybox()
//{
//	this->g_pD3DDevice = Kernel::Instance()->GetRenderer()->GetDevice();
//	this->activeCamera = NULL;
//}
//
//Skybox::~Skybox()
//{
//
//}
//
//void Skybox::Render()
//{
//	this->Update();
//	this->g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
//	this->g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
//	this->g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, D3DZB_FALSE);
//	//this->g_pD3DDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_SOLID);
//	//this->g_pD3DDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);
//
//	for(int i = 0; i < this->models.size(); i++)
//	{
//		//this->models.at(i)->Render(this->matWorld);
//	}
//	this->g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
//	this->g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, D3DZB_TRUE);
//	this->g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
//	Node::Render();
//}
//void Skybox::Update()
//{
//	if(this->activeCamera != NULL)
//	{
//		for(int i = 0; i < this->models.size(); i++)
//		{
//			//this->models.at(i)->SetPosition(this->activeCamera->GetPosition());
//		}
//	}
//}
//
//void Skybox::BindToCamera(Camera* cam)
//{
//	this->activeCamera = cam;
//}
//
//void Skybox::AddModel(Model* m)
//{
//	this->models.push_back(m);
//}