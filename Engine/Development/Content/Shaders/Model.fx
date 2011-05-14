float4x4 world : World;
float4x4 wvp : WorldViewProjection;
float4x4 itw : WorldInverseTranspose;
texture baseColor;

float AmbientIntensity = 0.5;
float4 AmbientColor : AMBIENT = float4(.5,.5,.5,1);

float DiffuseIntensity = 1.0;
float4 DiffuseColor : Diffuse = float4(1,1,1,1);

float4 SpecularColor : Specular = float4(1,1,1,1);
float SpecularIntensity : Scalar = 1.0;

float3 LightDirection : Direction = float3(1,0.5,0);
float4 CameraPosition : CameraPosition;

float LightPosX;
float LightPosY;
float LightPosZ;

sampler2D baseColorSampler =
sampler_state
{
    Texture = <baseColor>;
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
	float4 CamView : TEXCOORD3;
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
  //float3 LightPos;

//  LightPos.x = LightPosX;
//  LightPos.y = LightPosY;
 // LightPos.z = LightPosZ;
 // float3 LightDirection = LightPos;
  Out.Light = normalize(LightDirection);
  Out.Normal = normalize(mul(input.Normal,itw));
  Out.CamView = CameraPosition - mul(input.Position,world);
  return Out;
}

PS_OUT PS(VS_OUT input)
{
	PS_OUT output = (PS_OUT)0;
	float4 Color = tex2D( baseColorSampler, input.Tex.xy);
	
    float3 Norm = normalize(input.Normal);
    float3 LightDir = normalize(input.Light);
    float4 Ambient = AmbientIntensity * AmbientColor;
    float4 Diffuse = (DiffuseIntensity * DiffuseColor) * saturate(dot(LightDir,Norm));
    float3 Half = normalize(LightDir + normalize(input.CamView));    
    float specular = pow(saturate(dot(Norm,Half)),25);
	float4 finalLight = Ambient + Diffuse + ((SpecularColor * SpecularIntensity) * specular);
	finalLight.a = 1.0;
	output.Color = Color*finalLight;
	//output.Color = finalLight;

    return output;
}

technique D3D
{
    pass p0
    {
		//CULLMODE = CCW;
        ZEnable = TRUE;
        AlphaBlendEnable = True;
		SrcBlend = SrcAlpha;
		DestBlend = InvSrcAlpha;
        VertexShader = compile vs_1_1 VS();
        PixelShader = compile ps_2_0 PS();

    }
}
