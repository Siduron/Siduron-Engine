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



texture g_txSrcColor;
texture g_txSrcNormal;


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

//-----------------------------------------------------------------------------
// Pixel Shader: HorizontalBlur
// Desc: Blurs the image vertically
//-----------------------------------------------------------------------------
float4 PostProcessPS( float2 Tex : TEXCOORD0 ) : COLOR0
{
    float4 Color = 0;

    

    return Color;
}

// the format of our vertex data
struct VS_OUTPUT
{
  float4 Pos  : POSITION;
};

//Simple Vertex Shader - carry out transformation
VS_OUTPUT VS(float4 Pos  : POSITION)
{
  VS_OUTPUT Out = (VS_OUTPUT)0; 

  
  return Out;
}



//-----------------------------------------------------------------------------
// Technique: PostProcess
// Desc: Performs post-processing effect that converts a colored image to
//       black and white.
//-----------------------------------------------------------------------------
technique PostProcess
<
   
>
{
    pass p0
    {
        VertexShader = null;
        PixelShader = null;
        ZEnable = TRUE;
    }
}
