#include "Terrain.h"
#include "../Core/Kernel.h"
#include "noiseutils.h"


Terrain::Terrain()
{
	this->worldViewProj = new D3DXMATRIX();
	this->matWorldInverse = new D3DXMATRIX();
	this->matWorldInverseTransponse = new D3DXMATRIX();

	this->index_buffer_size = 0;

	ResourceManager* resourceManager = Kernel::Instance()->GetResourceManager();
	this->greenWorld.Texture1 = resourceManager->GetTexture("Content/Textures/Terrain/Green World/Grass0027_13_S.jpg");
	this->greenWorld.Texture2 = resourceManager->GetTexture("Content/Textures/Terrain/Green World/sandtexture.jpg");
	this->greenWorld.Texture3 = resourceManager->GetTexture("Content/Textures/Terrain/Green World/Cliffs0074_2_S.jpg");
	this->greenWorld.Texture4 = resourceManager->GetTexture("Content/Textures/Terrain/Green World/Concrete tile.jpg");
	this->greenWorld.debug = resourceManager->GetTexture("Content/Textures/Terrain/devtexture.bmp");
	this->greenWorld.water = resourceManager->GetTexture("Content/Textures/Terrain/2987042594_e9968cd001.jpg");
	this->greenWorld.water1 = resourceManager->GetTexture("Content/Textures/Terrain/940.jpg");
	this->currentSet = this->greenWorld;
	this->size = 0;
}

//*------------------------------------*
//| Creates terrain geometry.          |
//*------------------------------------*
bool Terrain::Create(unsigned int size)
{
	this->size = size;
	this->CreateNoise();

	this->terrain_shader = Kernel::Instance()->GetResourceManager()->GetShader("Content/Shaders/TerrainShaderNew.fx");
	this->water_shader = Kernel::Instance()->GetResourceManager()->GetShader("Content/Shaders/WaterNew.fx");
	Logger::Instance()->Log("Creating Vertices..", Info);
	bool success = true;

	vector< vector< Vertex* > > vertices;
	this->color_map = Util::BitmapToColormap( "colormap.bmp" );
	this->normal_map = Util::BitmapToColormap( "normalmap.bmp" );

	//Create vertices in a 2d grid for the terrain.
	for( unsigned int a = 0; a < size; a++ )
	{
		vector< Vertex* > column;
		for( unsigned int b = 0; b < size; b++ )
		{
			column.push_back( new Vertex ( ( 1.0f * b ), this->heightmap[ b ][ a ] * 0.06, ( -1.0f * a ), this->color_map[ b ][ a ].r, this->color_map[ b ][ a ].g, this->color_map[ b ][ a ].b, this->normal_map[ b ][ a ].r, this->normal_map[ b ][ a ].g, this->normal_map[ b ][ a ].b, b, a ) );
		}
		vertices.push_back( column );
	}
	this->vertices = vertices;

	this->vertex_buffer_terrain = this->CreateVertexBuffer( vertices, size );
	this->vertex_buffer_terrain_size = size * size;

	vector< vector< Vertex* > > vertices_water;
	//Create vertices in a 2d grid for the water.
	for( unsigned int a = 0; a < size; a++ )
	{
		vector< Vertex* > column;
		for( unsigned int b = 0; b < size; b++ )
		{
			column.push_back( new Vertex ( ( 1.0f * b ), 2, ( -1.0f * a ), 255, 255, 255, 0, 0, 0, b, a ) );
		}
		vertices_water.push_back( column );
	}
	this->vertex_buffer_water = this->CreateVertexBuffer( vertices_water, size );

	//Calculate size of index buffer.
	this->index_buffer_size = ( ( size * size ) * 2 ) - 4;
	if( !FAILED( Kernel::Instance()->GetRenderer()->GetDevice()->CreateIndexBuffer( this->index_buffer_size * sizeof( unsigned short ), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &this->index_buffer, NULL ) ) )
	{
		unsigned short *indices = NULL;
	
		this->index_buffer->Lock( 0, this->index_buffer_size, (void**)&indices, 0 );
		int current_index = 0;
		int current_vertex = 0;

		//Loop through the grid of the vertices, start at the second row and ignore the last row.
		for( int a = 0; a < this->size-1; a++ )
		{
			for( int b = 0; b < this->size; b++ )
			{
				//Set a bottom and top index in a saw like pattern. 
				indices[ 0 + current_index * 2 ] = this->size + current_vertex;
				indices[ 1 + current_index * 2 ] = 0 + current_vertex;
				current_index++;
				current_vertex++;

				//Check if the end of the column is reached to set a degenerated triangle so there won't be a triangle towards the next column.
				//Ignore the last column, since it won't have to jump to a new column.
				if( current_vertex % this->size == 0 && a < this->size-2 )
				{
					indices[ 0 + current_index * 2 ] = indices[ ( 0 + current_index * 2 ) - 1 ];
					indices[ 1 + current_index * 2 ] = current_vertex + this->size;
					current_index++;
				}
				
			}
		}
		this->index_buffer->Unlock();
	}
	else
	{
		success = false;
	}

	return success;
}

