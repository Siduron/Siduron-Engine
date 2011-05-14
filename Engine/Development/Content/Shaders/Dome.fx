float time;

sampler2D TextureSampler1 : register(s0) =
sampler_state
{
    AddressU = Wrap;
    AddressV = Wrap;
    MinFilter = Linear;
    MagFilter = Linear;
    MipFilter = Linear;
};

float4 DomeShader( float2 Tex : TEXCOORD0 ) : COLOR0
{
    float4 Color;
    float4 Color2;
    
    float2 Tex1 = Tex;
    float2 Tex2 = Tex;
    
    Tex1.y = Tex1.y + time/50000;
    Tex2.y = Tex2.y - time/40000;
    Tex1.x = Tex1.x - time/40000;
    Tex2.x = Tex2.x + time/50000;
    
    Tex1.xy = Tex1.xy;
    Tex2.xy = Tex2.xy;
    
    Color = tex2D( TextureSampler1, Tex1.xy*2);
    Color2 = tex2D( TextureSampler1, Tex2.xy*2);
    
    float4 Color3 = pow(lerp(Color,Color2,0.2),8);

	Color3.a = (Color3.r+Color3.g+Color3.b)/3;

    
    float4 Color4 = float4(0.0,0.5,1.0,0.1);
    return (Color3+Color4);

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
{
    pass p0
    {
		AlphaBlendEnable=true;
		SrcBlend = SrcAlpha;
		DestBlend = InvSrcAlpha;
        VertexShader = null;
        PixelShader = compile ps_2_0 DomeShader();
        ZWriteEnable = FALSE;
        ZEnable = TRUE;
    }
}