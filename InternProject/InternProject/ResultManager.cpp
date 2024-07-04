#include "ResultManager.h"
#include "Game.h"
#include "KInput.h"
#include "xa2.h"

ResultManager::ResultManager()
{

	resultTitle=std::make_unique<CanvasUI>();//リザルトタイトル
	resultBg=std::make_unique<CanvasUI>();//リザルト背景
	clearStepTitle=std::make_unique<CanvasUI>();//ステップ数タイトル
	clearScoreTitle=std::make_unique<CanvasUI>();//★数タイトル

	for (int i = 0; i < 3; i++)
	{
		resultButton[i] = std::make_unique<CanvasUI>();
	}

	for (int i = 0; i < 5; i++)
	{
		star[i] = std::make_unique<CanvasUI>();
		starShadow[i] = std::make_unique<CanvasUI>();
	}

	resultProcessor=std::make_unique<ResultProcess>();//ステップ数

}

ResultManager::~ResultManager()
{
}

void ResultManager::Init()
{
	resultTitle->InitCanvas({ 430, 104 }, { 1, 1 }, Game::Get()->GetModelManager()->resultTitle.Get(), Anime::SINGLE_PATTERN, ModelSet::MIDDLE);//リザルトタイトル
	resultBg->InitCanvas({ 1029, 713 }, { 1, 1 }, Game::Get()->GetModelManager()->resultBg.Get(), Anime::SINGLE_PATTERN, ModelSet::MIDDLE);//リザルト背景
	clearStepTitle->InitCanvas({ 375, 72 }, { 1, 1 }, Game::Get()->GetModelManager()->resultStepTitle.Get(), Anime::SINGLE_PATTERN, ModelSet::MIDDLE);//ステップ数タイトル
	clearScoreTitle->InitCanvas({ 139, 66 }, { 1, 1 }, Game::Get()->GetModelManager()->resultScoreTitle.Get(), Anime::SINGLE_PATTERN, ModelSet::MIDDLE);//★数タイトル

	for (int i = 0; i < 3; i++)
	{
		resultButton[i] = std::make_unique<CanvasUI>();
		resultButton[i]->mSprite->GetAnimation()->SetPlaying(false);
	}

	resultButton[Result::AGAIN]->InitCanvas({ 299, 96 }, { 1,2 }, Game::Get()->GetModelManager()->resultButton[Result::AGAIN].Get(), Anime::MULTI_PATTERN, ModelSet::MIDDLE);
	resultButton[Result::NEXT]->InitCanvas({ 316, 107 }, { 1,2 }, Game::Get()->GetModelManager()->resultButton[Result::NEXT].Get(), Anime::MULTI_PATTERN, ModelSet::MIDDLE);
	resultButton[Result::RETURN]->InitCanvas({ 624, 114 }, { 1,2 }, Game::Get()->GetModelManager()->resultButton[Result::RETURN].Get(), Anime::MULTI_PATTERN, ModelSet::MIDDLE);


	for (int i = 0; i < 5; i++)
	{
		star[i] = std::make_unique<CanvasUI>();
		starShadow[i] = std::make_unique<CanvasUI>();
		star[i]->InitCanvas({88,85},{1,1},Game::Get()->GetModelManager()->resultStar, Anime::SINGLE_PATTERN, ModelSet::MIDDLE);
		starShadow[i]->InitCanvas({ 88,85 }, { 1,1 }, Game::Get()->GetModelManager()->resultStarShadow, Anime::SINGLE_PATTERN, ModelSet::MIDDLE);

		star[i]->mSprite->mPos = { -2.1f + 1.5f * i ,1.5f ,0.3f };
		starShadow[i]->mSprite->mPos = { -2.1f + 1.5f * i ,1.5f ,0.3f };
	}

	resultProcessor = std::make_unique<ResultProcess>();//ステップ数
	resultProcessor->Init(1.8f, 0.0f, 0.95f, 10.f);

	//座標
	resultBg->mSprite->mPos={ 0.0f, 0.0f ,Game::Get()->GetLayerManager()->SetLayers(Layer::UI_PANEL)};
	resultTitle->mSprite->mPos = { 0.0f,3.1f,Game::Get()->GetLayerManager()->SetLayers(Layer::UI_WORD) };
	clearScoreTitle->mSprite->mPos = { -4.0f ,1.5f ,Game::Get()->GetLayerManager()->SetLayers(Layer::UI_WORD) };
	clearStepTitle->mSprite->mPos = { -2.5f ,0.0f,Game::Get()->GetLayerManager()->SetLayers(Layer::UI_WORD) };
	resultButton[Result::AGAIN]->mSprite->mPos = { 2.0f ,-1.5f ,Game::Get()->GetLayerManager()->SetLayers(Layer::FRONT_UI) };
	resultButton[Result::NEXT]->mSprite->mPos = { -2.3f ,-1.5f ,Game::Get()->GetLayerManager()->SetLayers(Layer::FRONT_UI) };
	resultButton[Result::RETURN]->mSprite->mPos = { 0.0f,-3.0f,Game::Get()->GetLayerManager()->SetLayers(Layer::FRONT_UI) };

	

	resultBg->mSprite->mScale = { 0.95f,0.95f,1.0f };
	resultTitle->mSprite->mScale = { 0.95f,0.95f,1.0f };
	clearScoreTitle->mSprite->mScale = { 0.95f,0.95f,1.0f };
	clearStepTitle->mSprite->mScale = { 0.95f,0.95f,1.0f };
	resultButton[Result::AGAIN]->mSprite->mScale = { 0.95f,0.95f,1.0f };
	resultButton[Result::NEXT]->mSprite->mScale = { 0.95f,0.95f,1.0f };
	resultButton[Result::RETURN]->mSprite->mScale = { 0.95f,0.95f,1.0f };


	mButtonNum = 0;
}