void Terrain::Render()
{
	//Kernel::Instance()->GetRenderer()->GetDevice()->SetRenderState( D3DRS_FILLMODE,D3DFILL_WIREFRAME );

	Kernel::Instance()->GetRenderer()->GetDevice()->SetTransform( D3DTS_WORLD,&this->matWorld );
	*this->worldViewProj = (this->matWorld * Kernel::Instance()->GetRenderer()->GetViewMatrix() * Kernel::Instance()->GetRenderer()->GetProjectionMatrix());
	D3DXMATRIX view = Kernel::Instance()->GetRenderer()->GetViewMatrix();
	D3DXMATRIX projection = Kernel::Instance()->GetRenderer()->GetProjectionMatrix();

	D3DXMatrixTranspose(this->matWorldInverseTransponse, &this->matWorld);
	D3DXMatrixInverse(this->matWorldInverseTransponse, NULL, matWorldInverseTransponse);

	
	Kernel::Instance()->GetRenderer()->GetDevice()->SetTexture(0,this->currentSet.Texture1->GetD3DTexture() );
	Kernel::Instance()->GetRenderer()->GetDevice()->SetTexture(1,this->currentSet.Texture2->GetD3DTexture() );
	Kernel::Instance()->GetRenderer()->GetDevice()->SetTexture(2,this->currentSet.Texture3->GetD3DTexture() );

	//this->g_pD3DDevice->SetTexture(5,this->currentSet.alt_Texture1->GetD3DTexture() );
	Kernel::Instance()->GetRenderer()->GetDevice()->SetTexture(3,this->currentSet.Texture4->GetD3DTexture() );

	UINT passes;
	this->terrain_shader->GetD3DEffect()->SetFloat( "time", timeGetTime());	
	Vector camera_position = Kernel::Instance()->GetRenderer()->GetCamera()->GetPosition();
	this->terrain_shader->GetD3DEffect()->SetVector( "CameraPosition", &D3DXVECTOR4( camera_position.x, camera_position.y, camera_position.z, 1 ) );
	this->terrain_shader->GetD3DEffect()->SetMatrix( "wvp", this->worldViewProj);
	this->terrain_shader->GetD3DEffect()->SetMatrix( "itw", this->matWorldInverseTransponse);
	this->terrain_shader->GetD3DEffect()->Begin(&passes,0);
	this->terrain_shader->GetD3DEffect()->BeginPass(0);
	this->terrain_shader->GetD3DEffect()->Begin(&passes,0);

	Kernel::Instance()->GetRenderer()->GetDevice()->SetFVF(CUSTOMFVF);
	Kernel::Instance()->GetRenderer()->GetDevice()->SetStreamSource(0, this->vertex_buffer_terrain, 0, sizeof(CUSTOMVERTEX));
	Kernel::Instance()->GetRenderer()->GetDevice()->SetIndices(this->index_buffer);
	Kernel::Instance()->GetRenderer()->GetDevice()->DrawIndexedPrimitive( D3DPT_TRIANGLESTRIP,0,0,this->vertex_buffer_terrain_size,0,this->index_buffer_size - 2 );
	
	this->terrain_shader->GetD3DEffect()->EndPass();
	this->terrain_shader->GetD3DEffect()->End();

	//Water HAX HAX HAX
	Kernel::Instance()->GetRenderer()->GetDevice()->SetTexture(0,this->currentSet.water->GetD3DTexture() );
	Kernel::Instance()->GetRenderer()->GetDevice()->SetTexture(1,this->currentSet.water1->GetD3DTexture() );
	UINT passes2;
	this->water_shader->GetD3DEffect()->SetFloat( "time", timeGetTime());
	this->water_shader->GetD3DEffect()->SetVector( "CameraPosition", &D3DXVECTOR4( camera_position.x, camera_position.y, camera_position.z, 1 ) );
	this->water_shader->GetD3DEffect()->SetMatrix( "wvp", this->worldViewProj);
	this->water_shader->GetD3DEffect()->SetMatrix( "itw", this->matWorldInverseTransponse);
	this->water_shader->GetD3DEffect()->Begin(&passes2,0);
	this->water_shader->GetD3DEffect()->BeginPass(0);
	this->water_shader->GetD3DEffect()->Begin(&passes2,0);
	Kernel::Instance()->GetRenderer()->GetDevice()->SetStreamSource(0, this->vertex_buffer_water, 0, sizeof(CUSTOMVERTEX));
	Kernel::Instance()->GetRenderer()->GetDevice()->DrawIndexedPrimitive( D3DPT_TRIANGLESTRIP,0,0,this->vertex_buffer_terrain_size,0,this->index_buffer_size - 2 );
	this->water_shader->GetD3DEffect()->EndPass();
	this->water_shader->GetD3DEffect()->End();

		
	Node::Render();
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
	baseFlatTerrain.SetSeed( 4426);

	module::ScaleBias flatTerrain;
	flatTerrain.SetSourceModule (0, baseFlatTerrain);
	flatTerrain.SetScale(0.00125);
	flatTerrain.SetBias(-0.75);

	module::Perlin terrainType;
	terrainType.SetFrequency (0.5);
	terrainType.SetPersistence (0.125);
	terrainType.SetSeed(2678);

	module::Select terrainSelector;
	terrainSelector.SetSourceModule (0, flatTerrain);
	terrainSelector.SetSourceModule (1, mountainTerrain);
	terrainSelector.SetControlModule (terrainType);
	terrainSelector.SetBounds (-100.0, 3000.0);
	terrainSelector.SetEdgeFalloff (0.4);

	module::Turbulence finalTerrain;
	finalTerrain.SetSourceModule (0, terrainSelector);
	finalTerrain.SetFrequency (2);
	finalTerrain.SetPower (0.125);
	finalTerrain.SetSeed( 65426 );

	noise::utils::NoiseMap heightMap;
	noise::utils::NoiseMapBuilderPlane heightMapBuilder;
	heightMap.SetSize( this->size,this->size );
	heightMapBuilder.SetSourceModule (finalTerrain);
	heightMapBuilder.SetDestNoiseMap (heightMap);
	heightMapBuilder.SetDestSize ( this->size, this->size );
	heightMapBuilder.SetBounds (4.0, 8.0, 3.0, 7.0);
	heightMapBuilder.Build ();

	noise::utils::RendererImage renderer;
    noise::utils::Image image;
	image.SetSize( this->size, this->size );
    renderer.SetSourceNoiseMap (heightMap);
    renderer.SetDestImage (image);
	renderer.Render ();
	noise::utils::WriterBMP writer;
	writer.SetSourceImage (image);
	writer.SetDestFilename ("heightmap.bmp");
	writer.WriteDestFile ();

	//this->LoadBMP("tutorial.bmp");
	this->heightmap = Util::BitmapToHeightmap( "heightmap.bmp" );
	renderer.SetDestImage (image);
	renderer.ClearGradient ();
	//renderer.AddGradientPoint (-1.00, utils::Color (0, 225, 0, 255)); // dirt
	//renderer.AddGradientPoint (-0.55, utils::Color (0, 225, 0, 255)); // dirt
	//renderer.AddGradientPoint (-0.45, utils::Color (255, 0, 0, 255)); // grass

	renderer.AddGradientPoint ( -1.00, utils::Color ( 0, 225,   0, 255 ) ); // grass
	renderer.AddGradientPoint ( -0.25, utils::Color ( 160, 32,   0, 255 ) ); // dirt
	renderer.AddGradientPoint ( 0.25, utils::Color ( 32, 128, 128, 255 ) ); // rock
	renderer.AddGradientPoint ( 1.00, utils::Color ( 50, 0, 255, 255 ) ); // snow
	renderer.Render ();
	writer.SetSourceImage (image);
	writer.SetDestFilename ("colormap.bmp");
	writer.WriteDestFile ();

	noise::utils::RendererNormalMap normalMapRenderer;
	noise::utils::Image normalImage;
	normalImage.SetSize( this->size, this->size );
	normalMapRenderer.SetSourceNoiseMap(heightMap);
	normalMapRenderer.SetDestImage(normalImage);
	normalMapRenderer.SetBumpHeight(6);
	normalMapRenderer.Render();                   
	noise::utils::WriterBMP normalMapWriter;
	normalMapWriter.SetSourceImage (normalImage);
	normalMapWriter.SetDestFilename ("normalmap.bmp");
	normalMapWriter.WriteDestFile ();

}

