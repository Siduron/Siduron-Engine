float4x4 wvp : WORLDVIEWPROJECTION;
texture baseColor;


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
	float4 Color = tex2D( baseColorSampler, input.Tex.xy);
    output.Color = Color;
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
