#include "StaticObject.h"

StaticObject::StaticObject()
{
	mObj = std::make_unique<Object2D>();
	
}

StaticObject::~StaticObject()
{
}

void StaticObject::InitObject(DirectX::XMFLOAT2 _size, DirectX::XMINT2 _split, ID3D11ShaderResourceView* _assets)
{
	mObj->InitObject(_size, _split, _assets, Anime::SINGLE_PATTERN, ModelSet::MIDDLE);
}

void StaticObject::Update()
{
	mObj->Update();
}

void StaticObject::Draw()
{
	mObj->Draw();
}
