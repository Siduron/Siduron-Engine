float4x4 wvp : WORLDVIEWPROJECTION;
float4x4 itw : WorldInverseTranspose;
float atmosphere = 1;

float AmbientIntensity = 0.0;
float4 AmbientColor : AMBIENT = float4(.5,.5,.5,1);

float DiffuseIntensity = 2.5;
float4 DiffuseColor : Diffuse = float4(1,1,1,1);

float4 SpecularColor : Specular = float4(1,1,1,1);
float SpecularIntensity : Scalar = 1.0;

float4 CameraPosition : CameraPosition;
float3 LightDirection : Direction = float3(1,0.5,0);

int size = 8;

sampler2D ColormapSampler : register(s0) =
sampler_state
{
    AddressU = Wrap;
    AddressV = Wrap;
    MinFilter = Linear;
    MagFilter = Linear;
    MipFilter = Linear;
};
sampler2D TextureSampler1 : register(s1) =
sampler_state
{
    AddressU = Wrap;
    AddressV = Wrap;
    MinFilter = Linear;
    MagFilter = Linear;
    MipFilter = Linear;
};
sampler2D TextureSampler2 : register(s2) =
sampler_state
{
    AddressU = Wrap;
    AddressV = Wrap;
    MinFilter = Linear;
    MagFilter = Linear;
    MipFilter = Linear;
};
sampler2D TextureSampler3 : register(s3) =
sampler_state
{
    AddressU = Wrap;
    AddressV = Wrap;
    MinFilter = Linear;
    MagFilter = Linear;
    MipFilter = Linear;
};
sampler2D NormalSampler : register(s4) =
sampler_state
{
    AddressU = Wrap;
    AddressV = Wrap;
    MinFilter = Linear;
    MagFilter = Linear;
    MipFilter = Linear;
};
sampler2D TextureSampler1_Alternate : register(s5) =
sampler_state
{
    AddressU = Wrap;
    AddressV = Wrap;
    MinFilter = Linear;
    MagFilter = Linear;
    MipFilter = Linear;
};

struct VS_IN
{
    float4 Position : POSITION;
    float2 Tex : TEXCOORD0;
    float3 Normal : NORMAL;
};
struct VS_OUT
{
	float4 Position : POSITION;
	float2 Tex : TEXCOORD0;
	float3 Light : TEXCOORD1;
	float3 Normal : TEXCOORD2;
	float3 CamView : TEXCOORD3;
};

struct PS_OUT
{
    float4 Color : COLOR0;
};

VS_OUT VS(VS_IN input)
{
  VS_OUT Out = (VS_OUT)0; 
  Out.Position = mul(input.Position,wvp);
  Out.Tex = input.Tex;
  Out.Light = normalize(LightDirection);
  Out.Normal = normalize(mul(input.Normal,itw));
  return Out;
}

PS_OUT Terrain_High(VS_OUT input)
{
	PS_OUT output = (PS_OUT)0;
	float4 ColorMap = tex2D( ColormapSampler, input.Tex.xy/(32*size));
	float4 NormalMap = tex2D( NormalSampler, input.Tex.xy/(32*size));
	float4 Grass = tex2D( TextureSampler1, input.Tex.xy/32);
	float4 GrassDetail = tex2D( TextureSampler1, input.Tex.xy/2);
	float4 Grass_Alternate = tex2D( TextureSampler1_Alternate, input.Tex.xy/32);
	float4 GrassDetail_Alternate = tex2D( TextureSampler1_Alternate, input.Tex.xy/2);
	float4 Dirt = tex2D( TextureSampler2, input.Tex.xy/32);
	float4 DirtDetail = tex2D( TextureSampler2, input.Tex.xy/2);
	float4 Rock = tex2D( TextureSampler3, input.Tex.xy/32);
	float4 RockDetail = tex2D( TextureSampler3, input.Tex.xy/2);
	
	float4 Color = float4(0,0,0,1);
	float4 Tex1ColorFinal = lerp(Grass_Alternate,Grass,atmosphere);
	float4 Tex1ColorFinal_detail = lerp(GrassDetail_Alternate,GrassDetail,atmosphere);
	Color.rgb += (Tex1ColorFinal*Tex1ColorFinal_detail/2)*ColorMap.r;
	Color.rgb += (Dirt*DirtDetail/2)*ColorMap.g;
	Color.rgb += (Rock*RockDetail/2)*ColorMap.b;
	
	input.Normal.r = NormalMap.r;
    input.Normal.g = NormalMap.g;
    input.Normal.b = NormalMap.b;
    
    float3 Norm = normalize(input.Normal);
    float3 LightDir = normalize(input.Light);
    float4 Ambient = AmbientIntensity * AmbientColor;
    float4 Diffuse = (DiffuseIntensity * DiffuseColor) * saturate(dot(LightDir,Norm));
    float3 Half = normalize(LightDir + normalize(input.CamView));    
    float specular = pow(saturate(dot(Norm,Half)),25);
	float4 finalLight = Ambient + (Diffuse) + ((SpecularColor * SpecularIntensity) * specular);
	finalLight.a = 1.0;
    output.Color = Color*pow(finalLight,3);
    //output.Color = pow(finalLight,4);
    return output;
}

