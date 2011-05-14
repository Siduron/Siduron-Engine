#include "Model.h"
#include "../Core/Kernel.h"

Model::Model(const std::string modelPath, const std::string modelName)
{
	this->g_pD3DDevice = Kernel::Instance()->GetRenderer()->GetDevice();
	// Create an instance of the Importer class
	Assimp::Importer importer;

	// And have it read the given file with some example postprocessing
	// Usually - if speed is not the most important aspect for you - you'll 
	// propably to request more postprocessing than we do in this example.
	const aiScene* scene = importer.ReadFile( modelPath+modelName, 
	aiProcess_CalcTangentSpace       | 
	aiProcess_Triangulate            |
	aiProcess_JoinIdenticalVertices  |
	aiProcess_FlipUVs				 |
	aiProcess_PreTransformVertices	 |
	aiProcess_FixInfacingNormals	 |
	//aiProcess_FlipWindingOrder		 |
	aiProcess_GenNormals			 |
	aiProcess_GenSmoothNormals |
	aiProcess_SortByPType);

	// If the import failed, report it
	if( !scene)
	{
		Logger::Instance()->Log("Failed to load model "+modelPath+modelName+"!", Error);
	}

	// Now we can access the file's contents. 
	this->scene = scene;

	for(int i = 0; i < scene->mNumMeshes; i++)
	{
		aiString texturePath;
		this->scene->mMaterials[scene->mMeshes[i]->mMaterialIndex]->GetTexture(aiTextureType_DIFFUSE,0,&texturePath);
		std::string tpath(texturePath.data);
		Texture* newTexture = Kernel::Instance()->GetResourceManager()->GetTexture(modelPath + tpath);

		this->meshes.push_back(new Mesh(scene->mMeshes[i], newTexture));
	}
	this->SetShader("Content/Shaders/Default.fx");
}

void Model::Render(D3DXMATRIX matWorld)
{
	//this->g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	//this->g_pD3DDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_SOLID);
	Renderer* renderer = Kernel::Instance()->GetRenderer();
	Camera* cam = renderer->GetCamera();
	

	this->g_pD3DDevice->SetTransform( D3DTS_WORLD,&matWorld );
	D3DXMATRIX worldViewProj = matWorld*renderer->GetViewMatrix()*renderer->GetProjectionMatrix();
	D3DXMATRIX matWorldInverseTransponse;
	D3DXMATRIX matWorldInverse;
	
	D3DXMatrixTranspose(&matWorldInverseTransponse, &matWorld);
	D3DXMatrixInverse(&matWorldInverseTransponse, NULL, &matWorldInverseTransponse);

	for(int i = 0; i < this->meshes.size(); i++)
	{			
		UINT passes;
		int currentTime = timeGetTime();
		Shader* meshShader = this->meshes.at(i)->GetShader();
		meshShader->GetD3DEffect()->SetMatrix( "world", &matWorld);
		meshShader->GetD3DEffect()->SetMatrix( "wvp", &worldViewProj);
		meshShader->GetD3DEffect()->SetMatrix( "itw", &matWorldInverseTransponse);
		meshShader->GetD3DEffect()->SetVector( "CameraPosition", &D3DXVECTOR4(cam->GetPosition().x,cam->GetPosition().y,cam->GetPosition().z,1));
		meshShader->GetD3DEffect()->SetFloat( "LightPosX", 0);
		meshShader->GetD3DEffect()->SetFloat( "LightPosY", 50);	
		meshShader->GetD3DEffect()->SetFloat( "LightPosZ", -10);
		meshShader->GetD3DEffect()->SetFloat( "time", currentTime);

		meshShader->GetD3DEffect()->SetTechnique( "D3D" );
		meshShader->GetD3DEffect()->Begin(&passes,0);
		meshShader->GetD3DEffect()->BeginPass(0);
		this->g_pD3DDevice->SetStreamSource(0, this->meshes.at(i)->vertexBuffer, 0, sizeof(CUSTOMVERTEX));
		this->g_pD3DDevice->SetFVF(CUSTOMFVF);
		this->g_pD3DDevice->SetIndices(this->meshes.at(i)->indexBuffer);
		if(this->meshes.at(i)->texture->GetD3DTexture() != NULL)
		{
			this->g_pD3DDevice->SetTexture(0, this->meshes.at(i)->texture->GetD3DTexture());
		}

		this->g_pD3DDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST,0,0,this->meshes.at(i)->verts.size(),0,this->meshes.at(i)->faceAmount);
		meshShader->GetD3DEffect()->EndPass();
		meshShader->GetD3DEffect()->End();
	}
}

std::vector<Mesh*> Model::GetMeshes()
{
	return this->meshes;
}

void Model::SetShader(std::string path)
{
	for(int i = 0; i < this->meshes.size(); i++)
	{
		this->meshes.at(i)->SetShader(path);
	}
}

void Model::Delete()
{

}

Model::~Model()
{

}