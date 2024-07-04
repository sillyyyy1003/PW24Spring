#pragma once
#include "Sprite3D.h"

/// @brief コライダー無しのオブジェクト GameObject用
class Object2D :public Sprite3D
{
public:
	
	//画面に表示するかどうか？
	bool isActive = true;

public:

	Object2D();

	virtual void InitObject(DirectX::XMFLOAT2 _size, DirectX::XMINT2 _split, ID3D11ShaderResourceView* _assets, Anime::AnimePattern _pattern,ModelSet::VerticalAlign _align);

	void Update() override;

	void Draw() override;

	virtual ~Object2D() = default;
};

