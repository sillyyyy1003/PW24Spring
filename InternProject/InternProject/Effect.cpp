#include "Effect.h"
#include "Game.h"
#include "GameObject2D.h"
#include "Object2D.h"

Effect::Effect()
{
    mSprite = std::make_unique<Sprite3D>();

}

Effect::~Effect()
{
}

void Effect::InitEffect(DirectX::XMFLOAT2 _size, DirectX::XMINT2 _split, ID3D11ShaderResourceView* _assets)
{
	mSprite->InitCanvas(_size, _split, _assets, Anime::SINGLE_PATTERN, ModelSet::MIDDLE);
}

void Effect::Update()
{
	if(isTrace)
	{
        DirectX::XMFLOAT3 tracePos = { 0,0,0 };

        //稼働中のオブジェクトを探す
        for (auto& element : Game::Get()->GetObjectList())
        {
            //目標オブジェクトに追跡
            if (element->GetIsTarget()) {

                //位置を獲得
                tracePos = element->mObj->mPos;
                this->mSprite->mPos = tracePos;
                //z軸の位置をずらす
                this->mSprite->mPos.z = tracePos.z - 0.1f;
                break;

            }
        }
	}

    mSprite->Update();
}

void Effect::Draw()
{
    if(isActive)
    {
        mSprite->Draw();
        
    }
	
}

void Effect::SetActive(bool isActive)
{
    this->isActive = isActive;

    if(isActive)
    {
        mSprite->GetAnimation()->SetLoop(true);
        mSprite->GetAnimation()->SetPlaying(true);
    }else
    {
        mSprite->GetAnimation()->SetPlaying(false);
    }
}

