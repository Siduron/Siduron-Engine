float4x4 wvp : WORLDVIEWPROJECTION;
float4x4 itw : WorldInverseTranspose;
float atmosphere = 1;
float debug = 0;

float AmbientIntensity = 1.25;
float4 AmbientColor : AMBIENT = float4(.5,.5,.5,1);

float DiffuseIntensity = 2.5;
float4 DiffuseColor : Diffuse = float4(1,1,1,1);

float4 SpecularColor : Specular = float4(1,1,1,1);
float SpecularIntensity : Scalar = 2.0;

float4 CameraPosition : CameraPosition;
float3 LightDirection : Direction = float3(1,0.5,0);

int render_mode = 0;

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
sampler2D TextureSampler3 : register(s2) =
sampler_state
{
    AddressU = Wrap;
    AddressV = Wrap;
    MinFilter = Linear;
    MagFilter = Linear;
    MipFilter = Linear;
};

sampler2D TextureSampler4 : register(s3) =
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
    float3 Normal : NORMAL;
    float4 Color : COLOR0;
    float2 Tex : TEXCOORD0;    
};
struct VS_OUT
{
	float4 Position : POSITION;
	float3 Normal : TEXCOORD2;
	float4 Color : COLOR0;
	float2 Tex : TEXCOORD0;
	float3 Light : TEXCOORD1;
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
  Out.Color = input.Color;
  Out.Tex = input.Tex;
  Out.Light = normalize(LightDirection);
  Out.Normal = normalize(mul(input.Normal,itw));
  return Out;
}

PS_OUT Terrain_High(VS_OUT input)
{
	PS_OUT output = (PS_OUT)0;
	float4 Grass = tex2D( TextureSampler1, input.Tex.xy/16);
	float4 GrassDetail = tex2D( TextureSampler1, input.Tex.xy/2);
	//float4 GrassDetail_Alternate = tex2D( TextureSampler1_Alternate, input.Tex.xy/2);
	float4 Dirt = tex2D( TextureSampler2, input.Tex.xy/32);
	float4 DirtDetail = tex2D( TextureSampler2, input.Tex.xy/2);
	float4 Rock = tex2D( TextureSampler3, input.Tex.xy/32);
	float4 RockDetail = tex2D( TextureSampler3, input.Tex.xy/2);
	
	float4 Color = float4(0,0,0,1);
	Color.rgb += ((Grass*GrassDetail/2)*input.Color.r) + ((Dirt*DirtDetail/2)*input.Color.g) + ((Rock*RockDetail/2)*input.Color.b);
    
	float3 Norm = normalize(input.Normal);
	float3 LightDir = normalize(input.Light);
	float4 Ambient = AmbientIntensity * AmbientColor;
	float4 Diffuse = (DiffuseIntensity * DiffuseColor) * saturate(dot(LightDir,Norm));
	float3 Half = normalize(LightDir + normalize(input.CamView));    
	float specular = pow(saturate(dot(Norm,Half)),25);
	float4 finalLight = Ambient + (Diffuse) + ((SpecularColor * SpecularIntensity) * specular);
	finalLight.a = 1.0;
	//output.Color = float4(input.Normal.r, input.Normal.g, input.Normal.b, 1);
	if( render_mode == 0 )
	{
		output.Color = Color * finalLight;
	}
	else if( render_mode == 1 )
	{
		output.Color = input.Color;
	}
	else if( render_mode == 2 )
	{
		output.Color = float4(input.Normal.r, input.Normal.g, input.Normal.b, 1);
	}
	else if( render_mode == 3 )
	{
		output.Color = finalLight;
	}
	
	//output.Color = NormalMap;
	//output.Color = pow(finalLight,4);
    return output;
}

PS_OUT Terrain_High_Concrete(VS_OUT input)
{
	PS_OUT output = (PS_OUT)0;
	float4 Color = tex2D( TextureSampler4, input.Tex.xy/4);
	output.Color = Color;
	return output;
}

PS_OUT Terrain_Debug(VS_OUT input)
{
	PS_OUT output = (PS_OUT)0;
	if(!debug)
	{	
		float4 Texture1 = tex2D( TextureSampler1, input.Tex.xy/4);
		output.Color = Texture1;
	}
	else
	{
		float4 Color = float4(0,1,0,1);
		output.Color = Color;
	}
	return output;
}

technique HighDetail
{
    pass p0
    {
        VertexShader = compile vs_1_1 VS();
        PixelShader = compile ps_2_0 Terrain_High();
        ZEnable = TRUE;
        ZWriteEnable = TRUE;
    }
}
