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
};
struct VS_OUT
{
	float4 Position : POSITION;
	float2 Tex : TEXCOORD0;
};

struct PS_OUT
{
    float4 Color : COLOR0;
};

VS_OUT VS(VS_IN input)
{
  VS_OUT Out = (VS_OUT)0; 

  Out.Position.x += sin ( time / 1000)/10;
  Out.Position.z += cos ( time / 1100)/5;
  Out.Position = mul(input.Position,wvp);
  Out.Tex = input.Tex;

  return Out;
}

PS_OUT PS(VS_OUT input)
{
	PS_OUT output = (PS_OUT)0;
	float2 Tex1 = input.Tex;
	float2 Tex2 = input.Tex;
	Tex1.x = input.Tex.x + (time/2000)/40;
	Tex2.x = input.Tex.x - (time/2500)/40;
			 
	Tex1.y = input.Tex.y + (time/2500)/20;
	Tex2.y = input.Tex.y - (time/2000)/30;
			
	Tex1.x = Tex1.x + (sin(Tex1.y*5)*sin(time/1010)/6);
	Tex1.x = Tex1.x + (sin(Tex1.y*50)*sin(time/800)/10);
	Tex1.x = Tex1.x + (sin(Tex1.y*75)*sin(time/400)/19);
	Tex1.x = Tex1.x + (sin(Tex1.y*117)*sin(time/300)/50);
	
	Tex1.y = Tex1.y + (sin(Tex1.x*5)*sin(time/1020)/6);
	Tex1.y = Tex1.y + (sin(Tex1.x*50)*sin(time/800)/10);
	Tex1.y = Tex1.y + (sin(Tex1.x*75)*sin(time/400)/19);
	Tex1.y = Tex1.y + (sin(Tex1.x*113)*sin(time/310)/50);
			
	Tex2.x = Tex2.x + (cos(Tex2.y*5)*cos(time/990)/6);
	Tex2.x = Tex2.x + (cos(Tex2.y*50)*cos(time/800)/10);
	Tex2.x = Tex2.x + (cos(Tex2.y*75)*cos(time/400)/19);
	Tex2.x = Tex2.x + (cos(Tex2.y*112)*cos(time/290)/50);
	
	Tex2.y = Tex2.y + (cos(Tex2.x*5)*cos(time/980)/6);
	Tex2.y = Tex2.y + (cos(Tex2.x*50)*cos(time/800)/10);
	Tex2.y = Tex2.y + (cos(Tex2.x*75)*cos(time/400)/19);
	Tex2.y = Tex2.y + (cos(Tex2.x*118)*cos(time/320)/50);
	
	float4 texture1 = tex2D( TextureSampler1, ((Tex1.xy/16)));
	float4 texture2 = tex2D( TextureSampler2, ((Tex2.xy/8)));
	texture1.a = 0.5;
	texture2.a = 0.5;
	output.Color = texture1 * texture2;
    
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
        ZWriteEnable = TRUE;
    }
}
