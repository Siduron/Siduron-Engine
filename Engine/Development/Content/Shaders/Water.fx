//-----------------------------------------------------------------------------
// File: PP_ColorGBlurV.fx
//
// Desc: Effect file for image post-processing sample.  This effect contains
//       a single technique with a pixel shader that amiplifies and blurs
//       an image vertically using weights that follow a Gaussian
//       distribution and.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------

float amount;
float time;

texture g_txSrcColor;
texture g_txSrcNormal;
texture g_txSrcPosition;
texture g_txSrcVelocity;

texture g_txSceneColor;
texture g_txSceneNormal;
texture g_txScenePosition;
texture g_txSceneVelocity;

texture Water1;
texture Water2;
texture Normal;

sampler2D Water1Sampler =
sampler_state
{
    Texture = <Water1>;
    AddressU = MIRROR;
    AddressV = MIRROR;
    MinFilter = Point;
    MagFilter = Linear;
    MipFilter = Linear;
	
	
};

sampler2D Water2Sampler =
sampler_state
{
    Texture = <Water2>;
    AddressU = MIRROR;
    AddressV = MIRROR;
    MinFilter = Point;
    MagFilter = Linear;
    MipFilter = Linear;
	
	
};

sampler2D NormalSampler =
sampler_state
{
    Texture = <Normal>;
    AddressU = Wrap;
    AddressV = Wrap;
    MinFilter = Point;
    MagFilter = Linear;
    MipFilter = Linear;
};

sampler2D g_samSrcColor =
sampler_state
{
    Texture = <g_txSrcColor>;
    AddressU = Wrap;
    AddressV = Wrap;
    MinFilter = Point;
    MagFilter = Linear;
    MipFilter = Linear;
	
	
};
sampler2D g_samSrcNormal =
sampler_state
{
    Texture = <g_txSrcNormal>;
    AddressU = Clamp;
    AddressV = Clamp;
    MinFilter = Point;
    MagFilter = Linear;
    MipFilter = Linear;
};
sampler2D g_samSrcPosition =
sampler_state
{
    Texture = <g_txSrcPosition>;
    AddressU = Clamp;
    AddressV = Clamp;
    MinFilter = Point;
    MagFilter = Linear;
    MipFilter = Linear;
};
sampler2D g_samSrcVelocity =
sampler_state
{
    Texture = <g_txSrcVelocity>;
    AddressU = Clamp;
    AddressV = Clamp;
    MinFilter = Point;
    MagFilter = Linear;
    MipFilter = Linear;
};

sampler2D g_samSceneColor = sampler_state
{
    Texture = <g_txSceneColor>;
    AddressU = Clamp;
    AddressV = Clamp;
    MinFilter = Point;
    MagFilter = Linear;
    MipFilter = Linear;
};
sampler2D g_samSceneNormal = sampler_state
{
    Texture = <g_txSceneNormal>;
    AddressU = Clamp;
    AddressV = Clamp;
    MinFilter = Point;
    MagFilter = Linear;
    MipFilter = Linear;
};
sampler2D g_samScenePosition = sampler_state
{
    Texture = <g_txScenePosition>;
    AddressU = Clamp;
    AddressV = Clamp;
    MinFilter = Point;
    MagFilter = Linear;
    MipFilter = Linear;
};
sampler2D g_samSceneVelocity = sampler_state
{
    Texture = <g_txSceneVelocity>;
    AddressU = Clamp;
    AddressV = Clamp;
    MinFilter = Point;
    MagFilter = Linear;
    MipFilter = Linear;
};




static const int g_cKernelSize = 13;

float2 PixelKernel[g_cKernelSize] =
{
    { 0, -6 },
    { 0, -5 },
    { 0, -4 },
    { 0, -3 },
    { 0, -2 },
    { 0, -1 },
    { 0,  0 },
    { 0,  1 },
    { 0,  2 },
    { 0,  3 },
    { 0,  4 },
    { 0,  5 },
    { 0,  6 },
};

float2 TexelKernel[g_cKernelSize]
<
    string ConvertPixelsToTexels = "PixelKernel";
>;




static const float BlurWeights[g_cKernelSize] = 
{
    0.002216,
    0.008764,
    0.026995,
    0.064759,
    0.120985,
    0.176033,
    0.199471,
    0.176033,
    0.120985,
    0.064759,
    0.026995,
    0.008764,
    0.002216,
};

float BloomScale = 5.5f;

// transformations provided by the app, constant Uniform data
float4x4 matWorldViewProj: WORLDVIEWPROJECTION;

// the format of our vertex data
struct VS_OUTPUT
{
  float4 Pos  : POSITION;
  float2 Tex : TEXCOORD0;
};

