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
		return color * materialDiffuse;
	}
	
	//①光源からの影響を計算
	//float3 lightVector = lightDir;
	float3 lightVector = float3(1, -1, 1);
	float3 pixelNormal = input.normal.xyz;
	//float4 amLight = ambientLight;
	float4 ambientLight = float4(0.1f, 0.1f, 0.1f, 0.0f);
	
	//正規化
	lightVector = normalize(lightVector);
	pixelNormal = normalize(pixelNormal);
	
	//dot:内積->光線と表面との間の角度
	float diffusePower = dot(lightVector, pixelNormal);
	
	//拡散反射光の強度を合理的な範囲内に収める
	diffusePower = saturate(diffusePower);
	
	//拡散反射光の強度を 0.2f より小さくならないよう
	diffusePower = max(diffusePower, 0.2f);
	
	float4 textureColor = myTexture.Sample(mySampler, input.tex);
	
	float4 pixelColor = textureColor * diffusePower;
	pixelColor.a = textureColor.a;
	
	//②環境光の影響を加える
	pixelColor = pixelColor + ambientLight;
	
	return pixelColor;
	
}