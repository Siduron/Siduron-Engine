float amount;
float time: TIME;

texture Alive;
texture Dead;
texture Alpha;
texture Normal;
texture Detail;

float4x4 World      : WORLD;
float4x4 View       : VIEW;
float4x4 Projection : PROJECTION;
float4x4 matWorldViewProj: WORLDVIEWPROJECTION;

// light direction (view space)
float3 lightDir = {0.577, -15.577, -80.577};
float4 camPos;

// light intensity
float4 I_a = { 0.7f, 0.7f, 0.7f, 0.7f };    // ambient
float4 I_d = { 1.0f, 1.0f, 1.0f, 1.0f };    // diffuse
float4 I_s = { 1.0f, 1.0f, 1.0f, 1.0f };    // specular

// material reflectivity
float4 k_a : MATERIALAMBIENT = { 0.3f, 0.3f, 0.3f, 1.0f };    // ambient
float4 k_d : MATERIALDIFFUSE = { 1.0f, 1.0f, 1.0f, 1.0f };    // diffuse
float4 k_s : MATERIALSPECULAR= { 1.0f, 1.0f, 1.0f, 1.0f };    // specular
float  n   : MATERIALPOWER = 20.0f;                           // power

sampler2D AliveSampler =
sampler_state
{
    Texture = <Alive>;
    AddressU = Wrap;
    AddressV = Wrap;
    MinFilter = Point;
    MagFilter = Linear;
    MipFilter = Linear;
	
	
};

sampler2D DeadSampler =
sampler_state
{
    Texture = <Dead>;
    AddressU = Wrap;
    AddressV = Wrap;
    MinFilter = Point;
    MagFilter = Linear;
    MipFilter = Linear;
};

sampler2D AlphaSampler =
sampler_state
{
    Texture = <Alpha>;
    AddressU = Wrap;
    AddressV = Wrap;
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

sampler2D DetailSampler =
sampler_state
{
    Texture = <Detail>;
    AddressU = Mirror;
    AddressV = Mirror;
    MinFilter = Point;
    MagFilter = Linear;
    MipFilter = Linear;
};


struct VS_INPUT
{
    float4 Pos   : POSITION;
};

struct VS_OUTPUT
{
    float4 Pos  : POSITION;
    float4 Diff : COLOR0;
    float4 Spec : COLOR1;
    float2 Tex  : TEXCOORD0;
};

// Lighting
VS_OUTPUT VS(float3 Pos  : POSITION, float3 Norm : NORMAL, float2 Tex  : TEXCOORD0)
{
	VS_OUTPUT Out = (VS_OUTPUT)0;
	float3 L = -lightDir;
	
    float4x4 WorldView = mul(World, View);
    float3 P = mul(float4(Pos, 1), (float4x3)WorldView);  // position (view space)

    float3 N = normalize(mul(Norm, (float3x3)WorldView)); // normal (view space)

    float3 R = normalize(2 * dot(N, L) * N - L);          // reflection vector (view space)
    float3 V = -normalize(P);                             // view direction (view space)
	
    Out.Pos  = mul(float4(P, 1), Projection);             // position (projected)
    Out.Diff = I_a * k_a + I_d * k_d * max(0, dot(N, L)); // diffuse + ambient
    Out.Spec = I_s * k_s * pow(max(0, dot(R, V)), n/4);   // specular
    Out.Tex  = Tex;                                       

	return Out;
}

//-----------------------------------------------------------------------------
// Pixel Shader: Splatting
// Desc: Blends multiple textures
//-----------------------------------------------------------------------------
float4 Splatting(VS_OUTPUT Out) : COLOR0
{
	float4 AliveColor;
	AliveColor = tex2D( AliveSampler, Out.Tex.xy / 10 );
	
	float4 DetailColor;
	DetailColor = tex2D( AliveSampler, Out.Tex.xy / 2.5);
	
	float4 DetailColor2;
	DetailColor2 = tex2D( AliveSampler, Out.Tex.xy);
	
	float4 DetailColor3;
	DetailColor3 = tex2D( DetailSampler, Out.Tex.xy);
	
	//Sand
	float4 DeadColor;
	DeadColor = tex2D( DeadSampler, Out.Tex.xy / 10 );
	
	float4 DeadColorDetail;
	DeadColorDetail = tex2D( DeadSampler, Out.Tex.xy / 2.5 );
	
	float4 DeadColorDetail2;
	DeadColorDetail2 = tex2D( DeadSampler, Out.Tex.xy);
	

	float4 NormalColor;
	NormalColor = tex2D( NormalSampler, Out.Tex.xy );
	
	float2 Tex2 = Out.Tex;
	Tex2.x = Tex2.x / 64;
	Tex2.y = Tex2.y / 64;

	float4 AlphaColor;
	AlphaColor = tex2D( AlphaSampler, Tex2.xy );
	
	//Splatting
	//float4 newColor = lerp(AliveColor,DeadColor, AlphaColor);
	float4 newColor = (AliveColor + DetailColor) /2;
	float4 newColor2 = (newColor + DetailColor2) / 2;
	float4 newColor3 = lerp(newColor2, DetailColor3, 0.3);
	
	//Bump mapping
	float4 bumpColor = newColor * dot(2.0*(NormalColor-0.3), 2.0*(Out.Diff-0.4));
	
	float4 newColorSand = (DeadColor + DeadColorDetail) /2;
	float4 newColorSand2 = (newColorSand + DeadColorDetail2) / 2;
	float4 newColorSand3 = lerp(newColorSand2, DetailColor3, 0.1);
	
	float4 finalColor = lerp(newColor3+bumpColor*2,newColorSand3, (AlphaColor*1));
	
	//Lighting
	float4 lightedColor = (Out.Diff*2 * finalColor*amount*2)*(Out.Spec*1.2);
	
		
	//return bumpColor + (lightedColor*2);
	//return bumpColor;
	//return lightedColor;
	//return newColor + bumpColor;
	return finalColor;
}

//-----------------------------------------------------------------------------
// Technique: PostProcess
// Desc: 
//-----------------------------------------------------------------------------
technique PostProcess
<
   
>
{
    pass p0
    {
		// lighting
        Lighting       = TRUE;
        SpecularEnable = TRUE;
		
		// texture stages
        ColorOp[0]   = MODULATE;
        ColorArg1[0] = TEXTURE;
        ColorArg2[0] = DIFFUSE;
        AlphaOp[0]   = MODULATE;
        AlphaArg1[0] = TEXTURE;
        AlphaArg2[0] = DIFFUSE;

        ColorOp[1]   = DISABLE;
        AlphaOp[1]   = DISABLE;
		
        VertexShader = compile vs_2_0 VS();
		//VertexShader = null;
        PixelShader = compile ps_2_0 Splatting();
		//PixelShader = null;
        ZEnable = TRUE;
    }
}
