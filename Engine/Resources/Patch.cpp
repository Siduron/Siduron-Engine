#include "Patch.h"

Patch::Patch(Renderer* r)
{
	this->debug = false;
	this->renderer = r;
	this->g_pD3DDevice = r->GetDevice();
	this->wireframe = false;
	this->lod = LOW;
	this->atmosphere = 1.0f;

	//this->position = new Vector(0.0f,0.0f,0.0f);
	//this->rotation = new Vector(0.0f,0.0f,0.0f);
	this->scale = Vector(1.0f,1.0f,1.0f);
	this->technique = "HighDetail";
	this->averageHeight = 0;

	this->primitive_count = 0;
}

void Patch::Create(std::vector<Vertex*> v)
{
	this->vertices = v;
	float totalHeight = 0;
	for(unsigned int i = 0; i < vertices.size(); i++)
	{
		this->Vertices[i] = *vertices.at(i)->GetCustomVertex();
		totalHeight += vertices[i]->GetHeight();
	}
	this->averageHeight = totalHeight / this->vertices.size();
	HRESULT hr = this->g_pD3DDevice->CreateVertexBuffer(25*sizeof(CUSTOMVERTEX),D3DUSAGE_WRITEONLY,CUSTOMFVF,D3DPOOL_MANAGED,&this->t_buffer,NULL);
	VOID* pVoid = NULL;    // the void* we were talking about

	//25 vertices
	this->t_buffer->Lock(0,25*sizeof(CUSTOMVERTEX), &pVoid, 0);    // locks t_buffer, the buffer we made earlier
	
	memcpy(pVoid, this->Vertices, sizeof(this->Vertices));    // copy vertices to the vertex buffer

	this->t_buffer->Unlock();    // unlock t_buffer

	this->center = this->vertices.at(12)->GetPosition(); //Set the center of this patch
	
	this->is_flat = true;
	for(unsigned int i = 1; i < vertices.size(); i++)
	{
		if(this->vertices[0]->GetHeight() != this->vertices[i]->GetHeight())
		{
			this->is_flat = false;
		}
	}
}