Vector Terrain::Collide( Vector position )
{
	//Find the nearest vertex on the top left of the current position.
	int x = static_cast<int>( position.x );
	int y = static_cast<int>( -position.z );

	//Get the 4 vertices closest to the current position.
	Vector Topleft = this->vertices[ y ][ x ]->GetPosition();
	Vector Topright = this->vertices[ y ][ x + 1 ]->GetPosition();
	Vector Bottomleft = this->vertices[ y + 1][ x ]->GetPosition();
	Vector Bottomright = this->vertices[ y + 1][ x + 1]->GetPosition();

	float minX = Topleft.x; //0%
	float maxX = Topright.x; //100%
	float percentX = ( ( ( position.x - minX) / ( maxX - minX ) ) ) * 100; 

	float minZ = Topright.z; //0%
	float maxZ = Bottomright.z; //100%
	float percentZ = ( ( ( position.z - minZ ) / ( maxZ - minZ ) ) ) * 100; 

	float HeightTL = Topleft.y;
	float HeightTR = Topright.y;
	float HeightBL = Bottomleft.y;
	float HeightBR = Bottomright.y;

	float heightTLTR = Math::Inst()->LinearInterpolate( HeightTL, HeightTR, percentX / 100 );
	float heightBLBR = Math::Inst()->LinearInterpolate( HeightBL, HeightBR, percentX / 100);
	float Xlerp = Math::Inst()->LinearInterpolate( heightTLTR, heightBLBR, percentZ / 100);
	float heightTLBL = Math::Inst()->LinearInterpolate( HeightTL, HeightBL, percentZ / 100);
	float heightTRBR = Math::Inst()->LinearInterpolate( HeightTR, HeightBR, percentZ / 100);
	float Zlerp = Math::Inst()->LinearInterpolate( heightTLBL, heightTRBR, percentX / 100);
	float final = ( Xlerp + Zlerp ) / 2;
	Vector newPosition = Vector( position.x, final, position.z );

	return newPosition;
}

