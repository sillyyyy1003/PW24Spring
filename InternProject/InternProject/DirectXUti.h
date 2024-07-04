#pragma once
#include <d3d11.h>
#include <cmath>
#include <wrl/client.h>

//Color
struct Color
{
	float r, g, b, a;
};

//model
struct ModelData
{
	Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;
	Microsoft::WRL::ComPtr<ID3D11Buffer> indexBuffer;
	int	indexNum;

};

//Constant Buffer
struct ConstBuffer
{
	DirectX::XMMATRIX matrixWorld;//位置
	DirectX::XMMATRIX matrixNormal;//法線
	DirectX::XMMATRIX matrixUV;//uv
	DirectX::XMFLOAT4 materialDiffuse;
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

/// @brief Compare Float and avoid digits cancellation
inline bool CompFloat(float a, float b) {
	float rel_epsilon = 1e-5f;
	float abs_epsilon = 1e-6f;
	float diff = std::fabs(a - b);
	if (diff <= abs_epsilon) {
		return true;
	}
	return diff <= rel_epsilon * std::fmax(std::fabs(a), std::fabs(b));
};

/// @brief 
/// @return
/// -1 smaller
///	1  bigger
///	0  equal
inline int CompResult(float a, float b)
{
	if (!CompFloat(a, b)) { return (a < b) ? -1 : 1; }
	else{ return 0; }
};

inline DirectX::XMFLOAT3 operator*(const DirectX::XMFLOAT3& lhs, const DirectX::XMFLOAT3& rhs)
{
	return DirectX::XMFLOAT3(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
}