void ResultManager::Update()
{
	//星獲得
	mStarNum = GetScore(Game::Get()->Get()->GetSceneManager()->mStageHolder[Game::Get()->Get()->GetSceneManager()->GetStage()]->GetStep(), starStandard);

	/*mStarNum = 3;*/

	DoKeyEvent();
	ButtonUpdate();


	resultBg->Update();
	resultTitle->Update();
	

	for(int i=0;i<3;i++)
	{
		resultButton[i]->Update();
	}

	for (int i = 0; i < mStarNum; i++)
	{
		star[i]->Update();
	}
	for (int i = 4; i + 1 > mStarNum; i--)
	{
		starShadow[i]->Update();
	}

}

void ResultManager::Draw()
{
	resultBg->Draw();
	resultTitle->Draw();
	clearScoreTitle->Draw();
	clearStepTitle->Draw();

	resultButton[0]->mSprite->GetAnimation()->SetFrameY(1);
	for (int i = 0; i < 3; i++)
	{
		resultButton[i]->Draw();
	}

	for (int i = 0; i < mStarNum; i++)
	{
		star[i]->Draw();
	}
	for (int i = 4; i + 1 > mStarNum; i--)
	{
		starShadow[i]->Draw();
	}

	resultProcessor->Print(1.5f,0.0,Game::Get()->GetSceneManager()->mStageHolder[Game::Get()->GetSceneManager()->GetStage()]->GetStep(), Debug::LEFT);
}

