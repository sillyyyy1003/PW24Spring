#include "Fade.h"
#include "Game.h"
#include "xa2.h"


Fade::Fade()
{
	mFadePanel = std::make_unique<CanvasUI>();
	mFadePanel->InitCanvas({ 1280.f,720.f }, { 1,1 }, Game::Get()->GetModelManager()->fade.Get(), Anime::SINGLE_PATTERN, ModelSet::MIDDLE);

	mFadePanel->SetPosZ(Game::Get()->GetLayerManager()->SetLayers(Layer::FADE));
	mState = Fade::None; 
}

Fade::~Fade()
{
}

void Fade::Update()
{
	float& alpha = mFadePanel->mSprite->mMaterialDiffuse.w;

	switch (mState) {
	case Fade_In:
	
		// パネルのRGBAのAの値を、減らす
		alpha -= mFadeSpeed; 
		// alphaが0.0f以下になったら、フェードイン終了
		if (alpha <= 0.0f)
		{
			mState = Fade::None; // 何もしない状態
			if (Game::Get()->GetSceneManager()->GetScene() == scene::STAGE)
			{
				switch(Game::Get()->GetSceneManager()->GetStage())
				{
				case scene::STAGE1_1:
					XA_Stop(SE_Present);
					XA_Play(BGM_Stage1);
					break;
				case scene::STAGE1_2:
					XA_Stop(SE_Present);
					XA_Play(BGM_Stage2);
					break;
				case scene::STAGE1_3:
					XA_Stop(SE_Present);
					XA_Play(BGM_Stage3);
					break;
				}
			}
			
		}
			
		break;
	case Fade_Out:
		// パネルのRGBAのAの値を、増やす
		alpha += mFadeSpeed;// * Game::Get()->fadeTime;
		// alphaが1.0f以上になったら、フェードアウト終了
		if (alpha >= 1.0f)
		{
			mState = Fade::None;
	
		}
		break;
	}

	
}

void Fade::Draw()
{
	mFadePanel->Draw();
}

void Fade::FadeIn()
{
	if (mState == Fade::None)
	{
		mState = Fade::Fade_In;
	}

}

void Fade::FadeOut()
{
	if (mState == Fade::None) {
		mState = Fade::Fade_Out;

		//リザルトシーン行く前にSE
		if (Game::Get()->GetSceneManager()->GetNextScene() == scene::RESULT)
		{
			XA_Play(SE_Combine);
		}
	}
		
}