PS_OUT Terrain_Low(VS_OUT input)
{
	PS_OUT output = (PS_OUT)0;
	float4 ColorMap = tex2D( ColormapSampler, input.Tex.xy/(32*size));
	float4 NormalMap = tex2D( NormalSampler, input.Tex.xy/(32*size));
	float4 Grass = tex2D( TextureSampler1, input.Tex.xy/8);
	float4 Grass_Alternate = tex2D( TextureSampler1_Alternate, input.Tex.xy/8);
	float4 Dirt = tex2D( TextureSampler2, input.Tex.xy/8);
	float4 Rock = tex2D( TextureSampler3, input.Tex.xy/8);	
	float4 Color = float4(0,0,0,1);
	float4 Tex1ColorFinal = lerp(Grass_Alternate,Grass,atmosphere);
	//float4 Tex1ColorFinal_detail = lerp(GrassDetail_Alternate,GrassDetail,atmosphere);
	Color.rgb += Tex1ColorFinal*ColorMap.r;
	Color.rgb += Dirt*ColorMap.g;
	Color.rgb += Rock*ColorMap.b;
	
	input.Normal.r = NormalMap.r;
    input.Normal.g = NormalMap.g;
    input.Normal.b = NormalMap.b;
    
    float3 Norm = normalize(input.Normal);
    float3 LightDir = normalize(input.Light);
    float4 Ambient = AmbientIntensity * AmbientColor;
    float4 Diffuse = (DiffuseIntensity * DiffuseColor) * saturate(dot(LightDir,Norm));
    float3 Half = normalize(LightDir + normalize(input.CamView));    
    //float specular = pow(saturate(dot(Norm,Half)),25);
	float4 finalLight = Ambient + (Diffuse);
	finalLight.a = 1.0;
    output.Color = Color*finalLight;

    return output;
}

PS_OUT Terrain_New(VS_OUT input)
{
	PS_OUT output = (PS_OUT)0;
	float4 ColorMap = tex2D( ColormapSampler, input.Tex.xy/(32*size));
	float4 NormalMap = tex2D( NormalSampler, input.Tex.xy/(32*size));
	float4 Grass = tex2D( TextureSampler1, input.Tex.xy/8);
	float4 GrassDetail = tex2D( TextureSampler1, input.Tex.xy/2);
	GrassDetail.rgb = (GrassDetail.r+GrassDetail.g+GrassDetail.b)/3.0f;
	float4 Dirt = tex2D( TextureSampler2, input.Tex.xy/8);
	float4 DirtDetail = tex2D( TextureSampler2, input.Tex.xy/2);
	DirtDetail.rgb = (DirtDetail.r+DirtDetail.g+DirtDetail.b)/3.0f;
	float4 Rock = tex2D( TextureSampler3, input.Tex.xy/8);
	float4 RockDetail = tex2D( TextureSampler3, input.Tex.xy/2);
	RockDetail.rgb = (RockDetail.r+RockDetail.g+RockDetail.b)/3.0f;
	
	float4 Color = float4(0,0,0,1);
	Color.rgb += ((Grass*GrassDetail)*2)*ColorMap.r;
	Color.rgb += ((Dirt*DirtDetail)*2)*ColorMap.g;
	Color.rgb += ((Rock*RockDetail)*2)*ColorMap.b;
	
	input.Normal.r = NormalMap.r;
    input.Normal.g = NormalMap.g;
    input.Normal.b = NormalMap.b;
    
    float3 Norm = normalize(input.Normal);
    float3 LightDir = normalize(input.Light);
    float4 Ambient = AmbientIntensity * AmbientColor;
    float4 Diffuse = (DiffuseIntensity * DiffuseColor) * saturate(dot(LightDir,Norm));
    float3 Half = normalize(LightDir + normalize(input.CamView));    
    float specular = pow(saturate(dot(Norm,Half)),25);
	float4 finalLight = Ambient + (Diffuse) + ((SpecularColor * SpecularIntensity) * specular);
	finalLight.a = 1.0;
    output.Color = Color*finalLight;
    //output.Color = Color;
    return output;
}

technique HighDetail
{
    pass p0
    {
        VertexShader = compile vs_1_1 VS();
        PixelShader = compile ps_2_0 Terrain_High();
        ZEnable = TRUE;
    }
}

technique LowDetail
{
    pass p0
    {
        VertexShader = compile vs_1_1 VS();
        PixelShader = compile ps_2_0 Terrain_High();
        ZEnable = TRUE;
    }
}

