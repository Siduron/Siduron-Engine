/**
 * This shader lightens the mesh, making it brighter then normal
 * It is used by raypicking to signal which entity is selected
 */

sampler2D MatTexture  = sampler_state {
    MinFilter = LinearMipMapLinear;
    MagFilter = Linear;
    WrapS = Repeat;
    WrapT = Repeat;
};

float4x4 WorldViewProjection : WorldViewProjection;
float4 Highlight : Highlight;
float ExpandModIncr : ExpandModIncr;
float BloatModIncr : BloatModIncr;

struct vs_output
{
	float4 position : POSITION;
    float4 color    : COLOR;
	float2 texCoord : TEXCOORD0;
		

};
vs_output mainVS(float4 pos : POSITION, float4 color : COLOR, float2 texCoord: TEXCOORD0) : POSITION
{
	vs_output uit;
	
	float4 posOut = float4(pos.x, pos.y, pos.z, 1);
	posOut += (BloatModIncr*normalize(float4(pos.x, pos.y, pos.z, 0)));
	
	posOut.x = posOut.x * ExpandModIncr;
	posOut.y = posOut.y * ExpandModIncr;
	posOut.z = posOut.z * ExpandModIncr;
	
	uit.position = mul(WorldViewProjection, posOut);
	uit.color = color;
	uit.texCoord = texCoord;
	return uit;
}

struct ps_out
{
	float4 color : COLOR;
};


ps_out mainPS(float4 color : COLOR, float2 texCoord : TEXCOORD0, uniform sampler2D decal) : COLOR 
{
	ps_out uit;
	uit.color = lerp(tex2D(decal, texCoord), Highlight, 0.3);

	return uit;
}

technique techniqueDX 
{
	pass p0 
	{
		// Alpha Blending
		BlendEnable = true;
		BlendFunc = int2(SrcAlpha, OneMinusSrcAlpha);

		// Z-buffer
		Zenable = true;
		ZWriteEnable = true;
		
		// Culling 
		CullMode = none;
		
		FragmentProgram = compile ps_2_0 mainPS(MatTexture);
		VertexProgram = compile vs_2_0 mainVS();
	}
}
technique techniqueOGL 
{
	pass p0 
	{
		CullFaceEnable = true;	
		DepthTestEnable = true;
		AlphaTestEnable = true; 
		AlphaFunc = float2(Greater, 0.1);

		FragmentProgram = compile arbfp1 mainPS(MatTexture);
		VertexProgram = compile arbvp1 mainVS();
	}
}
