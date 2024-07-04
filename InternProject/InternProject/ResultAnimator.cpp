#include "ResultAnimator.h"

#include "Game.h"
#include "KInput.h"
#include "Scene.h"
#include "xa2.h"

bool ResultAnimator::Move()
{
	int stageInfo = Game::Get()->GetSceneManager()->GetStage();

	// mStageAnime[stageInfo][2]だけ動く距離が違うために調整する
	mStageAnime[stageInfo][0]->mSprite->mPos.y += 0.1f * (mMoveSpeed * 1.1f);

	// 画像が定位置につくまでに一周するように計算する（ROTATETIMEで回転数を調整）
	mStageAnime[stageInfo][0]->mSprite->mRotation.z += 360 / (86 / (mMoveSpeed * 1.1f) / mRotateTime); // 回転速度（度）

	if (mStageAnime[stageInfo][0]->mSprite->mPos.y > 0.0f)
	{
		// 画像3を指定の位置に止める
		mStageAnime[stageInfo][0]->mSprite->mPos.y = 0.0f;
		mStageAnime[stageInfo][0]->mSprite->mRotation.z = 0.0f; // 回転角度をリセット

		// カウント開始
		mWaitCount++;

		if (mWaitCount > mWaitLimit)
		{
			// 画像1が右上から真ん中に降りてくる
			mStageAnime[stageInfo][1]->mSprite->mPos.x -= 0.157f * mMoveSpeed;
			mStageAnime[stageInfo][1]->mSprite->mPos.y -= 0.1f * mMoveSpeed;

			// 画像をZ軸を中心に回転させる
			mStageAnime[stageInfo][1]->mSprite->mRotation.z += 360 / (76 / mMoveSpeed / mRotateTime); // 回転速度（度）

			if (mStageAnime[stageInfo][1]->mSprite->mPos.y < 0.0f)
			{
				// 画像1を指定の位置に止める
				mStageAnime[stageInfo][1]->mSprite->mPos.x = 0.0f;
				mStageAnime[stageInfo][1]->mSprite->mPos.y = 0.0f;
				mStageAnime[stageInfo][1]->mSprite->mRotation.z = 0.0f; // 回転角度をリセット

				// カウント開始
				mWatiCount2++;

				if (mWatiCount2 > mWaitLimit)
				{
					// 画像2を左上から真ん中に移動させる
					mStageAnime[stageInfo][2]->mSprite->mPos.x += 0.157f * mMoveSpeed;
					mStageAnime[stageInfo][2]->mSprite->mPos.y -= 0.1f * mMoveSpeed;
					mStageAnime[stageInfo][2]->mSprite->mRotation.z += 360.0f / (76.0f / mMoveSpeed / mRotateTime); // 回転速度（度）

					if (mStageAnime[stageInfo][2]->mSprite->mPos.y < 0.0f)
					{
						// 画像2を指定の位置に止める
						mStageAnime[stageInfo][2]->mSprite->mPos.x = 0.0f;
						mStageAnime[stageInfo][2]->mSprite->mPos.y = 0.0f;
						mStageAnime[stageInfo][2]->mSprite->mRotation.z = 0.0f; // 回転角度をリセット

						// 画像の移動が完了
						return true;
					}
				}
			}
		}
	}


	// 画像の移動が途中
	return false;
}