LPDIRECT3DVERTEXBUFFER9 Terrain::CreateVertexBuffer( vector< vector< Vertex* > > vertices, int terrain_size )
{
	LPDIRECT3DVERTEXBUFFER9 new_buffer;
	//Creates the vertex buffer and copies the 1d vertices array to it.
	if( !FAILED( Kernel::Instance()->GetRenderer()->GetDevice()->CreateVertexBuffer( ( terrain_size * terrain_size ) * sizeof( CUSTOMVERTEX ), D3DUSAGE_WRITEONLY, CUSTOMFVF, D3DPOOL_MANAGED, &new_buffer, NULL ) ) )
	{
		CUSTOMVERTEX *vertices_fvf=NULL;

		new_buffer->Lock( 0, this->vertex_buffer_terrain_size, (void**)&vertices_fvf, 0 );

		//Copy the vertices to an array suitable for the vertex buffer.
		int i = 0;
		for( int a = 0; a < vertices.size(); a++)
		{
			for( int b = 0; b < vertices[ a ].size(); b++)
			{
				vertices_fvf[ i ] = *vertices[ a ][ b ]->GetCustomVertex();
				i++;
			}
		}
		new_buffer->Unlock();
	}
	else
	{
		new_buffer = NULL;
	}
	return new_buffer;
}

Shader* Terrain::GetTerrainShader()
{
	return this->terrain_shader;
}

Terrain::~Terrain()
{
	this->vertex_buffer_terrain->Release();
	this->index_buffer->Release();
}