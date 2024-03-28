#pragma once
#include "DirectX3D.h"
#include "WaveFrontReader.h"

//Color
struct Color {
	float r, g, b, a;
};

//model
struct ModelData {
	ID3D11Buffer* vertexBuffer;
	ID3D11ShaderResourceView* texture;
	ID3D11Buffer* indexBuffer;
	int	indexNum;

};

//Constant Buffer
struct ConstBuffer {
	DirectX::XMMATRIX matrixWorld;
	DirectX::XMMATRIX matrixNormal;
	DirectX::XMMATRIX matrixUV;
	DirectX::XMFLOAT4 materialDiffuse;
	DirectX::XMFLOAT3 lightDir;		//光の向き
	DirectX::XMFLOAT4 ambientLight;	//光の強さ

	bool isLight;
};

//VertexData
struct Vertex3D {
	DirectX::XMFLOAT3 position;	//世界座標
	DirectX::XMFLOAT2 uv;			//uv座標
	DirectX::XMFLOAT3 normal;	//法線
};


/// <summary>
/// GameObject用モデル2D/3D
/// </summary>
class Model{

public:
	
	ModelData model;

public:

	~Model();

	static ModelData Create2DModel(DirectX::XMFLOAT2 _size, DirectX::XMINT2 split);

	static ModelData Create3DModel(WaveFrontReader<uint16_t> reader);

	//Need Fix
	void Set2DModel(DirectX::XMFLOAT2 _size, DirectX::XMINT2 split);
	
	void SetTexture(ID3D11ShaderResourceView* texture);
	/*
	ModelData Load3DModel(const wchar_t* fileName);

	ID3D11ShaderResourceView* LoadTexture(const wchar_t* fileName);
	*/
};
