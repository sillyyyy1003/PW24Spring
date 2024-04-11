#pragma once


//Color
struct Color
{
	float r, g, b, a;
};

//model
struct ModelData
{
	ID3D11Buffer* vertexBuffer;
	ID3D11ShaderResourceView* texture;
	ID3D11Buffer* indexBuffer;
	int	indexNum;

};

//Constant Buffer
struct ConstBuffer
{
	DirectX::XMMATRIX matrixWorld;//位置
	DirectX::XMMATRIX matrixNormal;//法線
	DirectX::XMMATRIX matrixUV;//uv
	DirectX::XMFLOAT4 materialDiffuse;
	DirectX::XMFLOAT3 eyePos;
	float objCbPad0;
	unsigned int isLight;
	int dummy2, dummy3, dummy4;
};

//VertexData
struct Vertex3D
{
	DirectX::XMFLOAT3 position;	//世界座標
	DirectX::XMFLOAT2 uv;		//uv座標
	DirectX::XMFLOAT3 normal;	//法線
};

struct Light
{
	DirectX::XMFLOAT3 lightStrength;//light strength/Color
	float fallOffStart;//フォールオフの開始点:点光源・スポットライト
	DirectX::XMFLOAT3 lightDir;//方向：平行・スポットライト
	float fallOffEnd;//フォールオフの終了点:点光源・スポットライト
	DirectX::XMFLOAT3 lightPos;//光源の位置
	float spotPower; // スポットライトの強度
};

struct Material
{
	DirectX::XMFLOAT4 diffuseAlbedo; // 材質の拡散反射率
	DirectX::XMFLOAT3 fresnelR0; // RF(0)値、すなわち材質の反射特性
	float roughness; // 材質の粗さ
};

/*packing rule
1、元素会被包装到float4; 2、一个元素不能被分散到两个float4中
*/

