#include "Object2D.h"

Object2D::Object2D()
{
    //図形初期化
}

void Object2D::InitObject(DirectX::XMFLOAT2 _size, DirectX::XMINT2 _split, ID3D11ShaderResourceView* _assets,
                          Anime::AnimePattern _pattern, ModelSet::VerticalAlign _align)
{
    //モデル作成
    Sprite3D::InitCanvas(_size, _split, _assets, _pattern, _align);
}

void Object2D::Update()
{
    if(isActive)
    {
        Sprite3D::Update();
    }
    
}

void Object2D::Draw()
{
    if (isActive) 
    {
        Sprite3D::Draw();
    }
}

