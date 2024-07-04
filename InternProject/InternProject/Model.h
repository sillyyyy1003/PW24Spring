#pragma once
#include "DirectX3D.h"
#include "WaveFrontReader.h"

namespace ModelSet
{
	//オブジェクトによって、中心点が異なる、
	/*
	 *影：MIDDLE
	 *EFFECT/UI:TOP/MIDDLE/BOT
	 *OBJECT:BOTTOM
	 */
	enum VerticalAlign
	{
		NONE_ALIGN,
		TOP,	//縦の中心点が上
		MIDDLE,	//縦の中心点が真ん中
		BOTTOM,	//縦の中心点が底辺

	};
}

/// <summary>
/// GameObject用モデル2D/3D
/// </summary>
class Model
{

public:

	ModelData model;


public:
	Model();
	~Model();

	static ModelData Create2DModel(DirectX::XMFLOAT2 _size, DirectX::XMINT2 split,ModelSet::VerticalAlign _align);

	ModelData Create3DModel(const wchar_t* fileName);

	static ID3D11ShaderResourceView* LoadTexture(const wchar_t* _fileName);

	void SetTexture(ID3D11ShaderResourceView* texture);

	
};
