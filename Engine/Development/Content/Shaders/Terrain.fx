float4x4 wvp : WORLDVIEWPROJECTION;
float4x4 itw : WorldInverseTranspose;
float time;
float atmosphere;

float AmbientIntensity = 0.5;
float4 AmbientColor : AMBIENT = float4(.5,.5,.5,1);

float DiffuseIntensity = 1.0;
float4 DiffuseColor : Diffuse = float4(1,1,1,1);

float4 SpecularColor : Specular = float4(1,1,1,1);
float SpecularIntensity : Scalar = 2.0;

float4 CameraPosition : CameraPosition;
float3 LightDirection : Direction = float3(10,0,0);

float LightPosX;
float LightPosY;
float LightPosZ;
int size = 16;

sampler2D TexturemapSampler : register(s0) =
sampler_state
{
    //Texture = <Texturemap>;
    AddressU = Wrap;
    AddressV = Wrap;
    MinFilter = Point;
    MagFilter = Linear;
    MipFilter = Linear;
};
sampler2D DetailtextureSampler1 : register(s1) =
sampler_state
{
   // Texture = <Detailtexture1>;
    AddressU = Wrap;
    AddressV = Wrap;
    MinFilter = Point;
    MagFilter = Linear;
    MipFilter = Linear;
	
	
};
sampler2D DetailtextureSampler1_alternate : register(s2) =
sampler_state
{
   // Texture = <Detailtexture1_alternate>;
    AddressU = Wrap;
    AddressV = Wrap;
    MinFilter = Point;
    MagFilter = Linear;
    MipFilter = Linear;
	
	
};

sampler2D DetailtextureSampler2 : register(s3) =
sampler_state
{
   // Texture = <Detailtexture2>;
    AddressU = Wrap;
    AddressV = Wrap;
    MinFilter = Point;
    MagFilter = Linear;
    MipFilter = Linear;
	
	
};

sampler2D AlphamapSampler1 : register(s4) =
sampler_state
{
   // Texture = <Alphamap_detail1>;
    AddressU = Wrap;
    AddressV = Wrap;
    MinFilter = Point;
    MagFilter = Linear;
    MipFilter = Linear;
	
	
};

sampler2D AlphamapSampler2 : register(s5) =
sampler_state
{
   // Texture = <Alphamap_detail2>;
    AddressU = Wrap;
    AddressV = Wrap;
    MinFilter = Point;
    MagFilter = Linear;
    MipFilter = Linear;	
};

sampler2D NormalSampler : register(s6) =
sampler_state
{
   // Texture = <NormalTexture>;
    AddressU = Wrap;
    AddressV = Wrap;
    MinFilter = Point;
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

VS_OUT VS_Ambient(VS_IN input)
{
    VS_OUT output = (VS_OUT)0;
    output.Position = mul(input.Position,wvp);
    output.Tex = input.Tex;
  //  float3 LightPos;
    
 //   LightPos.x = LightPosX;
  //  LightPos.y = LightPosY;
 //   LightPos.z = LightPosZ;
 //   float3 LightDirection = LightPos;
    output.Light = normalize(LightDirection);
    output.Normal = normalize(mul(itw,input.Normal));
    return output;
}

PS_OUT PS_High(VS_OUT input)
{
    PS_OUT output = (PS_OUT)0;
    float4 normal = tex2D( NormalSampler, input.Tex.xy/(32*size));
    float4 texturemap = tex2D( TexturemapSampler, input.Tex.xy/(32*size));
    float4 colorAlphamap_detail1 = tex2D( AlphamapSampler1, input.Tex.xy/(32*size) );
    float4 colorAlphamap_detail2 = tex2D( AlphamapSampler2, input.Tex.xy/(32*size) );
    float4 colorDetail1 = tex2D( DetailtextureSampler1, input.Tex.xy/2);
    float4 colorDetail1_alternate = tex2D( DetailtextureSampler1_alternate, input.Tex.xy/2);
    float4 colorDetail2 = tex2D( DetailtextureSampler2, input.Tex.xy/2);
    input.Normal.r = normal.r;
    input.Normal.g = normal.g;
    input.Normal.b = normal.b;
    
    float3 Norm = normalize(input.Normal);
    float3 LightDir = normalize(input.Light);
    float4 Ambient = AmbientIntensity * AmbientColor;
    float4 Diffuse = (DiffuseIntensity * DiffuseColor) * saturate(dot(LightDir,Norm));
    float3 Half = normalize(LightDir + normalize(input.CamView));    
    float specular = pow(saturate(dot(Norm,Half)),25);
	float4 finalLight = Ambient + Diffuse + ((SpecularColor * SpecularIntensity) * specular);
	float4 finalColor = lerp(texturemap,((lerp(colorDetail1_alternate, colorDetail1,atmosphere)*colorAlphamap_detail1) + (colorDetail2*colorAlphamap_detail2)),0.7);    
	//output.Color = finalColor*((finalLight/4)*8);
	output.Color = texturemap;
	return output;
}
PS_OUT PS_Low(VS_OUT input)
{
    PS_OUT output = (PS_OUT)0;
    float4 texturemap = tex2D( TexturemapSampler, input.Tex.xy/(32*size));
    
    float3 Norm = normalize(input.Normal);
    float3 LightDir = normalize(input.Light);
    float4 Ambient = AmbientIntensity * AmbientColor;
    float4 Diffuse = (DiffuseIntensity * DiffuseColor) * saturate(dot(LightDir,Norm));
    float3 Half = normalize(LightDir + normalize(input.CamView));    
    float specular = pow(saturate(dot(Norm,Half)),25);
	float4 finalLight = Ambient + Diffuse + ((SpecularColor * SpecularIntensity) * specular);
	output.Color = texturemap*((finalLight/4)*8);
	return output;
}

technique HighDetail
{
    pass p0
    {
		CULLMODE = CCW;
		ZEnable = TRUE;
		VertexShader = compile vs_1_1 VS_Ambient();
        // We upgraded to pixel shader 2.0 so we can used more advanced commands
        PixelShader = compile ps_2_0 PS_High();
    }
}
technique LowDetail
{
	 pass p0
    {
		//CULLMODE = CCW;
		ZEnable = TRUE;
        VertexShader = compile vs_1_1 VS_Ambient();
        // We upgraded to pixel shader 2.0 so we can used more advanced commands
        PixelShader = compile ps_2_0 PS_Low();

    }
}