ResultAnimator::ResultAnimator()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			mStageAnime[j][i] = std::make_unique<CanvasUI>();
		}
	}

	mSkip = std::make_unique<CanvasUI>();
	mSkip->InitCanvas({ 351,65 }, { 1,1 }, Game::Get()->GetModelManager()->SkipButton.Get());

	mStageAnime[scene::STAGE1_1][0]->InitCanvas({ 502, 642 }, { 1,1 }, Game::Get()->GetModelManager()->ResultComic[scene::STAGE1_1][0].Get());
	mStageAnime[scene::STAGE1_1][1]->InitCanvas({ 650,476 } , { 1,1 }, Game::Get()->GetModelManager()->ResultComic[scene::STAGE1_1][1].Get());
	mStageAnime[scene::STAGE1_1][2]->InitCanvas({ 707,503 }, { 1,1 }, Game::Get()->GetModelManager()->ResultComic[scene::STAGE1_1][2].Get());

	mStageAnime[scene::STAGE1_2][0]->InitCanvas({ 650,476 }, { 1,1 }, Game::Get()->GetModelManager()->ResultComic[scene::STAGE1_2][0].Get());
	mStageAnime[scene::STAGE1_2][1]->InitCanvas({ 707,503 }, { 1,1 }, Game::Get()->GetModelManager()->ResultComic[scene::STAGE1_2][1].Get());
	mStageAnime[scene::STAGE1_2][2]->InitCanvas({ 502, 642 }, { 1,1 }, Game::Get()->GetModelManager()->ResultComic[scene::STAGE1_2][2].Get());

	mStageAnime[scene::STAGE1_3][0]->InitCanvas({ 502, 642 }, { 1,1 }, Game::Get()->GetModelManager()->ResultComic[scene::STAGE1_3][0].Get());
	mStageAnime[scene::STAGE1_3][1]->InitCanvas({ 707,503 }, { 1,1 }, Game::Get()->GetModelManager()->ResultComic[scene::STAGE1_3][1].Get());
	mStageAnime[scene::STAGE1_3][2]->InitCanvas({ 650,476 }, { 1,1 }, Game::Get()->GetModelManager()->ResultComic[scene::STAGE1_3][2].Get());
}

void ResultAnimator::Init()
{
	
	//位置のリセット
	mStageAnime[Game::Get()->GetSceneManager()->GetStage()][0]->mSprite->mPos= { 0.0f,-8.6f,0.5f }; 

	mStageAnime[Game::Get()->GetSceneManager()->GetStage()][1]->mSprite->mPos = { 12.0f,7.6f,0.4f };

	mStageAnime[Game::Get()->GetSceneManager()->GetStage()][2]->mSprite->mPos = { -12.1f,7.6f,0.3f };

	//回転のリセット
	for(int i=0;i<3;i++)
	{
		mStageAnime[Game::Get()->GetSceneManager()->GetStage()][i]->mSprite->mRotation.z = 0.f;
	}

	//Timer Rest
	mWaitCount = 0;
	mWatiCount2 = 0;

	//Animeのトリガーをリセット
	Game::Get()->SetResultAnime(false);

	mSkip->SetActive(false);
	mSkip->mSprite->mPos = { (640 - 200) * SCREEN_PARA,(360 - 50) * SCREEN_PARA,0.2f };


}

void ResultAnimator::Update()
{

	if(Move())
	{
		Game::Get()->GetSceneManager()->mStageHolder[Game::Get()->GetSceneManager()->GetStage()]->SetCompleted(true);
	}

	if(Game::Get()->GetSceneManager()->mStageHolder[Game::Get()->GetSceneManager()->GetStage()]->GetCompleted())
	{
		if(KInput::Get()->GetKeyTrigger(DIK_SPACE))
		{
			//音声
			XA_Play(SE_Result);

			//Reset Animation
			Game::Get()->SetResultAnime(false);

			//Game::Get()->GetSceneManager()->mStageHolder[Game::Get()->GetSceneManager()->GetStage()]->SetCompleted(true);
			Game::Get()->GetResultManager()->SetButtonNum(2);
		}
	}

	for (int i = 0; i < 3; i++)
	{
		mStageAnime[Game::Get()->GetSceneManager()->GetStage()][i]->Update();
	}

	if (Game::Get()->GetSceneManager()->mStageHolder[Game::Get()->GetSceneManager()->GetStage()]->GetCompleted())
	{
		mSkip->SetActive(true);
	}


}

void ResultAnimator::Draw()
{
	mSkip->Draw();
	mStageAnime[Game::Get()->GetSceneManager()->GetStage()][0]->Draw();
	mStageAnime[Game::Get()->GetSceneManager()->GetStage()][1]->Draw();
	mStageAnime[Game::Get()->GetSceneManager()->GetStage()][2]->Draw();
}
