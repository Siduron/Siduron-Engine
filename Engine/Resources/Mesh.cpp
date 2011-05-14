#include "Mesh.h"
#include "../Core/Kernel.h"

//Constructor for loading an AssImp mesh.
Mesh::Mesh(aiMesh* m, Texture* t)
{
	//Set variables
	this->mesh = m;
	this->texture = t;
	this->g_pD3DDevice = Kernel::Instance()->GetRenderer()->GetDevice();

	//Create all the vertices from the mesh data.
	for(int i = 0; i < m->mNumVertices; i++)
	{
		aiVector3D vector = m->mVertices[i];
		Vertex* v;

		//Set UV data if the current vertex has them, or else set them to 0.
		if(m->HasTextureCoords(0))
		{
			v = new Vertex(vector.x,vector.y,vector.z,m->mNormals[i].x,m->mNormals[i].y,m->mNormals[i].z,m->mTextureCoords[0][i].x,m->mTextureCoords[0][i].y);
		}
		else
		{
			v = new Vertex(vector.x,vector.y,vector.z,0,0,0,0,0);
		}
		this->verts.push_back(v);
	}
	//Get every wrapped d3d vertex and put them in an array for vertexbuffer use.
	CUSTOMVERTEX* l_vertices = new CUSTOMVERTEX[m->mNumVertices];
	for(int i = 0; i < m->mNumVertices; i++)
	{
		aiVector3D vector = m->mVertices[i];
		l_vertices[i] = *this->verts.at(i)->GetCustomVertex();
	}
	//Create the vertex buffer and copy all vertices into it.
	this->g_pD3DDevice->CreateVertexBuffer(m->mNumVertices*sizeof(CUSTOMVERTEX),D3DUSAGE_WRITEONLY,CUSTOMFVF,D3DPOOL_MANAGED,&this->vertexBuffer,NULL);
	VOID* pVoid = NULL;
	this->vertexBuffer->Lock(0,m->mNumVertices*sizeof(CUSTOMVERTEX), &pVoid, 0);
	memcpy(pVoid, l_vertices, this->verts.size()*sizeof(CUSTOMVERTEX)); 
	this->vertexBuffer->Unlock();

	//Create the index buffer and retrieve index values from mesh.
	this->faceAmount = m->mNumFaces;
	this->g_pD3DDevice->CreateIndexBuffer((this->faceAmount*3)*sizeof(WORD),D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &this->indexBuffer, NULL);
	WORD *indices=NULL;

	this->indexBuffer->Lock( 0, 0, (void**)&indices, 0 );
	for(int i = 0; i < this->faceAmount; i++)
	{
		indices[0+(i*3)] = m->mFaces[i].mIndices[0],
		indices[1+(i*3)] = m->mFaces[i].mIndices[1],
		indices[2+(i*3)] = m->mFaces[i].mIndices[2];
	}
	this->indexBuffer->Unlock();
}

//Set the shader for this mesh.
void Mesh::SetShader(std::string path)
{
	this->shader = Kernel::Instance()->GetResourceManager()->GetShader(path);
}

//Get the shader for this mesh.
Shader* Mesh::GetShader()
{
	return this->shader;
}
