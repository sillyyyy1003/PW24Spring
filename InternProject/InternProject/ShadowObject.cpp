#include "ShadowObject.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "Collider.h"

ShadowObject::ShadowObject(Collide::ColliderType _type)
{
	switch (_type) {
    case Collide::NULL_TYPE:
    	mCollider = std::make_unique<Collider>();
    	break;
    case Collide::SPHERE:
    	mCollider = std::make_unique<SphereCollider>();
    	break;
    case Collide::SQUARE:
        mCollider = std::make_unique<BoxCollider>();
    	break;
    }
    mCollider->Collider::InitType(_type);
}

void ShadowObject::InitShadow(DirectX::XMFLOAT2 _size, DirectX::XMINT2 _split, ID3D11ShaderResourceView* _assets)
{
    
    //影の作成
    mSprite = std::make_unique<Object2D>();
    mSprite->InitObject(_size, _split, _assets, Anime::AnimePattern::SINGLE_PATTERN, ModelSet::VerticalAlign::MIDDLE);

    //コライダーの作成
    InitCollider(_size);
}

void ShadowObject::Update()
{
    //オブジェクト
    mSprite->Update();

    //当たり判定
    //Get Size
    DirectX::XMFLOAT3 size = mSprite->mScale * mExtents;

	//Set to collider
    mCollider->Update(mSprite->GetPos(), mSprite->GetRotate(), size);
}

void ShadowObject::InitCollider(DirectX::XMFLOAT2 _size)
{
    mCollider->InitCollider(_size, mSprite->GetPos());
    mExtents = mCollider->GetExtents();
}

void ShadowObject::Draw()
{
    mSprite->Draw();
}
