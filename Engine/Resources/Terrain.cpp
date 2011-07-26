#include "Terrain.h"
#include "../Core/Kernel.h"
#include "noiseutils.h"

Terrain::Terrain()
{
	this->debug = false;
	this->renderer = Kernel::Instance()->GetRenderer();
	this->g_pD3DDevice = this->renderer->GetDevice();
	//this->position = Vector(0.0f,0.0f,0.0f);
	//this->rotation = Vector(0.0f,0.0f,0.0f);
	this->scale = Vector(1.0f,1.0f,1.0f);
	//this->cameraPosition = Kernel::Instance()->GetRenderer()->GetCamera()->GetPosition();
	this->worldViewProj = new D3DXMATRIX();
	this->matWorldInverse = new D3DXMATRIX();
	this->matWorldInverseTransponse = new D3DXMATRIX();
	
	ResourceManager* resourceManager = Kernel::Instance()->GetResourceManager();
	this->greenWorld.Texture1 = resourceManager->GetTexture("Content/Textures/Terrain/Grass0027_13_S.jpg");
	this->greenWorld.Texture2 = resourceManager->GetTexture("Content/Textures/Terrain/sandtexture.jpg");
	this->greenWorld.Texture3 = resourceManager->GetTexture("Content/Textures/Terrain/Cliffs0074_2_S.jpg");
	this->greenWorld.Texture4 = resourceManager->GetTexture("Content/Textures/Terrain/Concrete tile.jpg");
	this->greenWorld.alt_Texture1 = resourceManager->GetTexture("Content/Textures/Terrain/SoilMud0103_2_S.jpg");
	this->greenWorld.debug = resourceManager->GetTexture("Content/Textures/Terrain/devtexture.bmp");
	this->currentSet = this->greenWorld;
}

void Terrain::Create(int mapSize)
{
	this->CreateNoise();
	//this->texture_map = Kernel::Instance()->GetResourceManager()->GetTexture("Content/Maps/"+mapName+"/texturemap.png");
	//this->texture_normal = Kernel::Instance()->GetResourceManager()->GetTexture("Content/Maps/"+mapName+"/normalmap.png");
	//this->texture_alphamap_detail1 = Kernel::Instance()->GetResourceManager()->GetTexture("Content/Maps/"+mapName+"/alphamap_0.png");
	//this->texture_alphamap_detail2 = Kernel::Instance()->GetResourceManager()->GetTexture("Content/Maps/"+mapName+"/alphamap_1.png");
	//this->texture_alphamap_lava = Kernel::Instance()->GetResourceManager()->GetTexture("Content/Maps/"+mapName+"/alphamap_2.png");

	//this->texture_detail1 = Kernel::Instance()->GetResourceManager()->GetTexture("Content/Textures/Terrain/Grass0027_13_S.jpg");
	//this->texture_detail1_alternate = Kernel::Instance()->GetResourceManager()->GetTexture("Content/Textures/Terrain/SoilMud0103_2_S.jpg");
	//this->texture_detail2 = Kernel::Instance()->GetResourceManager()->GetTexture("Content/Textures/Terrain/sandtexture.jpg");
	//this->texture_detail3 = Kernel::Instance()->GetResourceManager()->GetTexture("Content/Textures/Terrain/Cliffs0074_2_S.jpg");
	
	//this->texture_lava = Kernel::Instance()->GetResourceManager()->GetTexture("Textures/Terrain/4278406515_9a31c37ff5.jpg");
	
	this->texture_water1 = Kernel::Instance()->GetResourceManager()->GetTexture("Content/Textures/Terrain/3020_bump.jpg");
	this->texture_water2 = Kernel::Instance()->GetResourceManager()->GetTexture("Content/Textures/Terrain/3020.jpg");
	//this->texture_height = Kernel::Instance()->GetResourceManager()->GetTexture("hm_tropical.bmp");
	
	this->terrainshader = Kernel::Instance()->GetResourceManager()->GetShader("Content/Shaders/TerrainShaderNew.fx");
	this->watershader = Kernel::Instance()->GetResourceManager()->GetShader("Content/Shaders/WaterNew.fx");
	Logger::Instance()->Log("Loading Heightmap..", Info);

	//this->LoadBMP("Content/Maps/"+mapName+"/heightmap.bmp");
	//this->LoadBMP("tutorial.bmp");
	//this->SmoothHeightData(0); //Smooth the height data
	
	//Create vertices, 34*34 for the first region. 32*32 vertices for all other regions
	Logger::Instance()->Log("Creating Vertices..", Info);
	float vertoffset = 0.25f;
	int size = (33*mapSize)+1;

	for(int a = 0; a <= size; a++)
	{
		std::vector<Vertex*> tempVerts;
		for(int b = 0; b <= size; b++)
		{
			Vertex* v = new Vertex(vertoffset * b, this->hmap[b][a], (-vertoffset * a), 1, 1, 1, b, a);
			tempVerts.push_back(v);
		}
		this->verts2.push_back(tempVerts);
	}
	
	Logger::Instance()->Log("Creating Indexbuffers..", Info);
	this->CreateIndexbuffers();

	Logger::Instance()->Log("Creating Patches..", Info);
	for(unsigned int v = 0; v < (8*mapSize); v++)
	{
		std::vector<Patch*> temppatches;
		for(unsigned int h = 0; h < (8*mapSize); h++)
		{
			Patch* temppatch = new Patch(this->renderer);
			std::vector<Vertex*> verts;

			for(unsigned int a = 0; a <= 4; a++)
			{
				for(unsigned int b = 0; b <= 4; b++)
				{
					verts.push_back(this->verts2.at(a+(4*v)).at(b+(4*h)));
				}
			}

			temppatch->Create(verts);

			//Set indexbuffers
			temppatch->indexbufferHigh = this->indexbufferHigh;
			temppatch->indexbufferMedium = this->indexbufferMedium;
			temppatch->indexbufferLow = this->indexbufferLow;

			temppatch->indexbufferMedium_stitchleft = this->indexbufferMedium_stitchleft;
			temppatch->indexbufferMedium_stitchtopleft = this->indexbufferMedium_stitchtopleft;
			temppatch->indexbufferMedium_stitchbottomleft = this->indexbufferMedium_stitchbottomleft;
			temppatch->indexbufferMedium_stitchtop = this->indexbufferMedium_stitchtop;
			temppatch->indexbufferMedium_stitchbottom = this->indexbufferMedium_stitchbottom;
			temppatch->indexbufferMedium_stitchright = this->indexbufferMedium_stitchright;
			temppatch->indexbufferMedium_stitchtopright = this->indexbufferMedium_stitchtopright;
			temppatch->indexbufferMedium_stitchbottomright = this->indexbufferMedium_stitchbottomright;

			temppatch->indexbufferLow_stitchleft = this->indexbufferLow_stitchleft;
			temppatch->indexbufferLow_stitchtopleft = this->indexbufferLow_stitchtopleft;
			temppatch->indexbufferLow_stitchbottomleft = this->indexbufferLow_stitchbottomleft;
			temppatch->indexbufferLow_stitchtop = this->indexbufferLow_stitchtop;
			temppatch->indexbufferLow_stitchbottom = this->indexbufferLow_stitchbottom;
			temppatch->indexbufferLow_stitchright = this->indexbufferLow_stitchright;
			temppatch->indexbufferLow_stitchtopright = this->indexbufferLow_stitchtopright;
			temppatch->indexbufferLow_stitchbottomright = this->indexbufferLow_stitchbottomright;
			
			//temppatch->texture_alphamap_detail1 = this->texture_alphamap_detail1;
			//temppatch->texture_alphamap_detail2 = this->texture_alphamap_detail2;
			/*temppatch->texture_detail1 = this->texture_detail1;
			temppatch->texture_detail1_alternate = this->texture_detail1_alternate;
			temppatch->texture_detail2 = this->texture_detail2;
			temppatch->texture_map = this->texture_map;
			temppatch->texture_normal = this->texture_normal;*/
			temppatch->SetShader(this->terrainshader);
			temppatch->worldViewProj = this->worldViewProj;
			temppatch->matWorldInverse = this->matWorldInverse;
			temppatch->matWorldInverseTransponse = this->matWorldInverseTransponse;
			temppatches.push_back(temppatch);
		}
		this->patches.push_back(temppatches);
	}

	//Set neighbours for the patches
	Logger::Instance()->Log("Setting Patch neighbours..", Info);
	for(unsigned int a = 0; a < this->patches.size(); a++)
	{	
		for(unsigned int b = 0; b < this->patches.at(a).size(); b++)
		{	
			std::map<std::string, Patch*> neighbours;
			if(b > 0) neighbours.insert(std::make_pair("Left", this->patches.at(a).at(b-1)));
			if(b < this->patches.at(a).size()-1) neighbours.insert(std::make_pair("Right", this->patches.at(a).at(b+1)));
			if(a > 0) neighbours.insert(std::make_pair("Up", this->patches.at(a-1).at(b)));
			if(a < this->patches.size()-1) neighbours.insert(std::make_pair("Down", this->patches.at(a+1).at(b)));
			this->patches.at(a).at(b)->SetNeighbours(neighbours);
		}
	}
	//Create Quadtree
	Logger::Instance()->Log("Creating Quadtree..", Info);
	this->quadtree = new Quadtree(this->patches, 0.0f, 8.0f*mapSize, 0.0f, -8.0f*mapSize, 8.0f*mapSize, 8.0f*mapSize);
	
	//Water plane, to test water shader only
	/*Logger::Instance()->Log("Creating Water..", Info);
	float watersize = 265.0f;
	float texsize = 265.0f;
	Vertex* TopLeft = new Vertex(32, 7.0f, 0, texsize, texsize,0,0,0);
	Vertex* TopRight = new Vertex(96, 7.0f, 0, 0.0f, texsize,0,1,0);
	Vertex* BottomLeft = new Vertex(32, 7.0f, -96, texsize, 0.0f,0,0,1);
	Vertex* BottomRight = new Vertex(96, 7.0f, -96,0.0f, 0.0f,0,1,1);
	CUSTOMVERTEX Vertices[4];
	Vertices[0] = *BottomLeft->GetCustomVertex();
	Vertices[1] = *TopLeft->GetCustomVertex();
	Vertices[2] = *BottomRight->GetCustomVertex();
	Vertices[3] = *TopRight->GetCustomVertex();
	this->g_pD3DDevice->CreateVertexBuffer(4*sizeof(CUSTOMVERTEX),D3DUSAGE_WRITEONLY,CUSTOMFVF,D3DPOOL_MANAGED,&this->waterbuffer,NULL);
	VOID* pVoid = NULL;
	this->waterbuffer->Lock(0,4*sizeof(CUSTOMVERTEX), &pVoid, 0);
	memcpy(pVoid, Vertices, sizeof(Vertices));

	this->waterbuffer->Unlock();*/
}