void Patch::Render()
{
	//D3DXMATRIX worldViewProj = this->matWorld**this->renderer->GetViewMatrix()**this->renderer->GetProjectionMatrix();
	//D3DXMATRIX matWorldInverseTransponse;
	//D3DXMATRIX matWorldInverse;

	//Vector* camPos = this->renderer->GetCamera()->GetPosition();
	//D3DXMatrixRotationX( &this->matRotateX, this->rotation->x );        // Pitch
	//D3DXMatrixRotationY( &this->matRotateY, this->rotation->y );        // Yaw
	//D3DXMatrixRotationZ( &this->matRotateZ, this->rotation->z );        // Roll
	//D3DXMatrixTranslation( &this->matTranslate, this->position->x-camPos->x,this->position->y-camPos->y,this->position->z-camPos->z );
	//D3DXMatrixScaling( &this->matScale, this->scale->x,this->scale->y,this->scale->z );
	//this->matWorld=(this->matRotateX*this->matRotateY*this->matRotateZ) * this->matScale * this->matTranslate;
	//this->g_pD3DDevice->SetTransform( D3DTS_WORLD,&this->matWorld );

	//
	//D3DXMatrixTranspose(&matWorldInverseTransponse, &this->matWorld);
	//D3DXMatrixInverse(&matWorldInverseTransponse, NULL, &matWorldInverseTransponse);

	//this->shader->GetD3DEffect()->SetFloat( "atmosphere", this->atmosphere);
	if(this->debug)
	{
		this->shader->GetD3DEffect()->SetTechnique( "Debug" );
	}
	this->shader->GetD3DEffect()->SetTechnique( this->technique.c_str());
	//this->shader->GetD3DEffect()->SetTechnique( "HighDetail" );
	//else this->shader->GetD3DEffect()->SetTechnique( "LowDetail" );

	//this->shader->GetD3DEffect()->SetMatrix( "wvp", this->worldViewProj);
	//this->shader->GetD3DEffect()->SetMatrix( "itw", this->matWorldInverseTransponse);
	//this->shader->GetD3DEffect()->Begin(&passes,0);
	//this->shader->GetD3DEffect()->BeginPass(0);
	this->g_pD3DDevice->SetStreamSource(0, this->t_buffer, 0, sizeof(CUSTOMVERTEX));
	
	if(this->wireframe)
	{
		this->renderer->EnableWireframe(true);
	}

	DETAILLEVEL leftDetail;
	DETAILLEVEL rightDetail;
	DETAILLEVEL upDetail;
	DETAILLEVEL downDetail;

	if(this->left != NULL) leftDetail = this->left->GetLod();
	if(this->right != NULL) rightDetail = this->right->GetLod();
	if(this->up != NULL) upDetail = this->up->GetLod();
	if(this->down != NULL) downDetail = this->down->GetLod();

	LPDIRECT3DINDEXBUFFER9 temp_index_buffer;
	if( this->IsFlat() )
	{
		temp_index_buffer = this->indexbufferLow;
		this->primitive_count = 2; //Low detail 2 triangles
	}
	else if(this->lod == LOW)
	{
		if(this->left != NULL && leftDetail == MEDIUM)
		{	
			if(this->up != NULL && upDetail == MEDIUM)
			{
				temp_index_buffer = this->indexbufferLow_stitchtopleft;
				this->primitive_count = 8; //Low detail 8 triangles
			}
			else if(this->down != NULL && downDetail == MEDIUM)
			{
				temp_index_buffer = this->indexbufferLow_stitchbottomleft;
				this->primitive_count = 4; //Low detail 8 triangles
			}
			else
			{
				temp_index_buffer = this->indexbufferLow_stitchleft;
				this->primitive_count = 3; //Low detail 3 triangles
			}
		}
		else if(this->right != NULL && rightDetail == MEDIUM)
		{
			if(this->up != NULL && upDetail == MEDIUM)
			{
				temp_index_buffer = this->indexbufferLow_stitchtopright;
				this->primitive_count = 4; //Low detail 4 triangles
			}
			else if(this->down != NULL && downDetail == MEDIUM)
			{
				temp_index_buffer = this->indexbufferLow_stitchbottomright;
				this->primitive_count = 6; //Low detail 6 triangles
			}
			else
			{
				temp_index_buffer = this->indexbufferLow_stitchright;
				this->primitive_count = 4; //Low detail 4 triangles
			}
		}
		else if(this->up != NULL && upDetail == MEDIUM)
		{
			temp_index_buffer = this->indexbufferLow_stitchtop;
			this->primitive_count = 3; //Low detail 3 triangles
		}
		else if(this->down != NULL && downDetail == MEDIUM)
		{
			temp_index_buffer = this->indexbufferLow_stitchbottom;
			this->primitive_count = 3; //Low detail 3 triangles
		}
		else
		{
			temp_index_buffer = this->indexbufferLow;
			this->primitive_count = 2; //Low detail 2 triangles
		}
	}
	else if(this->lod == MEDIUM)
	{
		if(this->left != NULL && leftDetail == HIGH)
		{
			if(this->up != NULL && upDetail == HIGH)
			{
				temp_index_buffer = this->indexbufferMedium_stitchtopleft;
				this->primitive_count = 30; //Medium detail 30 triangles
			}
			else if(this->down != NULL && downDetail == HIGH)
			{
				temp_index_buffer = this->indexbufferMedium_stitchbottomleft;
				this->primitive_count = 39; //Medium detail 39 triangles << 9 more than topleft?
			}
			else
			{
				temp_index_buffer = this->indexbufferMedium_stitchleft;
				this->primitive_count = 24; //Medium detail 24 triangles
			}
		}
		else if(this->right != NULL && rightDetail == HIGH)
		{
			if(this->up != NULL && upDetail == HIGH)
			{
				temp_index_buffer = this->indexbufferMedium_stitchtopright;
				this->primitive_count = 30; //Medium detail 30 triangles
			}
			else if(this->down != NULL && downDetail == HIGH)
			{
				temp_index_buffer = this->indexbufferMedium_stitchbottomright;
				this->primitive_count = 28; //Medium detail 28 triangles
			}
			else
			{
				temp_index_buffer = this->indexbufferMedium_stitchright;
				this->primitive_count = 24; //Medium detail 24 triangles
			}
		}
		else if(this->up != NULL && upDetail == HIGH)
		{
			temp_index_buffer = this->indexbufferMedium_stitchtop;
			this->primitive_count = 22; //Medium detail 22 triangles
		}
		else if(this->down != NULL && downDetail == HIGH)
		{
			temp_index_buffer = this->indexbufferMedium_stitchbottom;
			this->primitive_count = 22; //Medium detail 22 triangles
		}
		else
		{
			temp_index_buffer = this->indexbufferMedium;
			this->primitive_count = 12; //Medium detail 12 triangles
		}
	}
	else if(this->lod == HIGH)
	{
			temp_index_buffer = this->indexbufferHigh;
			this->primitive_count = 44; //High detail 44 triangles
	}
	
	this->g_pD3DDevice->SetIndices(temp_index_buffer);
	this->g_pD3DDevice->DrawIndexedPrimitive( D3DPT_TRIANGLESTRIP,0,0,25,0,this->primitive_count);
	//this->shader->GetD3DEffect()->EndPass();
	//this->shader->GetD3DEffect()->End();
	//if(this->wireframe)
	//{
	//	this->renderer->EnableWireframe(false);
	//}
}

void Patch::EnableWireframe(bool wireframe)
{
	this->wireframe = wireframe;
	//if(wireframe)
	//{
	//	this->wireframerenderer->EnableWireframe(true);
	//}
	//else
	//{
	//	this->renderer->EnableWireframe(false);
	//}
}

const bool Patch::IsFlat() const
{
	return this->is_flat;
}

void Patch::EnableDebug(bool debug)
{
	this->debug = debug;
}

void Patch::SetNeighbours(std::map<std::string, Patch*> n)
{
	this->neighbours = n;
	this->left = this->neighbours["Left"];
	this->right = this->neighbours["Right"];
	this->up = this->neighbours["Up"];
	this->down = this->neighbours["Down"];
}

void Patch::SetLod(DETAILLEVEL lod)
{
	this->lod = lod;
}

void Patch::SetShader(Shader* s)
{
	this->shader = s;
}

void Patch::SetTechnique(std::string technique)
{
	this->technique = technique;
}

const std::map<std::string, Patch*>& Patch::GetNeighbours()  const
{
	return this->neighbours;
}

Vector Patch::GetCenter() const
{
	return this->center;
}

const DETAILLEVEL& Patch::GetLod() const
{
	return this->lod;
}

const std::vector<Vertex*>& Patch::GetVertices() const
{
	return this->vertices;
}

Shader* Patch::GetShader() const
{
	return this->shader;
}

const float Patch::GetAverageHeight() const
{
	return this->averageHeight;
}

void Patch::Flatten()
{
	//this->t_buffer->Release();
	//float totalHeight = 0;
	//for(int i = 0; i < this->vertices.size(); i++)
	//{
	//	totalHeight += this->vertices[i]->GetHeight();
	//}

	//for(int i = 0; i < this->vertices.size(); i++)
	//{
	//	this->vertices[i]->SetHeight(totalHeight/this->vertices.size());
	//}
	//this->Create(this->vertices);
}