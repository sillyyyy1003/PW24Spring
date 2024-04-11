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
	
	//�ٹ�Դ�����Ӱ푤�Ӌ��
	//float3 lightVector = lightDir;
	float3 lightVector = float3(1, -1, 1);
	float3 pixelNormal = input.normal.xyz;
	//float4 amLight = ambientLight;
	float4 ambientLight = float4(0.1f, 0.1f, 0.1f, 0.0f);
	
	//��Ҏ��
	lightVector = normalize(lightVector);
	pixelNormal = normalize(pixelNormal);
	
	//dot:�ڷe->�⾀�ȱ���Ȥ��g�νǶ�
	float diffusePower = dot(lightVector, pixelNormal);
	
	//��ɢ�����Ώ��Ȥ����Ĥʹ����ڤ˅����
	diffusePower = saturate(diffusePower);
	
	//��ɢ�����Ώ��Ȥ� 0.2f ���С�����ʤ�ʤ��褦
	diffusePower = max(diffusePower, 0.2f);
	
	float4 textureColor = myTexture.Sample(mySampler, input.tex);
	
	float4 pixelColor = textureColor * diffusePower;
	pixelColor.a = textureColor.a;
	
	//�ڭh�����Ӱ푤�Ӥ���
	pixelColor = pixelColor + ambientLight;
	
	return pixelColor;
	
}