void ResultManager::DoKeyEvent()
{

	if (KInput::Get()->GetKeyTrigger(DIK_UPARROW)) {
		XA_Play(SE_Select);
		switch (mButtonNum)
		{
		case Result::NEXT:
			mButtonNum = Result::RETURN;
			break;
		case Result::AGAIN:
			mButtonNum = Result::RETURN;
			break;
		case Result::RETURN:
			mButtonNum = Result::NEXT;
			break;
		default:
			break;
		}
		return;
	}

	if (KInput::Get()->GetKeyTrigger(DIK_DOWNARROW)) {
		XA_Play(SE_Select);
		switch (mButtonNum)
		{
		case Result::NEXT:
			mButtonNum = Result::RETURN;
			break;
		case Result::AGAIN:
			mButtonNum = Result::RETURN;
			break;
		case Result::RETURN:
			mButtonNum = Result::NEXT;
			break;
		default:
			break;
		}
		return;
	}

	if (KInput::Get()->GetKeyTrigger(DIK_RIGHTARROW)) {
		XA_Play(SE_Select);
		switch (mButtonNum)
		{
		case Result::NEXT:
			mButtonNum = Result::AGAIN;
			break;
		case Result::AGAIN:
			mButtonNum = Result::NEXT;
			break;
		case Result::RETURN:
			break;
		default:
			break;
		}
		return;
	}

	if (KInput::Get()->GetKeyTrigger(DIK_LEFTARROW)) {
		XA_Play(SE_Select);
		switch (mButtonNum)
		{
		case Result::NEXT:
			mButtonNum = Result::AGAIN;
			break;
		case Result::AGAIN:
			mButtonNum = Result::NEXT;
			break;
		case Result::RETURN:
			break;
		default:
			break;
		}
		return;
	}

	if(KInput::Get()->GetKeyTrigger(DIK_SPACE))
	{
		XA_Play(SE_Select);
		isInput = true;
	}


}

void ResultManager::ButtonUpdate()
{
	if(isInput)
	{
		XA_Play(SE_SelectDecide);
		mResultCounter = 0;//reset Count
		switch (mButtonNum)
		{
		case Result::AGAIN://もう一度同じステージへ
			
			//同じステージだから、直接初期化をもう一回やったらいい
			Game::Get()->Get()->GetSceneManager()->ChangeScene(scene::STAGE,scene::FADE);
			
			isInput = false;
			break;
		case Result::RETURN://タイトルへ

			Game::Get()->Get()->GetSceneManager()->ChangeScene(scene::STAGESELECT, scene::FADE);
			
			isInput = false;
			break;
		case Result::NEXT://次のステージへ

			//新しステージをセット
			int stageInfo = Game::Get()->GetSceneManager()->GetStage();
			stageInfo++;
			//最大領域に超えたら
			if (stageInfo > 2)
			{
				Game::Get()->Get()->GetSceneManager()->ChangeScene(scene::TITLE, scene::FADE);
			}else
			{
				//設定
				Game::Get()->GetSceneManager()->SetNextStage(static_cast<scene::StageInfo>(stageInfo));
				//画面遷移開始
				Game::Get()->Get()->GetSceneManager()->ChangeScene(scene::STAGE, scene::FADE);
			}
			isInput = false;
			break;
		}
	}

	for (int i = 0; i < 3; i++) {
		if (mButtonNum == i) {
			resultButton[i]->mSprite->GetAnimation()->SetFrameY(1);
			ObjectMove(resultButton[i].get(), 0.1f, 0.03f);
		}
		else {
			resultButton[i]->mSprite->GetAnimation()->SetFrameY(0);
		}
	}
}

void ResultManager::ObjectMove(CanvasUI* ui, float moveSpeed, float moveHeight)
{
	float rate = 0.1f;
	ui->mSprite->mPos.y = ui->mSprite->mPos.y + moveHeight * rate * sinf(mResultCounter * moveSpeed);
	mResultCounter++;
}

void ResultManager::SetStandard(std::vector<int> _standard)
{
	if (_standard.size() == 4)
	{
		starStandard = _standard;
	}
}

int ResultManager::GetScore(int resultStep, std::vector<int> StarNum)
{
	//星５の判定
	if (resultStep <= StarNum[0])
	{
		return Result::FIVE;//星５
	}
	//星４の判定
	else if (resultStep <= StarNum[1])
	{
		return Result::FOUR;//星４
	}
	//星３の判定
	else if (resultStep <= StarNum[2])
	{
		return Result::THREE;//星３
	}
	//星２の判定
	else if (resultStep <= StarNum[3])
	{
		return Result::TWO;//星２
	}
	//星１の判定
	else
	{
		return Result::ONE;//星１
	}

	return 0;
}

