#pragma once
#include "Sprite2D.h"

///Summary
///UI等に使われてる
///Summary
class CanvasUI
{
public:
	
	//表示の切り替え
	bool isActive = true;

	std::unique_ptr<Sprite2D> mSprite = nullptr;
public:

	CanvasUI();

	~CanvasUI();

	void InitCanvas(DirectX::XMFLOAT2 _size, DirectX::XMINT2 _split, ID3D11ShaderResourceView* _assets, Anime::AnimePattern _pattern, ModelSet::VerticalAlign _align);
	void InitCanvas(DirectX::XMFLOAT2 _size, DirectX::XMINT2 _split, ID3D11ShaderResourceView* _assets);

	void SetPosZ(float _posZ) { mSprite->mPos.z = _posZ; };

	const bool GetActive() { return isActive; };
	void SetActive(bool _isActive) { isActive = _isActive; };

	void Update();

	void Draw();
};