void Terrain::Render()
{
	////this->g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	//this->g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, D3DZB_TRUE);
	//this->g_pD3DDevice->SetRenderState(D3DRS_FOGENABLE,FALSE);
	//this->g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	Vector camPos = this->renderer->GetCamera()->GetPosition();

	//D3DXMatrixRotationX( &this->matRotateX, this->rotation.x );        // Pitch
	//D3DXMatrixRotationY( &this->matRotateY, this->rotation.y );        // Yaw
	//D3DXMatrixRotationZ( &this->matRotateZ, this->rotation.z );        // Roll
	//D3DXMatrixTranslation( &this->matTranslate, this->position.x,this->position.y,this->position.z );
	//D3DXMatrixScaling( &this->matScale, this->scale.x,this->scale.y,this->scale.z );

	//this->matWorld=(this->matRotateX*this->matRotateY*this->matRotateZ) * this->matScale * this->matTranslate;
	this->g_pD3DDevice->SetTransform( D3DTS_WORLD,&this->matWorld );
	*this->worldViewProj = (this->matWorld*this->renderer->GetViewMatrix()*this->renderer->GetProjectionMatrix());
	D3DXMATRIX view = this->renderer->GetViewMatrix();
	D3DXMATRIX projection = this->renderer->GetProjectionMatrix();
	//D3DXMATRIX matWorldInverseTransponse;
	//D3DXMATRIX matWorldInverse;
	
	D3DXMatrixTranspose(this->matWorldInverseTransponse, &this->matWorld);
	D3DXMatrixInverse(this->matWorldInverseTransponse, NULL, matWorldInverseTransponse);
	
	if(!debug)
	{
		this->g_pD3DDevice->SetTexture(0,this->texture_map->GetD3DTexture() );
		this->g_pD3DDevice->SetTexture(1,this->currentSet.Texture1->GetD3DTexture() );
		this->g_pD3DDevice->SetTexture(2,this->currentSet.Texture2->GetD3DTexture() );
		this->g_pD3DDevice->SetTexture(3,this->currentSet.Texture3->GetD3DTexture() );
		this->g_pD3DDevice->SetTexture(4,this->texture_normal->GetD3DTexture() );
		this->g_pD3DDevice->SetTexture(5,this->currentSet.alt_Texture1->GetD3DTexture() );
		this->g_pD3DDevice->SetTexture(6,this->currentSet.Texture4->GetD3DTexture() );
	}
	else
	{
		this->g_pD3DDevice->SetTexture(1,this->currentSet.debug->GetD3DTexture() );
	}
	
	//Render
	this->quadtree->GetMasterNode()->CalcLod(Kernel::Instance()->GetRenderer()->GetCamera()->GetPosition());
	this->quadtree->GetMasterNode()->Render(Kernel::Instance()->GetRenderer()->GetCamera()->GetPosition());

	//this->renderer->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);
	//this->renderer->GetDevice()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	//this->renderer->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//this->renderer->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//this->g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	Node::Render();
}
void Terrain::RenderWater()
{
	D3DXMATRIX remap;
	D3DXMATRIX projTex = remap*this->renderer->GetViewMatrix()*this->renderer->GetProjectionMatrix();
	this->g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE	);
	UINT passes2;
	this->watershader->GetD3DEffect()->SetTechnique( "D3D" );
	this->watershader->GetD3DEffect()->SetMatrix( "wvp", worldViewProj);
	this->watershader->GetD3DEffect()->SetMatrix( "world", &this->matWorld);
	this->watershader->GetD3DEffect()->SetMatrix( "projTex", &projTex);
	this->watershader->GetD3DEffect()->Begin(&passes2,0);
	this->watershader->GetD3DEffect()->BeginPass(0);
	this->g_pD3DDevice->SetTexture(0,this->texture_water1->GetD3DTexture() );
	this->g_pD3DDevice->SetTexture(1,this->texture_water2->GetD3DTexture() );
	this->watershader->GetD3DEffect()->SetFloat("time", timeGetTime());
	Vector camPos = Kernel::Instance()->GetRenderer()->GetCamera()->GetPosition();
	this->watershader->GetD3DEffect()->SetVector( "camPos", &D3DXVECTOR4(camPos.x,camPos.y,camPos.z,1));
	this->watershader->GetD3DEffect()->SetVector( "EyePosition", &D3DXVECTOR4(0,0,0,1));
	this->g_pD3DDevice->SetStreamSource(0, this->waterbuffer, 0, sizeof(CUSTOMVERTEX));
	this->g_pD3DDevice->SetFVF(CUSTOMFVF);
	this->g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	this->watershader->GetD3DEffect()->EndPass();
	this->watershader->GetD3DEffect()->End();
	this->g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	
}