// Simple Vertex Shader - carry out transformation
VS_OUTPUT VS(float4 Pos  : POSITION,float2 Tex : TEXCOORD0)
{
  VS_OUTPUT Out = (VS_OUTPUT)0;
  float angle=((time/1000)%360)*1;

    //Pos.y  = sin( Pos.x+angle);
   // Pos.y += sin( Pos.z+angle);
   // Pos.y *= Pos.x * 0.001f;
	//Pos.y+=1;
  Out.Pos = Out.Pos + mul(Pos , matWorldViewProj); 
  Out.Tex = Tex;
  return Out;
}

struct PS_OUT
{
	float4 color : COLOR;
};

//-----------------------------------------------------------------------------
// Pixel Shader: HorizontalBlur
// Desc: Blurs the image vertically
//-----------------------------------------------------------------------------
PS_OUT MultiTexture( VS_OUTPUT In) : COLOR0
{
	PS_OUT Out = (PS_OUT)0;
	float2 Tex1 = In.Tex;
	float2 Tex2 = In.Tex;
	
	Tex1.x = In.Tex.x + (time/2000)/40;
	Tex2.x = In.Tex.x - (time/2500)/40;
			 
	Tex1.y = In.Tex.y + (time/2500)/20;
	Tex2.y = In.Tex.y - (time/2000)/30;
			
	Tex1.x = Tex1.x + (sin(Tex1.y*5)*sin(time/1010)/60);
	Tex1.x = Tex1.x + (sin(Tex1.y*50)*sin(time/800)/100);
	Tex1.x = Tex1.x + (sin(Tex1.y*75)*sin(time/400)/195);
	//Tex1.x = Tex1.x + (sin(Tex1.y*117)*sin(time/300)/500);
	
	Tex1.y = Tex1.y + (sin(Tex1.x*5)*sin(time/1020)/60);
	Tex1.y = Tex1.y + (sin(Tex1.x*50)*sin(time/800)/100);
	Tex1.y = Tex1.y + (sin(Tex1.x*75)*sin(time/400)/195);
	//Tex1.y = Tex1.y + (sin(Tex1.x*113)*sin(time/310)/500);
			
	Tex2.x = Tex2.x + (cos(Tex2.y*5)*cos(time/990)/60);
	Tex2.x = Tex2.x + (cos(Tex2.y*50)*cos(time/800)/100);
	Tex2.x = Tex2.x + (cos(Tex2.y*75)*cos(time/400)/195);
	//Tex2.x = Tex2.x + (cos(Tex2.y*112)*cos(time/290)/500);
	
	Tex2.y = Tex2.y + (cos(Tex2.x*5)*cos(time/980)/60);
	Tex2.y = Tex2.y + (cos(Tex2.x*50)*cos(time/800)/100);
	Tex2.y = Tex2.y + (cos(Tex2.x*75)*cos(time/400)/195);
	//Tex2.y = Tex2.y + (cos(Tex2.x*118)*cos(time/320)/500);
	
	float4 Color1 = tex2D( Water1Sampler, Tex1.xy);
	float4 Color2 = tex2D( Water2Sampler, Tex2.xy);
	float4 NormalColor1 = tex2D( NormalSampler, Tex1.xy);
	float4 NormalColor2 = tex2D( NormalSampler, Tex2.xy);
		
	Color1.a = 0.3;
	Color2.a = 0.6;
	
	//Color1 = Color1 * NormalColor1;
	//Color2 = Color2 * NormalColor2;	
			
	float4 ColorFinal = ((Color1 + Color2)/2);
		
	Out.color = ColorFinal;
	return Out;
}

PS_OUT Ripples(PS_OUT In)
{
	PS_OUT Out = (PS_OUT)0;
	Out.color = In.color;
	//float4 color1 = 150;

	return Out;
}

//-----------------------------------------------------------------------------
// Technique: PostProcess
// Desc: Performs post-processing effect that converts a colored image to
//       black and white.
//-----------------------------------------------------------------------------
technique PostProcess
<
    string Parameter0 = "BloomScale";
    float4 Parameter0Def = float4( 1.5f, 0, 0, 0 );
    int Parameter0Size = 1;
    string Parameter0Desc = " (float)";
>
{
    pass p0
    {
    
        VertexShader = compile vs_1_1 VS();
        PixelShader = compile ps_3_0 MultiTexture();
		//PixelShader = null;
		ZWriteEnable = TRUE;
        ZEnable = TRUE;
    }
    
    pass p1
    {
		VertexShader = null;
        PixelShader = compile ps_3_0 Ripples();
    }
}
