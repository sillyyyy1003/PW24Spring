struct PS_IN
{
	float4 pos : SV_Position;
	float2 tex : TEXCOORD;
	float4 normal : NORMAL;
};

Texture2D myTexture : register(t0);
SamplerState mySampler : register(s0);

cbuffer ConstBuffer : register(b0)
{
	matrix matrixWorld;
	matrix matrixNormal;
	matrix matrixUV;
	float4 materialDiffuse;

	unsigned int isLight;
	int dummy2, dummy3, dummy4;
}
float4 ps_main(PS_IN input) : SV_Target
{
	if (!isLight)
    {
        float4 color = myTexture.Sample(mySampler, input.tex);
        float4 ambientFactor = float4(0.6, 0.6, 0.6, 1.0f);
        //float4 ambientFactor = float4(1.f, 1.f, 1.f,1.0f);
        return color * materialDiffuse * ambientFactor;
    }

	//Set Normal
 //   float3 pos = input.pos.xyz;
 //   float3 normal = float3(pos.x, pos.y,-1.f);

	////Set Light Position in front of the object
 //   float3 lightPos = float3(pos.x,pos.y , pos.z - 0.2f);
 //   float3 toLightVec = lightPos - pos;
 //   float toLightLength = length(toLightVec);

	
	//lightPos = normalize(lightPos);
	//normal = normalize(normal);
 //   float diffusePower = saturate(dot(lightPos, normal));

 //   float attenuation = saturate(1.0f - toLightLength / 3.f);
 //   attenuation = pow(attenuation, 2.0f);
 //   float4 lightAmbient = { 0.4, 0.4, 0.4, 0.4 };
 //   lightAmbient *= diffusePower * attenuation;

 //   
 //   attenuation = pow(attenuation, 2.0f);
    float4 color = myTexture.Sample(mySampler, input.tex);
    color = color * materialDiffuse;

	return color;
	
}