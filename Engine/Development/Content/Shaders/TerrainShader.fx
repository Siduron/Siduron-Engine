texture Texturemap;
texture Detailtexture1;
texture Detailtexture2;
texture Lava;
texture Lightmap;
texture Normalmap;
texture Alphamap_detail1;
texture Alphamap_detail2;
texture Alphamap_lava;
float time;
int size = 16;

sampler2D TextureMapSampler =
sampler_state
{
    Texture = <Texturemap>;
    AddressU = Wrap;
    AddressV = Wrap;
    MinFilter = Point;
    MagFilter = Linear;
    MipFilter = Linear;
};

sampler2D DetailtextureSampler1 =
sampler_state
{
    Texture = <Detailtexture1>;
    AddressU = Wrap;
    AddressV = Wrap;
    MinFilter = Point;
    MagFilter = Linear;
    MipFilter = Linear;
	
	
};

sampler2D DetailtextureSampler2 =
sampler_state
{
    Texture = <Detailtexture2>;
    AddressU = Wrap;
    AddressV = Wrap;
    MinFilter = Point;
    MagFilter = Linear;
    MipFilter = Linear;
	
	
};

sampler2D Lavasampler =
sampler_state
{
    Texture = <Lava>;
    AddressU = Wrap;
    AddressV = Wrap;
    MinFilter = Point;
    MagFilter = Linear;
    MipFilter = Linear;
	
	
};

sampler2D LightmapSampler =
sampler_state
{
    Texture = <Lightmap>;
    AddressU = Wrap;
    AddressV = Wrap;
    MinFilter = Point;
    MagFilter = Linear;
    MipFilter = Linear;
	
	
};

sampler2D NormalmapSampler =
sampler_state
{
    Texture = <Normalmap>;
    AddressU = Wrap;
    AddressV = Wrap;
    MinFilter = Point;
    MagFilter = Linear;
    MipFilter = Linear;
	
	
};

sampler2D AlphamapSampler1 =
sampler_state
{
    Texture = <Alphamap_detail1>;
    AddressU = Wrap;
    AddressV = Wrap;
    MinFilter = Point;
    MagFilter = Linear;
    MipFilter = Linear;
	
	
};

sampler2D AlphamapSampler2 =
sampler_state
{
    Texture = <Alphamap_detail2>;
    AddressU = Wrap;
    AddressV = Wrap;
    MinFilter = Point;
    MagFilter = Linear;
    MipFilter = Linear;
	
	
};

sampler2D LavaAlphamapSampler =
sampler_state
{
    Texture = <Alphamap_lava>;
    AddressU = Wrap;
    AddressV = Wrap;
    MinFilter = Point;
    MagFilter = Linear;
    MipFilter = Linear;
	
	
};

float4 Detail( float2 Tex : TEXCOORD0 ) : COLOR0
{
    float4 colorTexturemap;
    float4 colorDetailtextureLarge;
    float4 colorDetailtextureSmall1;
    float4 colorDetailtextureSmall2;
    float4 colorLava;
    float4 colorLightmap;
    float4 colorNormalmap;
    float4 colorAlphamap_detail1;
    float4 colorAlphamap_detail2;
	float4 colorAlphamap_lava;
	
    colorTexturemap = tex2D( TextureMapSampler, Tex.xy/(32*size) );
    colorAlphamap_detail1 = tex2D( AlphamapSampler1, Tex.xy/(32*size) );
    colorAlphamap_detail2 = tex2D( AlphamapSampler2, Tex.xy/(32*size) );
    colorAlphamap_lava = tex2D( LavaAlphamapSampler, Tex.xy/(32*size) );
    
    colorDetailtextureLarge = tex2D( DetailtextureSampler1, Tex.xy*32 );
    //colorDetailtextureSmall1 = tex2D( DetailtextureSampler1, Tex.xy*128 );
    colorDetailtextureSmall1 = tex2D( DetailtextureSampler1, Tex.xy/2);
    colorDetailtextureSmall2 = tex2D( DetailtextureSampler2, Tex.xy/2);
    colorLava = tex2D( Lavasampler, (Tex.xy*64)-time/10000 );
    colorNormalmap = tex2D( NormalmapSampler, Tex.xy*128 );
	
   // float4 details = lerp(colorDetailtextureSmall1, colorDetailtextureSmall2,0.4);
	float4 details = colorDetailtextureSmall1;
	
    colorLightmap = tex2D( LightmapSampler, Tex.xy/(32*size) );
  	//float4 lightColor = (colorTexturemap * ((colorDetailtextureSmall1*colorAlphamap_detail1) + (colorDetailtextureSmall2*colorAlphamap_detail2) + (colorLava*colorAlphamap_lava))* colorLightmap*3) ;
	float4 lightColor = (colorTexturemap * ((colorDetailtextureSmall1*colorAlphamap_detail1) + (colorDetailtextureSmall2*colorAlphamap_detail2) + (colorLava*colorAlphamap_lava))) ;

    //float4 bumpColor = lightColor* dot(1.0*(colorNormalmap-0.2), 1.0);
	return lightColor;
}

struct VS_OUTPUT
{
  float4 Pos  : POSITION;
};


VS_OUTPUT VS(float4 Pos  : POSITION)
{
  VS_OUTPUT Out = (VS_OUTPUT)0; 

  
  return Out;
}
technique D3D
<
   
>
{
    pass p0
    {
        VertexShader = null;
        PixelShader = compile ps_2_0 Detail();
        ZEnable = TRUE;
    }
}
