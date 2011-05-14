float4x4 wvp : WORLDVIEWPROJECTION;
float4x4 World      : WORLD;
float4x4 View       : VIEW;
float4x4 Projection : PROJECTION;
float time;

float AmbientIntensity = 0.5;
float4 AmbientColor : AMBIENT = float4(.5,.5,.5,1);

float DiffuseIntensity = 1.0;
float4 DiffuseColor : Diffuse = float4(1,1,1,1);

float4 SpecularColor : Specular = float4(1,1,1,1);
float SpecularIntensity : Scalar = 2.0;

float3 LightDirection : Direction = float3(1,0,1);
float4 CameraPosition : CameraPosition;


sampler2D TextureSampler1 : register(s0) =
sampler_state
{
    AddressU = Wrap;
    AddressV = Wrap;
    MinFilter = Linear;
    MagFilter = Linear;
    MipFilter = Linear;
};
sampler2D TextureSampler2 : register(s1) =
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
    float4 Tangent : TANGENT;
};
struct VS_OUT
{
	float4 Position : POSITION;
	float2 Tex : TEXCOORD0;
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
  Out.Normal = input.Normal;
  Out.CamView = CameraPosition - mul(input.Position,World);

  return Out;
}

PS_OUT PS(VS_OUT input)
{
	PS_OUT output = (PS_OUT)0;
	float2 Tex1 = input.Tex;
	float2 Tex2 = input.Tex;
	Tex1.x = input.Tex.x + (time/200000);
	Tex2.x = input.Tex.x + (time/250000);
	
	float4 normalMap = tex2D( TextureSampler1, ((Tex1.xy*64)));
	float4 wtexture = tex2D( TextureSampler2, ((Tex1.xy*64)));
	float4 baseColor = float4(0.4,0.8,0.8,1);
	float3 Normal;
	Normal.r = normalMap.r;
    Normal.g = normalMap.g;
    Normal.b = normalMap.b;
    
    float3 Norm = normalize(Normal);
    float3 LightDir = normalize(LightDirection);
    float4 Ambient = AmbientIntensity * AmbientColor;
    float4 Diffuse = (DiffuseIntensity * DiffuseColor) * saturate(dot(LightDir,Norm));
    float3 Half = normalize(LightDir + normalize(input.CamView));    
    float specular = pow(saturate(dot(Norm,Half)),25);
	float4 finalLight = Ambient + (Diffuse) + ((SpecularColor * SpecularIntensity) * specular);
	if( ((finalLight.r+finalLight.g+finalLight.b)/3) < 0.7)
	{
		finalLight.a = (finalLight.r+finalLight.g+finalLight.b)/3;
		finalLight.a = finalLight.a;
	}
	finalLight.a = 0.7;
	
	baseColor.a = 0.7;    
	output.Color = (finalLight*baseColor);
//	output.Color.a = pow((finalLight.r+finalLight.g+finalLight.b)/3,1);
    
    return output;
}

technique D3D
{
    pass p0
    {
		AlphaBlendEnable=true;
		SrcBlend = SrcAlpha;
		DestBlend = InvSrcAlpha;
        VertexShader = compile vs_1_1 VS();
        PixelShader = compile ps_3_0 PS();
        ZEnable = TRUE;
    }
}
