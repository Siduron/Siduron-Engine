float4x4 wvp : WORLDVIEWPROJECTION;
texture baseColor;
texture texture1;
float red;
float green;
float blue;
float contrast;
float time;
float atmosphere;

sampler2D baseColorSampler =
sampler_state
{
    Texture = <baseColor>;
    AddressU = Wrap;
    AddressV = Wrap;
    MinFilter = Linear;
    MagFilter = Linear;
    MipFilter = Linear;
	
	
};

sampler2D texture1Sampler =
sampler_state
{
    Texture = <texture1>;
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
	float3 Normal : TEXCOORD2;
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
  return Out;
}

PS_OUT PS(VS_OUT input)
{
	PS_OUT output = (PS_OUT)0;
	float2 Tex1 = input.Tex;
	float2 Tex2 = (input.Tex*2)-time/1000;
	
	float4 Color = tex2D( baseColorSampler, Tex1);
	if(atmosphere < 1.0)
	{
		Color += tex2D( baseColorSampler, Tex1-0.002);
		Color += tex2D( baseColorSampler, Tex1+0.002);
		Color += tex2D( baseColorSampler, Tex1+0.004);
		Color = Color / 4;
	}
	float4 texture1Color = tex2D( texture1Sampler, Tex2);
	Color.r += red;
	Color.g += green;
	Color.b += blue;
	output.Color = pow(lerp(texture1Color,Color,atmosphere),contrast);
    return output;
}

technique D3D
{
    pass p0
    {
        VertexShader = compile vs_1_1 VS();
        PixelShader = compile ps_2_0 PS();
        ZEnable = TRUE;
    }
}
