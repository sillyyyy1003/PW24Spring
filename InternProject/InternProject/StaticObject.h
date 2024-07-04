#pragma once
#include "Object2D.h"

/// @brief 背景などに使われてるオブジェクト
///	中心点が真ン中
class StaticObject
{
public:
	std::unique_ptr<Object2D> mObj = nullptr;
public:
	StaticObject();
	~StaticObject();
	void InitObject(DirectX::XMFLOAT2 _size, DirectX::XMINT2 _split, ID3D11ShaderResourceView* _assets);

	void Update();

	void Draw();
	
};