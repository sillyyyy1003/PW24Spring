#include "CanvasUI.h"

#include "DebugManager.h"

CanvasUI::CanvasUI()
{
	mSprite = std::make_unique<Sprite2D>();
}

CanvasUI::~CanvasUI()
{
}

void CanvasUI::InitCanvas(DirectX::XMFLOAT2 _size, DirectX::XMINT2 _split, ID3D11ShaderResourceView* _assets,
	Anime::AnimePattern _pattern, ModelSet::VerticalAlign _align)
{
	mSprite->InitSprite(_size, _split, _assets, _pattern, _align);
}

void CanvasUI::InitCanvas(DirectX::XMFLOAT2 _size, DirectX::XMINT2 _split, ID3D11ShaderResourceView* _assets)
{
	mSprite->InitSprite(_size, _split, _assets, Anime::SINGLE_PATTERN, ModelSet::MIDDLE);
}

void CanvasUI::Update()
{
	mSprite->Update();
}

void CanvasUI::Draw()
{
	if(isActive)
	{
		mSprite->Draw();
	}
}