void Terrain::ToggleWireframe()
{
	//for(unsigned int a = 0; a < this->patches.size(); a++)
	//{
	//	for(unsigned int b = 0; b < this->patches.at(a).size(); b++)
	//	{
	//		//this->patches.at(a).at(b)->ToggleWireframe();
	//	}
	//}
}

void Terrain::EnableDebug(bool debug)
{
	this->debug = debug;
	for(unsigned int a = 0; a < this->patches.size(); a++)
	{
		for(unsigned int b = 0; b < this->patches[a].size(); b++)
		{
			this->patches[a][b]->EnableDebug(debug);
		}
	}
}

bool Terrain::LoadBMP(std::string argFileName)
{
	//Logger::Instance()->Log("Loading Heightmap..", Info);
	//Load image from file
	HDC lhdcDest;	//Handle to Device Context (Windows GDI)
	HANDLE hbmp;	//Handle to an object (standard handle)
	HINSTANCE* hInst = new HINSTANCE();//Handle to an instance (instance of the window)

	//Create a memory device context compatible with the specified device (NULL)
	lhdcDest = CreateCompatibleDC(NULL);
	if (lhdcDest == NULL)	 
	{		  
		DeleteDC(lhdcDest);	//Delete the DC (prevents a memory leak!)
		return false;		//Jump out of the function
	}

	//Windows GDI load image of type BMP (fileformat)
	hbmp = LoadImage(*hInst, argFileName.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (hbmp == NULL)	//Give a visual warning if the loading of the image failed
	{
		char s[100];
		wsprintf(s, "Can't find HeightMask %s", argFileName);
		MessageBox(NULL, s, "ERROR ERROR ERROR", MB_OK);
		return false;		//Jump out of the function
	}
	//At this point it is sure that lhdcDest & hbmp are valid.

	//Load the bmp into the device context (memory space)
	SelectObject(lhdcDest, hbmp);

	//The BITMAP structure defines the type, width, height, color format, and bit values of a bitmap
	BITMAP bm;
	//The GetObject function retrieves information for the specified graphics object
	//bm is cast to a "void*" because GetObject function doesn't 'know' it's format 
	//(don't know what it is, but just put it in that buffer)
	GetObject(hbmp, sizeof(BITMAP), (void*)&bm);

	//Store the width and height of the heightmap
	int width = bm.bmWidth;
	int height = bm.bmHeight;

	//Check if the bitmap's dimensions are dividable by 2
	//if (width % 2 > 0 || height % 2 > 0)
	//{
	//	Logger::Instance()->Log("Incorrect heightmap dimensions, must be dividable by 2..", Error);
	//	return false;
	//}
		
	//Create an array to hold all the heightdata
	//WHY is a BYTE array used, and not e.g. a INT array?
	//WHY "*3"?
	BYTE* tempheightData = new BYTE[width*width*3];
	
	//Iterate through the BMP-file and fill the heightdata-array
	for (int lHeight = 0; lHeight < width; lHeight++)
	{
		for (int lWidth = 0; lWidth < width; lWidth++)
		{
			tempheightData[(lWidth*width*3)+lHeight*3+0] = GetRValue(GetPixel(lhdcDest, lHeight, lWidth));
			tempheightData[(lWidth*width*3)+lHeight*3+1] = GetGValue(GetPixel(lhdcDest, lHeight, lWidth));
			tempheightData[(lWidth*width*3)+lHeight*3+2] = GetBValue(GetPixel(lhdcDest, lHeight, lWidth));
		}
	}
	//Check if the bitmap is greyscale
	if( (tempheightData[0] + tempheightData[1] + tempheightData[2]) / 3  != tempheightData[0])
	{
		Logger::Instance()->Log("Heightmap is not greyscale..", Error);
		return false;
	}

	//Fill the heightmap array for the terrain. b is width or x, a is height or z
	int counter = 0;
	for(int a=0; a < 530; a++)
	{
		for(int b=0; b < 530; b++)
		{
			this->hmap[b][a] = tempheightData[counter*3]*0.04f;
			counter++;
		}
	}
	
	delete hInst;
	return true;
}

/*/////////////////////////////////////////
Smoothes the height data
*//////////////////////////////////////////
void Terrain::SmoothHeightData(int passes)
{
	float adjacentAmount = 0.0f; //amount of neighbours heights
	float adjacentTotal = 0.0f; //total amount of height of all neighbours
	for(int i = 0; i < passes; i++)
	{
		float newhmap[530][530];
		for(int height = 0; height < 530; height++)
		{
			for(int width = 0; width < 530; width++)
			{
				adjacentAmount = 0.0f;
				adjacentTotal = 0.0f;
				if(width-1 > 0) //Check left
				{
					adjacentAmount++;
					adjacentTotal += this->hmap[width-1][height];

					if(height > 0) //Check upper left
					{
						adjacentAmount++;
						adjacentTotal += this->hmap[width-1][height-1];
					}
					if(height < 530) //Check bottom left
					{
						adjacentAmount++;
						adjacentTotal += this->hmap[width-1][height+1];
					}
				}
				if(width < 530) //Check right
				{
					adjacentAmount++;
					adjacentTotal += this->hmap[width+1][height];
					if(height > 0) //Check upper right
					{
						adjacentAmount++;
						adjacentTotal += this->hmap[width+1][height-1];
					}
					if(height < 530) //Check bottom right
					{
						adjacentAmount++;
						adjacentTotal += this->hmap[width+1][height+1];
					}
				}
				if((height) > 0) //Check up
				{
					adjacentAmount++;
					adjacentTotal += this->hmap[width][height-1];
				}
				if(height < 530) //Check down
				{
					adjacentAmount++;
					adjacentTotal += this->hmap[width][height+1];
				}
				float newheight = (this->hmap[width][height] + (adjacentTotal / adjacentAmount)) * 0.5f;
				newhmap[width][height] = newheight;
			}
		}
		//Overwrite the original heightmap
		for (int a = 0; a < 530; a++)
		{
			for (int b = 0; b < 530; b++)
			{
				this->hmap[a][b] = newhmap[a][b];
			}
        }
	}
}



/*/////////////////////////////////////////
Create the indexbuffers
*//////////////////////////////////////////
void Terrain::CreateIndexbuffers()
{
/*Create indices for high detail level*/
	this->g_pD3DDevice->CreateIndexBuffer(46*sizeof(WORD),D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &this->indexbufferHigh, NULL);
	WORD *indices_high=NULL;
	this->indexbufferHigh->Lock( 0, 0, (void**)&indices_high, 0 );
	//Row 1
	indices_high[0] = 5;
	indices_high[1] = 0;
	indices_high[2] = 6;
	indices_high[3] = 1;
	indices_high[4] = 7;
	indices_high[5] = 2;
	indices_high[6] = 8;
	indices_high[7] = 3;
	indices_high[8] = 9;
	indices_high[9] = 4;

	//Degenerating
	indices_high[10] = 4;
	indices_high[11] = 10;

	//Row 2
	indices_high[12] = 10;
	indices_high[13] = 5;
	indices_high[14] = 11;
	indices_high[15] = 6;
	indices_high[16] = 12;
	indices_high[17] = 7;
	indices_high[18] = 13;
	indices_high[19] = 8;
	indices_high[20] = 14;
	indices_high[21] = 9;

	//Degenerating
	indices_high[22] = 9;
	indices_high[23] = 15;

	//Row 3
	indices_high[24] = 15;
	indices_high[25] = 10;
	indices_high[26] = 16;
	indices_high[27] = 11;
	indices_high[28] = 17;
	indices_high[29] = 12;
	indices_high[30] = 18;
	indices_high[31] = 13;
	indices_high[32] = 19;
	indices_high[33] = 14;

	//Degenerating
	indices_high[34] = 14;
	indices_high[35] = 20;

	//Row 4
	indices_high[36] = 20;
	indices_high[37] = 15;
	indices_high[38] = 21;
	indices_high[39] = 16;
	indices_high[40] = 22;
	indices_high[41] = 17;
	indices_high[42] = 23;
	indices_high[43] = 18;
	indices_high[44] = 24;
	indices_high[45] = 19;

	this->indexbufferHigh->Unlock();
	/*/////////////////////////////*/

	/*Create indices for medium detail level*/
	this->g_pD3DDevice->CreateIndexBuffer(14*sizeof(WORD),D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &this->indexbufferMedium, NULL);
	WORD *indices_medium=NULL;
	this->indexbufferMedium->Lock( 0, 0, (void**)&indices_medium, 0 );
	//Row 1
	indices_medium[0] = 10;
	indices_medium[1] = 0;
	indices_medium[2] = 12;
	indices_medium[3] = 2;
	indices_medium[4] = 14;
	indices_medium[5] = 4;
	
	//Degenerating
	indices_medium[6] = 4;
	indices_medium[7] = 20;

	//Row 2
	indices_medium[8] = 20;
	indices_medium[9] = 10;
	indices_medium[10] = 22;
	indices_medium[11] = 12;
	indices_medium[12] = 24;
	indices_medium[13] = 14;
	this->indexbufferMedium->Unlock();

	/*Restitching indexbuffers*/
	/*Stitches on the left side*/
	this->g_pD3DDevice->CreateIndexBuffer(26*sizeof(WORD),D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &this->indexbufferMedium_stitchleft, NULL);
	WORD *indices_medium_stitchleft=NULL;
	this->indexbufferMedium_stitchleft->Lock( 0, 0, (void**)&indices_medium_stitchleft, 0 );
	//Row 1
	indices_medium_stitchleft[0] = 12;
	indices_medium_stitchleft[1] = 10;
	indices_medium_stitchleft[2] = 5;

	//Degenerating
	indices_medium_stitchleft[3] = 5;

	indices_medium_stitchleft[4] = 12;
	indices_medium_stitchleft[5] = 0;
	indices_medium_stitchleft[6] = 2;

	//Degenerating
	indices_medium_stitchleft[7] = 2;

	indices_medium_stitchleft[8] = 12;
	indices_medium_stitchleft[9] = 2;
	indices_medium_stitchleft[10] = 14;
	indices_medium_stitchleft[11] = 4;

	//Degenerating
	indices_medium_stitchleft[12] = 4;
	indices_medium_stitchleft[13] = 22;

	//Row 2
	indices_medium_stitchleft[14] = 22;
	indices_medium_stitchleft[15] = 20;
	indices_medium_stitchleft[16] = 15;

	//Degenerating
	indices_medium_stitchleft[17] = 15;

	indices_medium_stitchleft[18] = 22;
	indices_medium_stitchleft[19] = 10;
	indices_medium_stitchleft[20] = 12;

	//Degenerating
	indices_medium_stitchleft[21] = 12;

	indices_medium_stitchleft[22] = 22;
	indices_medium_stitchleft[23] = 12;
	indices_medium_stitchleft[24] = 24;
	indices_medium_stitchleft[25] = 14;

	this->indexbufferMedium_stitchleft->Unlock();
	/*/////////////////////////////*/
	/*Stitches on the top left side*/
	this->g_pD3DDevice->CreateIndexBuffer(32*sizeof(WORD),D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &this->indexbufferMedium_stitchtopleft, NULL);
	WORD *indices_medium_stitchtopleft=NULL;
	this->indexbufferMedium_stitchtopleft->Lock( 0, 0, (void**)&indices_medium_stitchtopleft, 0 );
	//Row 1
	indices_medium_stitchtopleft[0] = 12;
	indices_medium_stitchtopleft[1] = 10;
	indices_medium_stitchtopleft[2] = 5;

	////Degenerating
	indices_medium_stitchtopleft[3] = 5;

	indices_medium_stitchtopleft[4] = 12;
	indices_medium_stitchtopleft[5] = 0;
	indices_medium_stitchtopleft[6] = 1;
	
	////Degenerating
	indices_medium_stitchtopleft[7] = 1;

	indices_medium_stitchtopleft[8] = 12;
	indices_medium_stitchtopleft[9] = 1;
	indices_medium_stitchtopleft[10] = 2;

	indices_medium_stitchtopleft[11] = 2;

	indices_medium_stitchtopleft[12] = 12;
	indices_medium_stitchtopleft[13] = 2;
	indices_medium_stitchtopleft[14] = 14;
	indices_medium_stitchtopleft[15] = 3;
	indices_medium_stitchtopleft[16] = 4;

	////Degenerating
	indices_medium_stitchtopleft[17] = 4;
	indices_medium_stitchtopleft[18] = 22;
	indices_medium_stitchtopleft[19] = 22;

	//Row 2
	indices_medium_stitchtopleft[20] = 22;
	indices_medium_stitchtopleft[21] = 20;
	indices_medium_stitchtopleft[22] = 15;

	//Degenerating
	indices_medium_stitchtopleft[23] = 15;

	indices_medium_stitchtopleft[24] = 22;
	indices_medium_stitchtopleft[25] = 10;
	indices_medium_stitchtopleft[26] = 12;

	//Degenerating
	indices_medium_stitchtopleft[27] = 12;

	indices_medium_stitchtopleft[28] = 22;
	indices_medium_stitchtopleft[29] = 12;
	indices_medium_stitchtopleft[30] = 24;
	indices_medium_stitchtopleft[31] = 14;

	this->indexbufferMedium_stitchtopleft->Unlock();
	/*/////////////////////////////*/
	/*Stitches on the bottom left side*/
	this->g_pD3DDevice->CreateIndexBuffer(41*sizeof(WORD),D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &this->indexbufferMedium_stitchbottomleft, NULL);
	WORD *indices_medium_stitchbottomleft=NULL;
	this->indexbufferMedium_stitchbottomleft->Lock( 0, 0, (void**)&indices_medium_stitchbottomleft, 0 );
	//Row 1
	indices_medium_stitchbottomleft[0] = 12;
	indices_medium_stitchbottomleft[1] = 10;
	indices_medium_stitchbottomleft[2] = 5;

	//Degenerating
	indices_medium_stitchbottomleft[3] = 5;

	indices_medium_stitchbottomleft[4] = 12;
	indices_medium_stitchbottomleft[5] = 0;
	indices_medium_stitchbottomleft[6] = 2;

	//Degenerating
	indices_medium_stitchbottomleft[7] = 2;

	indices_medium_stitchbottomleft[8] = 12;
	indices_medium_stitchbottomleft[9] = 2;
	indices_medium_stitchbottomleft[10] = 14;
	indices_medium_stitchbottomleft[11] = 4;

	//Degenerating
	indices_medium_stitchbottomleft[12] = 4;
	indices_medium_stitchbottomleft[13] = 21;

	//Row 2
	indices_medium_stitchbottomleft[14] = 21;
	indices_medium_stitchbottomleft[15] = 20;
	indices_medium_stitchbottomleft[16] = 15;

	//Degenerating
	indices_medium_stitchbottomleft[17] = 15;

	indices_medium_stitchbottomleft[18] = 21;
	indices_medium_stitchbottomleft[19] = 15;
	indices_medium_stitchbottomleft[20] = 22;
	indices_medium_stitchbottomleft[21] = 10;
	indices_medium_stitchbottomleft[22] = 12;

	//Degenerating
	indices_medium_stitchbottomleft[23] = 12;
	indices_medium_stitchbottomleft[24] = 22;

	indices_medium_stitchbottomleft[25] = 22;
	indices_medium_stitchbottomleft[26] = 23;
	indices_medium_stitchbottomleft[27] = 12;

	//Degenerating
	indices_medium_stitchbottomleft[28] = 12;
	
	indices_medium_stitchbottomleft[29] = 24;
	indices_medium_stitchbottomleft[30] = 23;

	//Degenerating
	indices_medium_stitchbottomleft[31] = 23;
	indices_medium_stitchbottomleft[32] = 24;

	indices_medium_stitchbottomleft[33] = 24;
	indices_medium_stitchbottomleft[34] = 12;
	indices_medium_stitchbottomleft[35] = 23;

	//Degenerating
	indices_medium_stitchbottomleft[36] = 23;
	indices_medium_stitchbottomleft[37] = 12;

	indices_medium_stitchbottomleft[38] = 12;
	indices_medium_stitchbottomleft[39] = 14;
	indices_medium_stitchbottomleft[40] = 24;

	this->indexbufferMedium_stitchbottomleft->Unlock();
	/*/////////////////////////////*/
	/*Stitches on the top side*/
	this->g_pD3DDevice->CreateIndexBuffer(24*sizeof(WORD),D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &this->indexbufferMedium_stitchtop, NULL);
	WORD *indices_stitchtop=NULL;
	this->indexbufferMedium_stitchtop->Lock( 0, 0, (void**)&indices_stitchtop, 0 );
	//Row 1
	indices_stitchtop[0] = 10;
	indices_stitchtop[1] = 0;
	indices_stitchtop[2] = 12;
	indices_stitchtop[3] = 1;
	indices_stitchtop[4] = 2;

	//Degenerating
	indices_stitchtop[5] = 2;
	indices_stitchtop[6] = 12;

	indices_stitchtop[7] = 12;
	indices_stitchtop[8] = 14;
	indices_stitchtop[9] = 2;
	indices_stitchtop[10] = 3;
	
	//Degenerating
	indices_stitchtop[11] = 3;
	indices_stitchtop[12] = 14;

	indices_stitchtop[13] = 14;
	indices_stitchtop[14] = 4;
	indices_stitchtop[15] = 3;

	//Degenerating
	indices_stitchtop[16] = 3;
	indices_stitchtop[17] = 20;

	//Row 2
	indices_stitchtop[18] = 20;
	indices_stitchtop[19] = 10;
	indices_stitchtop[20] = 22;
	indices_stitchtop[21] = 12;
	indices_stitchtop[22] = 24;
	indices_stitchtop[23] = 14;

	this->indexbufferMedium_stitchtop->Unlock();
	/*/////////////////////////////*/
	/*Stitches on the bottom side*/
	this->g_pD3DDevice->CreateIndexBuffer(24*sizeof(WORD),D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &this->indexbufferMedium_stitchbottom, NULL);
	WORD *indices_stitchbottom=NULL;
	this->indexbufferMedium_stitchbottom->Lock( 0, 0, (void**)&indices_stitchbottom, 0 );
	//Row 1
	indices_stitchbottom[0] = 10;
	indices_stitchbottom[1] = 0;
	indices_stitchbottom[2] = 12;
	indices_stitchbottom[3] = 2;
	indices_stitchbottom[4] = 14;
	indices_stitchbottom[5] = 4;
	
	//Degenerating
	indices_stitchbottom[6] = 4;
	indices_stitchbottom[7] = 20;

	//Row 2
	indices_stitchbottom[8] = 20;
	indices_stitchbottom[9] = 10;
	indices_stitchbottom[10] = 21;
	indices_stitchbottom[11] = 22;
	indices_stitchbottom[12] = 22;
	indices_stitchbottom[13] = 10;
	indices_stitchbottom[14] = 12;

	indices_stitchbottom[15] = 12;
	indices_stitchbottom[16] = 22;
	
	indices_stitchbottom[17] = 22;
	indices_stitchbottom[18] = 23;
	indices_stitchbottom[19] = 12;
	indices_stitchbottom[20] = 24;
	indices_stitchbottom[21] = 24;
	indices_stitchbottom[22] = 14;
	indices_stitchbottom[23] = 12;
	this->indexbufferMedium_stitchbottom->Unlock();
	/*/////////////////////////////*/
	/*Stitches on the right side*/
	this->g_pD3DDevice->CreateIndexBuffer(26*sizeof(WORD),D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &this->indexbufferMedium_stitchright, NULL);
	WORD *indices_stitchright=NULL;
	this->indexbufferMedium_stitchright->Lock( 0, 0, (void**)&indices_stitchright, 0 );
	//Row 1
	indices_stitchright[0] = 10;
	indices_stitchright[1] = 0;
	indices_stitchright[2] = 12;
	indices_stitchright[3] = 2;
	indices_stitchright[4] = 2;
	indices_stitchright[5] = 4;
	indices_stitchright[6] = 9;
	indices_stitchright[7] = 9;
	indices_stitchright[8] = 2;
	indices_stitchright[9] = 14;
	indices_stitchright[10] = 12;
	
	//Degenerating
	indices_stitchright[11] = 12;
	indices_stitchright[12] = 20;

	//Row 2
	indices_stitchright[13] = 20;
	indices_stitchright[14] = 22;
	indices_stitchright[15] = 10;
	indices_stitchright[16] = 12;

	//Degenerating
	indices_stitchright[17] = 12;
	indices_stitchright[18] = 14;

	indices_stitchright[19] = 14;
	indices_stitchright[20] = 12;
	indices_stitchright[21] = 19;
	indices_stitchright[22] = 24;
	//Degenerating
	indices_stitchright[23] = 24;

	indices_stitchright[24] = 12;
	indices_stitchright[25] = 22;

	this->indexbufferMedium_stitchright->Unlock();
	/*/////////////////////////////*/
	/*Stitches on the top right side*/
	this->g_pD3DDevice->CreateIndexBuffer(32*sizeof(WORD),D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &this->indexbufferMedium_stitchtopright, NULL);
	WORD *indices_stitchtopright=NULL;
	this->indexbufferMedium_stitchtopright->Lock( 0, 0, (void**)&indices_stitchtopright, 0 );
	//Row 1
	indices_stitchtopright[0] = 10;
	indices_stitchtopright[1] = 0;
	indices_stitchtopright[2] = 12;
	indices_stitchtopright[3] = 1;
	indices_stitchtopright[4] = 2;
	indices_stitchtopright[5] = 2;
	indices_stitchtopright[6] = 12;
	indices_stitchtopright[7] = 14;
	indices_stitchtopright[8] = 14;
	indices_stitchtopright[9] = 2;
	indices_stitchtopright[10] = 9;
	indices_stitchtopright[11] = 3;
	indices_stitchtopright[12] = 3;
	indices_stitchtopright[13] = 4;
	indices_stitchtopright[14] = 9;

	//Degenerating
	indices_stitchtopright[15] = 9;
	indices_stitchtopright[16] = 10;

	//Row 2
	indices_stitchtopright[17] = 10;
	indices_stitchtopright[18] = 20;
	indices_stitchtopright[19] = 22;
	indices_stitchtopright[20] = 22;
	indices_stitchtopright[21] = 10;
	indices_stitchtopright[22] = 12;

	//Degenerating
	indices_stitchtopright[23] = 12;
	indices_stitchtopright[24] = 14;

	indices_stitchtopright[25] = 14;
	indices_stitchtopright[26] = 12;
	indices_stitchtopright[27] = 19;
	indices_stitchtopright[28] = 24;
	//Degenerating
	indices_stitchtopright[29] = 24;

	indices_stitchtopright[30] = 12;
	indices_stitchtopright[31] = 22;

	this->indexbufferMedium_stitchtopright->Unlock();
	/*/////////////////////////////*/
	/*Stitches on the bottom right side*/
	this->g_pD3DDevice->CreateIndexBuffer(30*sizeof(WORD),D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &this->indexbufferMedium_stitchbottomright, NULL);
	WORD *indices_stitchbottomright=NULL;
	this->indexbufferMedium_stitchbottomright->Lock( 0, 0, (void**)&indices_stitchbottomright, 0 );
	//Row 1
	indices_stitchbottomright[0] = 10;
	indices_stitchbottomright[1] = 0;
	indices_stitchbottomright[2] = 12;
	indices_stitchbottomright[3] = 2;
	indices_stitchbottomright[4] = 2;
	indices_stitchbottomright[5] = 4;
	indices_stitchbottomright[6] = 9;
	indices_stitchbottomright[7] = 9;
	indices_stitchbottomright[8] = 2;
	indices_stitchbottomright[9] = 14;
	indices_stitchbottomright[10] = 12;
	//Degenerating
	indices_stitchbottomright[11] = 12;
	
	//Row 2
	indices_stitchbottomright[12] = 10;
	indices_stitchbottomright[13] = 22;
	indices_stitchbottomright[14] = 21;
	indices_stitchbottomright[15] = 21;
	indices_stitchbottomright[16] = 10;
	indices_stitchbottomright[17] = 20;
	
	//Degenerating
	indices_stitchbottomright[18] = 20;
	indices_stitchbottomright[19] = 12;

	indices_stitchbottomright[20] = 12;
	indices_stitchbottomright[21] = 14;
	indices_stitchbottomright[22] = 19;
	indices_stitchbottomright[23] = 19;
	indices_stitchbottomright[24] = 12;
	indices_stitchbottomright[25] = 24;
	indices_stitchbottomright[26] = 23;
	indices_stitchbottomright[27] = 23;
	indices_stitchbottomright[28] = 12;
	indices_stitchbottomright[29] = 22;
	this->indexbufferMedium_stitchbottomright->Unlock();
	/*/////////////////////////////*/
	/*Create indices for low detail level*/
	this->g_pD3DDevice->CreateIndexBuffer(4*sizeof(WORD),D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &this->indexbufferLow, NULL);
	WORD *indices_low=NULL;
	this->indexbufferLow->Lock( 0, 0, (void**)&indices_low, 0 );
	//Only 1 quad
	indices_low[0] = 20;
	indices_low[1] = 0;
	indices_low[2] = 24;
	indices_low[3] = 4;
	this->indexbufferLow->Unlock();

	/*Restitching indexbuffers*/
	/*Left*/
	this->g_pD3DDevice->CreateIndexBuffer(5*sizeof(WORD),D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &this->indexbufferLow_stitchleft, NULL);
	WORD *indices_low_stitchleft=NULL;
	this->indexbufferLow_stitchleft->Lock( 0, 0, (void**)&indices_low_stitchleft, 0 );
	indices_low_stitchleft[0] = 20;
	indices_low_stitchleft[1] = 10;
	indices_low_stitchleft[2] = 24;
	indices_low_stitchleft[3] = 0;
	indices_low_stitchleft[4] = 4;
	this->indexbufferLow_stitchleft->Unlock();

	/*Top Left*/
	this->g_pD3DDevice->CreateIndexBuffer(10*sizeof(WORD),D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &this->indexbufferLow_stitchtopleft, NULL);
	WORD *indices_low_stitchtopleft=NULL;
	this->indexbufferLow_stitchtopleft->Lock( 0, 0, (void**)&indices_low_stitchtopleft, 0 );
	indices_low_stitchtopleft[0] = 20;
	indices_low_stitchtopleft[1] = 10;
	indices_low_stitchtopleft[2] = 24;
	indices_low_stitchtopleft[3] = 0;
	indices_low_stitchtopleft[4] = 2;
	indices_low_stitchtopleft[5] = 2;
	indices_low_stitchtopleft[6] = 3;
	indices_low_stitchtopleft[7] = 2;
	indices_low_stitchtopleft[8] = 24;
	indices_low_stitchtopleft[9] = 4;
	this->indexbufferLow_stitchtopleft->Unlock();

	/*Bottom Left*/
	this->g_pD3DDevice->CreateIndexBuffer(6*sizeof(WORD),D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &this->indexbufferLow_stitchbottomleft, NULL);
	WORD *indices_low_stitchbottomleft=NULL;
	this->indexbufferLow_stitchbottomleft->Lock( 0, 0, (void**)&indices_low_stitchbottomleft, 0 );
	indices_low_stitchbottomleft[0] = 4;
	indices_low_stitchbottomleft[1] = 24;
	indices_low_stitchbottomleft[2] = 0;
	indices_low_stitchbottomleft[3] = 22;
	indices_low_stitchbottomleft[4] = 10;
	indices_low_stitchbottomleft[5] = 20;
	this->indexbufferLow_stitchbottomleft->Unlock();

	/*Top*/
	this->g_pD3DDevice->CreateIndexBuffer(5*sizeof(WORD),D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &this->indexbufferLow_stitchtop, NULL);
	WORD *indices_low_stitchtop=NULL;
	this->indexbufferLow_stitchtop->Lock( 0, 0, (void**)&indices_low_stitchtop, 0 );
	indices_low_stitchtop[0] = 20;
	indices_low_stitchtop[1] = 0;
	indices_low_stitchtop[2] = 24;
	indices_low_stitchtop[3] = 2;
	indices_low_stitchtop[4] = 4;
	this->indexbufferLow_stitchtop->Unlock();

	/*Bottom*/
	this->g_pD3DDevice->CreateIndexBuffer(5*sizeof(WORD),D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &this->indexbufferLow_stitchbottom, NULL);
	WORD *indices_low_stitchbottom=NULL;
	this->indexbufferLow_stitchbottom->Lock( 0, 0, (void**)&indices_low_stitchbottom, 0 );
	indices_low_stitchbottom[0] = 4;
	indices_low_stitchbottom[1] = 24;
	indices_low_stitchbottom[2] = 0;
	indices_low_stitchbottom[3] = 22;
	indices_low_stitchbottom[4] = 20;
	this->indexbufferLow_stitchbottom->Unlock();

	/*Right*/
	this->g_pD3DDevice->CreateIndexBuffer(5*sizeof(WORD),D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &this->indexbufferLow_stitchright, NULL);
	WORD *indices_low_stitchright=NULL;
	this->indexbufferLow_stitchright->Lock( 0, 0, (void**)&indices_low_stitchright, 0 );
	indices_low_stitchright[0] = 20;
	indices_low_stitchright[1] = 0;
	indices_low_stitchright[2] = 24;
	indices_low_stitchright[3] = 14;
	indices_low_stitchright[4] = 4;
	this->indexbufferLow_stitchright->Unlock();

	/*Top Right*/
	this->g_pD3DDevice->CreateIndexBuffer(6*sizeof(WORD),D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &this->indexbufferLow_stitchtopright, NULL);
	WORD *indices_low_stitchtopright=NULL;
	this->indexbufferLow_stitchtopright->Lock( 0, 0, (void**)&indices_low_stitchtopright, 0 );
	indices_low_stitchtopright[0] = 20;
	indices_low_stitchtopright[1] = 0;
	indices_low_stitchtopright[2] = 24;
	indices_low_stitchtopright[3] = 2;
	indices_low_stitchtopright[4] = 14;
	indices_low_stitchtopright[5] = 4;
	this->indexbufferLow_stitchtopright->Unlock();

	/*Bottom Right*/
	this->g_pD3DDevice->CreateIndexBuffer(8*sizeof(WORD),D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &this->indexbufferLow_stitchbottomright, NULL);
	WORD *indices_low_stitchbottomright=NULL;
	this->indexbufferLow_stitchbottomright->Lock( 0, 0, (void**)&indices_low_stitchbottomright, 0 );
	indices_low_stitchbottomright[0] = 20;
	indices_low_stitchbottomright[1] = 0;
	indices_low_stitchbottomright[2] = 22;
	indices_low_stitchbottomright[3] = 24;
	indices_low_stitchbottomright[4] = 24;
	indices_low_stitchbottomright[5] = 0;
	indices_low_stitchbottomright[6] = 14;
	indices_low_stitchbottomright[7] = 4;

	this->indexbufferLow_stitchbottomright->Unlock();
	/*/////////////////////////////*/
}

Vector Terrain::Collide(Vector v)
{
	return this->quadtree->GetMasterNode()->Collide(v);
}

Quadtree* Terrain::GetQuadtree()
{
	return this->quadtree;
}

void Terrain::CreateNoise()
{
	////Billow
	//module::Billow myModule;
	//myModule.SetOctaveCount(6);
	//myModule.SetFrequency(6);
	//myModule.SetSeed(40);
	//module::Billow myModule2;
	//myModule2.SetOctaveCount(6);
	//myModule2.SetFrequency(6);

	////Scale
	//module::ScaleBias flatModule1;
	//flatModule1.SetSourceModule(0, myModule);
	//flatModule1.SetScale(0.125/2);

	//module::Select selectModule1;
	//selectModule1.SetSourceModule(0, flatModule1);
	//selectModule1.SetBounds(5,1000);

	//module::ScaleBias flatModule2;
	//flatModule2.SetSourceModule(0, myModule2);
	//flatModule2.SetScale(0.125/2);
	//flatModule2.SetBias(-0.5);
	//
	////Final
	//module::Perlin terrainType;
	//terrainType.SetFrequency (2.5);
	//terrainType.SetPersistence (0.125);
	//terrainType.SetSeed(20);

	//module::Select finalTerrain;
	//finalTerrain.SetSourceModule (0, flatModule1);
	//finalTerrain.SetSourceModule (1, flatModule2);
	//finalTerrain.SetControlModule(terrainType);
	//finalTerrain.SetBounds (0.0, 1000.0);
	//finalTerrain.SetEdgeFalloff (0.50);

	module::Billow mountainTerrain;
	module::Billow baseFlatTerrain;
	baseFlatTerrain.SetFrequency (2.0);
	
	module::ScaleBias flatTerrain;
	flatTerrain.SetSourceModule (0, baseFlatTerrain);
	flatTerrain.SetScale(0.00125);
	flatTerrain.SetBias(-0.75);

	module::Perlin terrainType;
	terrainType.SetFrequency (0.5);
	terrainType.SetPersistence (0.125);
	terrainType.SetSeed(1884);

	module::Select terrainSelector;
	terrainSelector.SetSourceModule (0, flatTerrain);
	terrainSelector.SetSourceModule (1, mountainTerrain);
	terrainSelector.SetControlModule (terrainType);
	terrainSelector.SetBounds (0.0, 1000.0);
	terrainSelector.SetEdgeFalloff (0.1);
	
	module::Turbulence finalTerrain;
	finalTerrain.SetSourceModule (0, terrainSelector);
	finalTerrain.SetFrequency (2);
	finalTerrain.SetPower (0.125);

	noise::utils::NoiseMap heightMap;
	noise::utils::NoiseMapBuilderPlane heightMapBuilder;
	heightMap.SetSize(530,530);
	heightMapBuilder.SetSourceModule (finalTerrain);
	heightMapBuilder.SetDestNoiseMap (heightMap);
	heightMapBuilder.SetDestSize (530, 530);
	heightMapBuilder.SetBounds (0.0, 4.0, -8.0, -4.0);
	heightMapBuilder.Build ();

	noise::utils::RendererImage renderer;
    noise::utils::Image image;
	image.SetSize(530,530);
    renderer.SetSourceNoiseMap (heightMap);
    renderer.SetDestImage (image);
	renderer.Render ();
	noise::utils::WriterBMP writer;
	writer.SetSourceImage (image);
	writer.SetDestFilename ("tutorial.bmp");
	writer.WriteDestFile ();
	
	this->LoadBMP("tutorial.bmp");
	renderer.SetDestImage (image);
	renderer.ClearGradient ();
	//renderer.AddGradientPoint (-1.00, utils::Color (0, 225, 0, 255)); // dirt
	//renderer.AddGradientPoint (-0.55, utils::Color (0, 225, 0, 255)); // dirt
	//renderer.AddGradientPoint (-0.45, utils::Color (255, 0, 0, 255)); // grass

	renderer.AddGradientPoint (-1.00, utils::Color ( 160, 32,   0, 255)); // grass
	renderer.AddGradientPoint (-0.25, utils::Color (124, 224,   0, 255)); // dirt
	renderer.AddGradientPoint ( 0.25, utils::Color (32, 128, 128, 255)); // rock
	renderer.AddGradientPoint ( 1.00, utils::Color (124, 0, 255, 255)); // snow
	renderer.Render ();
	writer.SetSourceImage (image);
	writer.SetDestFilename ("tutorialColor.bmp");
	writer.WriteDestFile ();
	
	this->texture_map = Kernel::Instance()->GetResourceManager()->GetTexture("tutorialColor.bmp");

   noise::utils::RendererNormalMap normalMapRenderer;
   noise::utils::Image normalImage;
   normalImage.SetSize(530,530);
   normalMapRenderer.SetSourceNoiseMap(heightMap);
   normalMapRenderer.SetDestImage(normalImage);
   normalMapRenderer.SetBumpHeight(6);
   normalMapRenderer.Render();                   
   noise::utils::WriterBMP normalMapWriter;
   normalMapWriter.SetSourceImage (normalImage);
   normalMapWriter.SetDestFilename ("tutorialNormal.bmp");
   normalMapWriter.WriteDestFile ();
   this->texture_normal = Kernel::Instance()->GetResourceManager()->GetTexture("tutorialNormal.bmp");
}

Patch* Terrain::GetPatchByIndex(int y, int x) const
{
	return this->patches[y][x];
}

const int Terrain::NumPatchesY() const
{
	return this->patches.size();
}

const int Terrain::NumPatchesX() const
{
	return this->patches[0].size();
}

Terrain::~Terrain()
{
	this->t_buffer->Release();
	this->waterbuffer->Release();
	delete this->matWorldInverseTransponse;
	delete this->matWorldInverse;
	delete this->worldViewProj;
	delete this->quadtree;
	ResourceManager* resourceManager = Kernel::Instance()->GetResourceManager();
	resourceManager->DeleteTexture(this->texture_map->GetPath());
	resourceManager->DeleteTexture(this->currentSet.Texture1->GetPath());
	resourceManager->DeleteTexture(this->currentSet.alt_Texture1->GetPath());
	resourceManager->DeleteTexture(this->currentSet.Texture2->GetPath());
	resourceManager->DeleteTexture(this->currentSet.Texture3->GetPath());
	resourceManager->DeleteTexture(this->texture_water1->GetPath());
	resourceManager->DeleteTexture(this->texture_water2->GetPath());
		
	//Release Indexbuffers
	this->indexbufferHigh->Release();
	this->indexbufferMedium->Release();
	this->indexbufferLow->Release();

	this->indexbufferMedium_stitchleft->Release();
	this->indexbufferMedium_stitchtopleft->Release();
	this->indexbufferMedium_stitchbottomleft->Release();
	this->indexbufferMedium_stitchtop->Release();
	this->indexbufferMedium_stitchbottom->Release();
	this->indexbufferMedium_stitchright->Release();
	this->indexbufferMedium_stitchtopright->Release();
	this->indexbufferMedium_stitchbottomright->Release();

	this->indexbufferLow_stitchleft->Release();
	this->indexbufferLow_stitchtopleft->Release();
	this->indexbufferLow_stitchbottomleft->Release();
	this->indexbufferLow_stitchtop->Release();
	this->indexbufferLow_stitchbottom->Release();
	this->indexbufferLow_stitchright->Release();
	this->indexbufferLow_stitchtopright->Release();
	this->indexbufferLow_stitchbottomright->Release();

	for(unsigned int a = 0; a < this->verts2.size(); a++)
	{
		for(unsigned int b = 0; b < this->verts2.size(); b++)
		{
			delete this->verts2[a][b];
		}
	}
}