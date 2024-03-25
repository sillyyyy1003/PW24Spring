struct VS_IN
{
	float4 pos : POSITIONT;
	float2 tex : TEX;
	float4 normal : NORMAL;
};

struct VS_OUT
{
	float4 pos : SV_POSITION;
	float2 tex : TEXCOORD;
	float4 normal : NORMAL;
};

//cbuffer:defination of Constant Buffer in hlsl
cbuffer ConstBuffer : register(b0)
{
	//顶点着色器负责处理世界坐标，顶点法线（即每个顶点的朝向），以及纹理坐标
	matrix matrixWorld;
	matrix matrixNormal;
	matrix matrixUV;
};


VS_OUT vs_main(VS_IN input )
{
	VS_OUT output;
	//ワールド座標
	output.pos = mul(input.pos, matrixWorld);
	
	//UV
	float4 tex4;
	tex4.xy = input.tex;
	tex4.z = 0;
	tex4.w = 1;
	output.tex = mul(tex4, matrixUV).xy;
	
	//LIGHT
	output.normal = mul(input.normal, matrixNormal);
	
	return output;
}