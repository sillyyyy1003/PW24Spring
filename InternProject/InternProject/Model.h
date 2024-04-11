#pragma once
#include "DirectX3D.h"
#include "WaveFrontReader.h"

/// <summary>
/// GameObject用モデル2D/3D
/// </summary>
class Model{

public:
	
	ModelData model;

public:

	~Model();

	static ModelData Create2DModel(DirectX::XMFLOAT2 _size, DirectX::XMINT2 split);

	static ModelData Create3DModel(const wchar_t* fileName);

	static ID3D11ShaderResourceView* LoadTexture(const wchar_t* fileName);
	
	void SetTexture(ID3D11ShaderResourceView* texture);
	/*
	ModelData Load3DModel(const wchar_t* fileName);

	ID3D11ShaderResourceView* LoadTexture(const wchar_t* fileName);
	*/
};
