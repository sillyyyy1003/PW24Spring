#include "UiManager.h"

#include "DebugLog.h"
#include "KInput.h"
#include "Game.h"
#include "xa2.h"

UiManager::UiManager()
{
	//title
	title=std::make_unique<CanvasUI>();

	//tutorial
	for (int i = 0; i < 8; i++) 
	{
		uiTutorial[i] = std::make_unique<CanvasUI>();
		tutorialPageIn[i] = std::make_unique<CanvasUI>();
	}

	//stageSelect
	uiSelectBg = std::make_unique<CanvasUI>();;//背景
	uiSelectCursor = std::make_unique<CanvasUI>();;//ステージセレクトのカーソル
	for(int i=0;i<3;i++)
	{
		uiSelectStage[i] = std::make_unique<CanvasUI>();//ステージ
		uiSelectChapter[i] = std::make_unique<CanvasUI>();//チャプター
		uiClearMark[i] = std::make_unique<CanvasUI>();//クリアの印
	}

	stageMask = std::make_unique<CanvasUI>();//Stage側を暗くするマスク
	chapterMask = std::make_unique<CanvasUI>();//chapter側を暗くするマスク

	//Pause
	uiPauseBg = std::make_unique<CanvasUI>();		//PAUSEの背景
	for(int i=0;i<4;i++)
	{
		uiPauseButton[i] = std::make_unique<CanvasUI>();
	}
	pauseMask = std::make_unique<CanvasUI>();		//pauseの時画面を全体的に暗くなるmask
	uiSoundCursor = std::make_unique<CanvasUI>();	//サウンド用カーソル
	uiSoundBg = std::make_unique<CanvasUI>();		//SOUNDの背景

	for(int i=0;i<5;i++)
	{
		uiSoundOp_BGM[i] = std::make_unique<CanvasUI>();	//BGM設定
		uiSoundOp_SE[i] = std::make_unique<CanvasUI>();	//SE設定
	}

	for (int i = 0; i < 3; i++)
	{
		stageTutorial[i] = std::make_unique<CanvasUI>();
		stageHint[i] = std::make_unique<CanvasUI>();
		stageShapeHint[i] = std::make_unique<CanvasUI>();
	}

	hintBg = std::make_unique<CanvasUI>();
	controlPanel = std::make_unique<CanvasUI>();
	//ui
	uiStepNum=std::make_unique<ResultProcess>();
	uiArrow = std::make_unique<CanvasUI>();

}

UiManager::~UiManager()
{
}

void UiManager::Init()
{
	//title
	title->InitCanvas({ 1280, 720},{10,2},Game::Get()->GetModelManager()->uiTitle.Get());

	//tutorial
	uiTutorial[INTRODUCE] ->InitCanvas({ 1280, 720 }, { 8,2 }, Game::Get()->GetModelManager()->uiTutorial[INTRODUCE].Get());
	uiTutorial[MOVE1]->InitCanvas({ 1280, 720 }, { 6,2 }, Game::Get()->GetModelManager()->uiTutorial[MOVE1].Get());
	uiTutorial[MOVE2]->InitCanvas({ 1280, 720 }, { 9,1 }, Game::Get()->GetModelManager()->uiTutorial[MOVE2].Get());
	uiTutorial[MOVE3]->InitCanvas({ 1280, 720 }, { 6,2 }, Game::Get()->GetModelManager()->uiTutorial[MOVE3].Get());
	uiTutorial[MOVE4]->InitCanvas({ 1280, 720 }, { 6,2 }, Game::Get()->GetModelManager()->uiTutorial[MOVE4].Get());
	uiTutorial[SIZECHANGE]->InitCanvas({ 1280, 720 }, { 11,2 }, Game::Get()->GetModelManager()->uiTutorial[SIZECHANGE].Get());
	uiTutorial[COMBINITION]->InitCanvas({ 1280, 720 }, { 8,1 }, Game::Get()->GetModelManager()->uiTutorial[COMBINITION].Get());
	uiTutorial[END]->InitCanvas({ 1280, 720 }, { 7,2 }, Game::Get()->GetModelManager()->uiTutorial[END].Get());
	

	tutorialPageIn[INTRODUCE]->InitCanvas({ 1280, 720 }, { 8,1 }, Game::Get()->GetModelManager()->uiTutorialAnimation[INTRODUCE].Get());
	tutorialPageIn[MOVE1]->InitCanvas({ 1280, 720 }, {8,1 }, Game::Get()->GetModelManager()->uiTutorialAnimation[MOVE1].Get());
	tutorialPageIn[MOVE2]->InitCanvas({ 1280, 720 }, { 7,1 }, Game::Get()->GetModelManager()->uiTutorialAnimation[MOVE2].Get());
	tutorialPageIn[MOVE3]->InitCanvas({ 1280, 720 }, { 7,1 }, Game::Get()->GetModelManager()->uiTutorialAnimation[MOVE3].Get());
	tutorialPageIn[MOVE4]->InitCanvas({ 1280, 720 }, { 7,1 }, Game::Get()->GetModelManager()->uiTutorialAnimation[MOVE4].Get());
	tutorialPageIn[SIZECHANGE]->InitCanvas({ 1280, 720 }, { 8,1 }, Game::Get()->GetModelManager()->uiTutorialAnimation[SIZECHANGE].Get());
	tutorialPageIn[COMBINITION]->InitCanvas({ 1280, 720 }, { 8,1 }, Game::Get()->GetModelManager()->uiTutorialAnimation[COMBINITION].Get());
	tutorialPageIn[END]->InitCanvas({ 1280, 720 }, { 8,1 }, Game::Get()->GetModelManager()->uiTutorialAnimation[END].Get());
	

	//stageSelect
	uiSelectBg -> InitCanvas({ 1280, 720 }, { 1,1 }, Game::Get()->GetModelManager()->uiSelectBg.Get());//背景
	uiSelectCursor->InitCanvas({ 76, 84 }, { 1,1 }, Game::Get()->GetModelManager()->uiSelectCursor.Get());//ステージセレクトのカーソル

	uiSelectStage[STAGE1]->InitCanvas({ 421, 133 }, {1,2 }, Game::Get()->GetModelManager()->uiSelectStage[STAGE1].Get());//ステージ
	uiSelectStage[STAGE2]->InitCanvas({ 421, 142 }, { 1,2 }, Game::Get()->GetModelManager()->uiSelectStage[STAGE2].Get());//ステージ
	uiSelectStage[STAGE3]->InitCanvas({ 421, 143, }, { 1,2 }, Game::Get()->GetModelManager()->uiSelectStage[STAGE3].Get());//ステージ



	for (int i = 0; i < 3; i++)
	{
		uiSelectChapter[i]->InitCanvas({ 300, 57 }, { 1,1 }, Game::Get()->GetModelManager()->uiSelectChapter[i].Get());//チャプター
		uiClearMark[i]->InitCanvas({ 87, 87 }, { 1,1 }, Game::Get()->GetModelManager()->uiClear);//クリアの印
	}

	stageMask->InitCanvas({ 1280, 720 }, { 1, 1 }, Game::Get()->GetModelManager()->selectMask.Get());//Stage側を暗くするマスク
	chapterMask->InitCanvas({ 1280, 720 }, { 1, 1 }, Game::Get()->GetModelManager()->chapterMask.Get());//chapter側を暗くするマスク

	//Pause
	uiPauseBg->InitCanvas({ 647, 702 }, { 1,1 }, Game::Get()->GetModelManager()->uiPauseBg.Get());		//PAUSEの背景

	for (int i = 0; i < 4; i++)
	{
		uiPauseButton[i]->InitCanvas({ 280, 92 }, { 1,2 }, Game::Get()->GetModelManager()->uiPauseButton[i].Get());
	}

	pauseMask->InitCanvas({ 1280, 720 }, { 1,1 }, Game::Get()->GetModelManager()->PauseBg.Get());		//pauseの時画面を全体的に暗くなるmask


	uiSoundCursor->InitCanvas({ 56, 51 }, { 1,1 }, Game::Get()->GetModelManager()->uiSoundCursor.Get());	//サウンド用カーソル
	uiSoundBg->InitCanvas({ 687, 550 }, { 1,1 }, Game::Get()->GetModelManager()->uiSoundBg.Get());		//SOUNDの背景

	for (int i = 0; i < 5; i++)
	{
		uiSoundOp_BGM[i]->InitCanvas({ 313, 324 }, { 1,1 }, Game::Get()->GetModelManager()->uiSoundOp);	//BGM設定
		uiSoundOp_SE[i]->InitCanvas({ 313, 324 }, { 1,1 }, Game::Get()->GetModelManager()->uiSoundOp);	//SE設定
	}

	//stageTutorial for first stage
	for (int i = 0; i < 3; i++)
	{
		stageTutorial[i]->InitCanvas({ 350, 720 }, { 17, 2 }, Game::Get()->GetModelManager()->stageTutorial[i].Get());
		stageHint[i]->InitCanvas({ 883, 657 }, { 1,1 }, Game::Get()->GetModelManager()->stageHint[i].Get());
		stageShapeHint[i]->InitCanvas({ 883, 657 }, { 1,1 }, Game::Get()->GetModelManager()->stageShapeHint[i].Get());
	}

	
	hintBg->InitCanvas({ 1280, 720 }, { 1, 1 }, Game::Get()->GetModelManager()->hintBg.Get());
	controlPanel->InitCanvas({ 1280, 720 }, { 1, 1 }, Game::Get()->GetModelManager()->controlPanel.Get());
	uiStepNum->Init(0, 0, 0.8, 0);

	uiArrow->InitCanvas({ 17,17 }, { 8,1 }, Game::Get()->GetModelManager()->uiArrow.Get());

	InitUi();
}

void UiManager::Update()
{
	switch (Game::Get()->GetSceneManager()->GetScene()) {
	case scene::TITLE:
		TitleUpdate();
		break;
	case scene::TUTORIAL:
		TutorialUpdate();
		break;
	case scene::STAGESELECT:
		SelectUpdate();
		break;
	case scene::STAGE:
		StageUpdate();
		break;
	case scene::RESULT:
		break;
	default:;
	}
}

void UiManager::Draw()
{
	switch (Game::Get()->GetSceneManager()->GetScene()) {
	case scene::TITLE:
		TitleDraw();
		break;
	case scene::TUTORIAL:
		TutorialDraw();
		break;
	case scene::STAGESELECT:
		SelectDraw();
		break;
	case scene::STAGE:
		StageDraw();
		break;
	case scene::RESULT:
		break;
	default:;
	}
}

void UiManager::InitUi()
{
	switch (Game::Get()->GetSceneManager()->GetScene()) {
	case scene::TITLE:
		XA_Play(BGM_TITLE);
		InitTitle();
		break;
	case scene::TUTORIAL:
		InitTutorial();
		break;
	case scene::STAGESELECT:
		XA_Play(BGM_SelectStage);// セレクト画面に戻った時にBGM再生
		InitStageSelect();
		break;
	case scene::STAGE:
		InitStage();
		break;
	case scene::RESULT:
		break;
	default: ;
	}
}

void UiManager::InitTitle()
{
	//アニメション設定
	title->mSprite->GetAnimation()->SetLoop(true);//最初はループように設定
	title->mSprite->GetAnimation()->SetAnimeSpeed(0.3f);

	//位置設定
	title->mSprite->mPos = { 0.0f,0.0f,Game::Get()->GetLayerManager()->SetLayers(Layer::BACKGROUND) };
}

void UiManager::InitTutorial()
{
	for (int i = 0; i < mTutorialNum; i++) {
		uiTutorial[i]->mSprite->GetAnimation()->SetLoop(true);
		uiTutorial[i]->mSprite->GetAnimation()->SetPlaying(false);
		uiTutorial[i]->mSprite->GetAnimation()->SetAnimeSpeed(0.08f);
		uiTutorial[i]->mSprite->mPos = { 0.0f, 0.0f, Game::Get()->GetLayerManager()->SetLayers(Layer::BACKGROUND) };
		uiTutorial[i]->mSprite->mScale = { 0.97f, 0.97f, 0.9f };
		uiTutorial[i]->isActive = true;

	
		tutorialPageIn[i]->mSprite->GetAnimation()->SetLoop(false);
		tutorialPageIn[i]->mSprite->GetAnimation()->SetAnimeSpeed(0.15f);
		tutorialPageIn[i]->mSprite->mPos = { 0.0f, 0.0f, Game::Get()->GetLayerManager()->SetLayers(Layer::MASK_BACK) };
		tutorialPageIn[i]->mSprite->mScale = { 0.97f, 0.97f, 0.9f };
		tutorialPageIn[i]->isActive = true;

	}
	uiTutorial[INTRODUCE]->mSprite->GetAnimation()->SetLoop(false);
	uiTutorial[END]->mSprite->GetAnimation()->SetLoop(false);
	tutorial = INTRODUCE;
}

void UiManager::InitStageSelect()
{
	// 位置 & 大小
	uiSelectBg->mSprite->mPos = { 0.0f,0.04f,Game::Get()->GetLayerManager()->SetLayers(Layer::BACKGROUND) };//背景を一番後ろ
	uiSelectBg->mSprite->mScale = { 0.98f,0.98f,1.0f };//大きさ
	uiSelectCursor->mSprite->mPos = { 5.2f,3.6f,0.8f };//Chapterの横に出るように

	uiSelectStage[STAGE1]->mSprite->mPos = { -3.2f,1.3f,Game::Get()->GetLayerManager()->SetLayers(Layer::UI_BOX) };
	uiSelectStage[STAGE2]->mSprite->mPos = { -2.7f,-0.6f,Game::Get()->GetLayerManager()->SetLayers(Layer::UI_BOX) };
	uiSelectStage[STAGE3]->mSprite->mPos = { -3.1f,-2.5f,Game::Get()->GetLayerManager()->SetLayers(Layer::UI_BOX) };

	uiSelectChapter[CHAPTER1]->mSprite->mPos = { 3.1f,3.2f,Game::Get()->GetLayerManager()->SetLayers(Layer::UI_BOX) };
	uiSelectChapter[CHAPTER2]->mSprite->mPos = { 3.1f,0.8f,Game::Get()->GetLayerManager()->SetLayers(Layer::UI_BOX) };
	uiSelectChapter[CHAPTER3]->mSprite->mPos = { 3.1f,-1.5f,Game::Get()->GetLayerManager()->SetLayers(Layer::UI_BOX) };

	stageMask->mSprite->mPos = { 0.0,0.0,Game::Get()->GetLayerManager()->SetLayers(Layer::MASK_FRONT) };
	chapterMask->mSprite->mPos = { 0.0,0.0,Game::Get()->GetLayerManager()->SetLayers(Layer::MASK_FRONT) };

	//クリアの印の位置設定
	float posy = 2.3f;
	uiClearMark[0]->mSprite->mPos = { 4.5f,posy,Game::Get()->GetLayerManager()->SetLayers(Layer::UI_WORD) };
	posy = 2.3f - 2.5f;
	uiClearMark[1]->mSprite->mPos = { 5.0f,posy,Game::Get()->GetLayerManager()->SetLayers(Layer::UI_WORD) };
	posy = 2.3f - 2.5f * 2.0f;
	uiClearMark[2]-> mSprite->mPos = { 4.8f,posy,Game::Get()->GetLayerManager()->SetLayers(Layer::UI_WORD) };

	//アニメション
	for (int i = 0; i < mStageNum; i++) {
		uiSelectStage[i]->mSprite->GetAnimation()->SetFrameY(0);
		uiSelectStage[i]->mSprite->GetAnimation()->SetAnimeSpeed(0.05f);
		uiSelectStage[i]->mSprite->GetAnimation()->SetPlaying(false);
	}

	//最初はカーソルを隠す
	uiSelectCursor->isActive=false;

	//ステージを設定
	selectStage = STAGE1;
	selectChapter = CHAPTER1;
	isSelectStage = true;
	stageMask->isActive = false;
	chapterMask->isActive = true;

	mStageNum = 3;
	mChapterNum = 3;
}

void UiManager::InitStage()
{
	//stageTutorial

	for (int i = 0; i < 3; i++)
	{
		stageTutorial[i]->mSprite->GetAnimation()->SetPlaying(false);
		stageTutorial[i]->mSprite->GetAnimation()->SetLoop(false);
		stageTutorial[i]->mSprite->GetAnimation()->SetAnimeSpeed(0.3f);
		stageTutorial[i]->mSprite->mScale = { 0.6f,0.6f,1.0f };
		stageTutorial[i]->mSprite->mPos = { 510.0f * SCREEN_PARA, -144.0f * SCREEN_PARA,0.2f };

		stageTutorial[i]->SetActive(false);

	}

	//最初の一回しか表示しない
	if(tutorialNum!=FINISHED)
	{
		tutorialNum = MOVETUTORIAL;
	}


	hintBg->mSprite->mPos.z = 0.3f;

	//ControlPanel
	controlPanel->mSprite->mPos = { 0,0,Game::Get()->GetLayerManager()->SetLayers(Layer::UI_PANEL)};//一番手前にする
	controlPanel->mSprite->mScale = { 0.96f,0.96f,1.0f };

	//pause panel
	pauseMask->mSprite->mPos.z = 0.7f;
	uiPauseBg->mSprite->mPos = { -300 * SCREEN_PARA, 0.0f, Game::Get()->GetLayerManager()->SetLayers(Layer::UI_PANEL) };

	float posY = 1.7f;

	for (int i = 0; i < pauseNum; i++) {
		uiPauseButton[i]->mSprite->mPos = { -6.0,posY - i * 1.35f,Game::Get()->GetLayerManager()->SetLayers(Layer::UI_BOX) };
		uiPauseButton[i]->mSprite->GetAnimation()->SetPlaying(false);

		if (pauseSelect == i) {
			uiPauseButton[i]->mSprite->GetAnimation()->SetFrameY(0);
			uiPauseButton[i]->mSprite->mPos.x = -5.5f;
		}
		else {
			uiPauseButton[i]->mSprite->GetAnimation()->SetFrameY(1);
			uiPauseButton[i]->mSprite->mPos.x = -6.0f;
		}
	}


	uiSoundBg->mSprite->mPos = { 1.0f, 0.2f, 0.4f };
	uiSoundCursor->mSprite->mPos = { -2.0f, 0.65f, 0.3f };
	DirectX::XMFLOAT3 pos = { 1.0f, 0.7f, 0.2f };

	for (int i = 0; i < 5; i++)
	{
		//位置
		uiSoundOp_BGM[i]->mSprite->mPos = { pos.x + i * 0.8f,pos.y, pos.z };
		uiSoundOp_SE[i]->mSprite->mPos = { pos.x + i * 0.8f, -pos.y, pos.z };
		//大きさ
		uiSoundOp_BGM[i]->mSprite->mScale= { 0.2f,0.2f,0.2f };
		uiSoundOp_SE[i]->mSprite->mScale = { 0.2f,0.2f,0.2f };

	}
	//PAUSESELECT
	pauseSelect = RESUME;


	isPause = false;
	isSound = false;
	stageTutorial[MOVETUTORIAL]->mSprite->GetAnimation()->SetPlaying(true);

	uiSoundBg->SetActive(false);
	uiSoundCursor->SetActive(false);

	for(int i=0;i<5;i++)
	{
		uiSoundOp_BGM[i]->SetActive(false);
		uiSoundOp_SE[i]->SetActive(false);
	}

	for (int i = 0; i < 3; i++)
	{
		stageHint[i]->mSprite->mPos.z = 0.2f;
		stageShapeHint[i]->mSprite->mPos.z = 0.2f;
	}

	//hint;
	Game::Get()->GetSceneManager()->mStageHolder[Game::Get()->GetSceneManager()->GetStage()]->SetHint(true);
	Game::Get()->GetSceneManager()->mStageHolder[Game::Get()->GetSceneManager()->GetStage()]->SetShapeHint(false);

	controlPanel->SetActive(true);
	uiArrow->mSprite->mPos = { 6.0f,325.0f * SCREEN_PARA,0.5f };
	uiArrow->mSprite->GetAnimation()->SetLoop(true);
	uiArrow->mSprite->GetAnimation()->SetAnimeSpeed(0.15f);
}

void UiManager::TitleUpdate()
{
	//スペースキー押したら、チュートリアルに進む
	if (KInput::Get()->GetKeyTrigger(DIK_SPACE)) {
		XA_Play(SE_TITLE);
		Game::Get()->GetSceneManager()->SetScene(scene::TUTORIAL);
		InitTutorial();
	}

	if(KInput::Get()->GetKeyTrigger(DIK_RETURN))
	{
		Game::Get()->GetSceneManager()->ChangeScene(scene::STAGESELECT,scene::FADE);
	}
	title->Update();
}

void UiManager::TutorialUpdate()
{
	//入力
	if (KInput::Get()->GetKeyTrigger(DIK_SPACE))
	{
		if (tutorial != END && !tutorialPageIn[tutorial]->mSprite->GetAnimation()->GetPlaying()) {//最後まで行ってない場合
			XA_Play(SE_TITLE);
			int num = tutorial;
			num++;
			//データタイプを転換
			tutorial = static_cast<TUTORIAL_SKILL>(num);
		}else if(tutorial==END) 
		{
			//シーンの切り替え
			if(!uiTutorial[END]->mSprite->GetAnimation()->GetPlaying())
			{
				XA_Play(SE_SelectDecide);
				Game::Get()->GetSceneManager()->ChangeScene(scene::STAGESELECT, scene::FADE);
			}
		}
	}

	//pageIn終わったら、ループアニメーションに入る
	if (!tutorialPageIn[tutorial]->mSprite->GetAnimation()->GetPlaying()&& tutorialPageIn[tutorial]->isActive) {
		tutorialPageIn[tutorial]->isActive = false;
		uiTutorial[tutorial]->mSprite->GetAnimation()->SetPlaying(true);
	}

	uiTutorial[tutorial]->Update();
	tutorialPageIn[tutorial]->Update();
}

void UiManager::SelectUpdate()
{
	DoSelectKey();
	SetSelectStatus();

	uiSelectBg->Update();
	uiSelectCursor->Update();

	for (int i = 0; i < mStageNum; i++) {
		uiSelectStage[i]->Update();
	}

	for (int i = 0; i <mChapterNum; i++) {
		uiSelectChapter[i]->Update();
		uiClearMark[i]->Update();
	}

}

void UiManager::ObjectMove(CanvasUI* pObject, float moveSpeed, float bounceHeight)
{
	float rate = 0.1f;
	pObject->mSprite->mPos.y = pObject->mSprite->mPos.y + bounceHeight * rate * sinf(mSelectCounter * moveSpeed);
	mSelectCounter++;
}

void UiManager::DoSelectKey()
{
	if(Game::Get()->GetFade()->mState!=Fade::None)
	{
		return;
	}

	if (KInput::Get()->GetKeyTrigger(DIK_SPACE)) {
		

		if (isSelectStage) {//ステージを選択
			XA_Play(SE_SelectDecide);//決定SE再生
			isSelectStage = false;//SelectChapterに入る
			selectChapter = CHAPTER1;//チャプターを設定
			uiSelectCursor->isActive = true;
		}
		else {//チャプターを選択
			//今のステージを計算
			int num = selectStage * 3 + selectChapter;

			if(num>=3)
			{
				//シーン遷移に入る
				Game::Get()->GetSceneManager()->ChangeScene(scene::TITLE, scene::FADE);
				return;
			}

			//シーンマネージャーに今のステージを伝える
			Game::Get()->GetSceneManager()->SetNextStage(static_cast<scene::StageInfo>(num));
			//シーン遷移に入る
			Game::Get()->GetSceneManager()->ChangeScene(scene::STAGE,scene::FADE);

			XA_Play(SE_Press);//ステージに遷移するとお題のSEを再生
		}
	}


	if (KInput::Get()->GetKeyTrigger(DIK_UPARROW)) {
		XA_Play(SE_Select);//選択SE再生
		//Do Select KeyEvents
		if (isSelectStage) {
			//STAGE1の場合制限する
			if (selectStage == STAGE1) {
				selectStage = STAGE3;
			}
			else {
				int num = selectStage;
				num--;
				selectStage = static_cast<SELECTSTAGE>(num);
			}
		}
		else {//ステージセレクト
			//CHAPTER1の場合制限する
			if (selectChapter == CHAPTER1) {
				selectChapter = CHAPTER3;
			}
			else {
				int num = selectChapter;
				num--;
				selectChapter = static_cast<SELECTCHAPTER>(num);
			}
		}
	}

	if (KInput::Get()->GetKeyTrigger(DIK_DOWNARROW)) {
		XA_Play(SE_Select);//選択SE再生
		//Do Select KeyEvents
		if (isSelectStage) {
			//STAGE1の場合制限する
			if (selectStage == STAGE3) {
				selectStage = STAGE1;
			}
			else {
				int num = selectStage;
				num++;
				selectStage = static_cast<SELECTSTAGE>(num);
			}
		}
		else {//ステージセレクト
			//CHAPTER1の場合制限する
			if (selectChapter == CHAPTER3) {
				selectChapter = CHAPTER1;
			}
			else {
				int num = selectChapter;
				num++;
				selectChapter = static_cast<SELECTCHAPTER>(num);
			}
		}
	}

	if (KInput::Get()->GetKeyTrigger(DIK_ESCAPE)) {
		XA_Play(SE_SelectDecide);//セレクトSE再生
		//ステージ選択の場合→タイトルに戻る
		if (isSelectStage) {
			Game::Get()->GetSceneManager()->ChangeScene(scene::TITLE,scene::FADE);
		}
		else {
			isSelectStage = true;
			//カーソルを隠す
			uiSelectCursor->isActive=false;
			//元の位置に戻る
			selectChapter = CHAPTER1;
		}
	}

	

}

void UiManager::SetSelectStatus()
{
	if (isSelectStage) {
		uiSelectCursor->isActive = false;
		//選択されたステージアニメション起動
		for (int i = 0; i < mStageNum; i++) {
			if (selectStage == i) {
				//ACTIVE
				uiSelectStage[i]->mSprite->GetAnimation()->SetFrameY(0);
				ObjectMove(uiSelectStage[i].get(), 0.2f, 0.1f);

			}
			else {
				//INACTIVE
				uiSelectStage[i]->mSprite->mPos.y = 1.3f - 1.9f * i;
				uiSelectStage[i]->mSprite->GetAnimation()->SetFrameY(1);
			}
		}
	}
	else {
		int num = selectChapter;
		uiSelectCursor->isActive = true;
		uiSelectCursor->mSprite->mPos = {1.3f, 3.6f - num * 2.4f, 0.7f};
		ObjectMove(uiSelectCursor.get(), 0.1f, 0.4f);//羽ペンを動かす
	}

	//クリアの印をつける
	int num = selectStage * 3;
	for (int i = 0; i < mChapterNum; i++) {
		//完成下かどうか
		if (Game::Get()->GetSceneManager()->mStageHolder[num + i]->GetCompleted()) {
			//クリアしたら描画する
			uiClearMark[i]->isActive=true;
		}
		else {
			//クリアしなかったら描画しない
			uiClearMark[i]->isActive = false;
		}
	}

	if (!isSelectStage) {
		stageMask->isActive =true;
		chapterMask->isActive = false;
	}
	else {
		stageMask->isActive = false;
		chapterMask->isActive = true;
	}

}

void UiManager::StageUpdate()
{

	if (!isPause)
	{
		if(!isHint)
		{
			StageTutorial();
		}
		
		uiArrow->Update();
		HintUpdate();
	}
	else
	{
		uiArrow->SetActive(false);
		if (isSound) {

			DoSoundEvent();

			//Reset
			for(int i=0;i<5;i++)
			{
				uiSoundOp_BGM[i]->SetActive(false);
				uiSoundOp_SE[i]->SetActive(false);
			}

			//今の状態をアップデート
			for (int i = 0; i < Game::Get()->GetBGMVolume(); i++) {
				uiSoundOp_BGM[i]->SetActive(true);
			}
			for (int i = 0; i < Game::Get()->GetSEVolume(); i++) {
				uiSoundOp_SE[i]->SetActive(true);
			}

			//カーソルの位置を更新する
			if (isSelectBgm) {
				uiSoundCursor->mSprite->mPos = { -2.0f, 0.7f, 0.2f };
			}
			else {
				uiSoundCursor->mSprite->mPos = { -2.0f, -0.7f, 0.2f };
			}

		}
		else if(isPause) {

			DoPauseEvent();

			//アニメションの変更
			for (int i = 0; i < pauseNum; i++) {
				if (pauseSelect == i) {
					uiPauseButton[i]->mSprite->GetAnimation()->SetFrameY(0);
					ObjectMove(uiPauseButton[i].get(), 0.1f, 0.03f);
					uiPauseButton[i]->mSprite->mPos.x = -5.5f;
				}
				else {
					uiPauseButton[i]->mSprite->GetAnimation()->SetFrameY(1);
					uiPauseButton[i]->mSprite->mPos.x = -6.0f;
				}
			}

			//マスクを有効にする
			hintBg->SetActive(true);

			//Apply Animation
			for (int i = 0; i < pauseNum; i++) {
				uiPauseButton[i]->Update();
			}
		}
	}


}

void UiManager::StageTutorial()
{
	if (Game::Get()->GetSceneManager()->GetStage() != scene::STAGE1_1) { return; }
	if (tutorialNum == IDLETUTORIAL) { return; }

	if (Game::Get()->GetFade()->mState != Fade::Fade_In) {

		switch (tutorialNum) {
		case MOVETUTORIAL:

			if (KInput::Get()->GetKeyTrigger(DIK_UPARROW) ||
				KInput::Get()->GetKeyTrigger(DIK_DOWNARROW) ||
				KInput::Get()->GetKeyTrigger(DIK_LEFTARROW) ||
				KInput::Get()->GetKeyTrigger(DIK_RIGHTARROW)
				) 
			{
				isNextTutorial = true;
			}
			if (isNextTutorial) 
			{
				//buffer time
				tutorialCounter++;

				if (tutorialCounter >= 60) {
					tutorialNum = SPACETUTORIAL;
					stageTutorial[tutorialNum]->mSprite->GetAnimation()->SetPlaying (true);
					tutorialCounter = 0;
					isNextTutorial = false;
				}
			}
			break;
		case SPACETUTORIAL:
			if (KInput::Get()->GetKeyTrigger(DIK_SPACE)) {
				isNextTutorial = true;

			}

			if (isNextTutorial) {
				//buffer time
				tutorialCounter++;

				if (tutorialCounter >= 60) {
					tutorialNum = HINTTUTORIAL;
					stageTutorial[tutorialNum]->mSprite->GetAnimation()->SetPlaying(true);
					isNextTutorial = false;
					tutorialCounter = 0;
				}
			}
			break;
		case HINTTUTORIAL:

			if (KInput::Get()->GetKeyTrigger(DIK_H)) {
				tutorialNum = FINISHED;
			}
			break;
		}

		for (int i = 0; i < 3; i++) {

			if (i == tutorialNum) 
			{
				stageTutorial[i]->isActive = true;
				if (!stageTutorial[i]->mSprite->GetAnimation()->GetPlaying()) 
				{
					//最後の１フレームに固定
					stageTutorial[i]->mSprite->GetAnimation()->SetFrameX(16);
					stageTutorial[i]->mSprite->GetAnimation()->SetFrameY(1);

					hintBg->isActive = false;
					//Game::Get()->isTutorialFinish[i] = 1;
				
				}else
				{
					hintBg->isActive = true;
				}
			}else
			{
				stageTutorial[i]->isActive = false;
				
			}

			stageTutorial[i]->Update();
		}

	}

}


void UiManager::DoStageKey()
{
	
}

void UiManager::HintUpdate()
{
	
	//形のヒント
	if (KInput::Get()->GetKeyTrigger(DIK_H))
	{
		if (!Game::Get()->GetSceneManager()->mStageHolder[Game::Get()->GetSceneManager()->GetStage()]->GetShapeHint())
		{
			Game::Get()->GetSceneManager()->mStageHolder[Game::Get()->GetSceneManager()->GetStage()]->SetShapeHint(true);
			stageShapeHint[Game::Get()->GetSceneManager()->GetStage()]->isActive = true;
			hintBg->isActive = true;
			isHint = true;
			XA_Play(SE_TITLE);
		}

	}

	if (Game::Get()->GetSceneManager()->mStageHolder[Game::Get()->GetSceneManager()->GetStage()]->GetShapeHint())
	{
		isHint = true;
		hintBg->isActive = true;
		stageShapeHint[Game::Get()->GetSceneManager()->GetStage()]->isActive = true;
		if (KInput::Get()->GetKeyTrigger(DIK_SPACE))
		{
			Game::Get()->GetSceneManager()->mStageHolder[Game::Get()->GetSceneManager()->GetStage()]->SetShapeHint(false);
			stageShapeHint[Game::Get()->GetSceneManager()->GetStage()]->isActive = false;
			hintBg->isActive = false;
			isHint = false;
		}
	}

	if (Game::Get()->GetSceneManager()->mStageHolder[Game::Get()->GetSceneManager()->GetStage()]->GetHint())
	{
		isHint = true;
		hintBg->isActive = true;
		stageHint[Game::Get()->GetSceneManager()->GetStage()]->isActive = true;
		
		if (KInput::Get()->GetKeyTrigger(DIK_SPACE))
		{
			Game::Get()->GetSceneManager()->mStageHolder[Game::Get()->GetSceneManager()->GetStage()]->SetHint(false);
			stageHint[Game::Get()->GetSceneManager()->GetStage()]->isActive = false;
			hintBg->isActive = false;
			isHint = false;
			XA_Play(SE_TITLE);
		}
	
	}


}

void UiManager::PauseSwitch()
{
	if (isPause)
	{
		if(isSound)
		{
			isSound = false;
			//元の状態が残さないようにリセット
			for (int i = 0; i < 5; i++) {

				uiSoundOp_BGM[i]->SetActive(false);
				uiSoundOp_SE[i]->SetActive(false);
			}
			uiSoundBg->SetActive(false);
			uiSoundCursor->SetActive(false);
			isSelectBgm = true;//RESET
			return;
		}
		
		isPause = false;
		isSound = false;
		pauseSelect = RESUME;
		//画面エフェクトの切り替え
		stageMask->SetActive(true);
		controlPanel->SetActive(true);
		uiArrow->SetActive(true);
		pauseMask->SetActive(false);
	}
	else
	{
		isPause = true;
		//画面エフェクトの切り替え
		stageMask->SetActive(false);
		controlPanel->SetActive(false);
		uiArrow->SetActive(false);
		pauseMask->SetActive(true);
	}
}

void UiManager::DoPauseEvent()
{

	if (KInput::Get()->GetKeyTrigger(DIK_SPACE)) {
		XA_Play(SE_SelectDecide);
		switch (pauseSelect)
		{
		case UiManager::RESUME:
			PauseSwitch();
			break;
		case UiManager::RESTART:
			Game::Get()->InitStage();
			PauseSwitch();
			InitUi();//PAUSE画面の設定を最初に戻る
			break;
		case UiManager::BACKSELECT:
			PauseSwitch();
			//InitUi();//PAUSE画面の設定を最初に戻る
			Game::Get()->GetSceneManager()->ChangeScene(scene::STAGESELECT, scene::FADE);
			break;
		case UiManager::SOUND:
			isSound = true;
			uiSoundBg->SetActive(true);
			uiSoundCursor->SetActive(true);
			//今の状態をアップデート
			for (int i = 0; i < Game::Get()->GetBGMVolume(); i++) {
				uiSoundOp_BGM[i]->SetActive(true);
			}
			for (int i = 0; i < Game::Get()->GetSEVolume(); i++) {
				uiSoundOp_SE[i]->SetActive(true);
			}
			//カーソルの位置を更新する
			if (isSelectBgm) {
				uiSoundCursor->mSprite->mPos = { -2.0f, 0.7f, 0.3f };
			}
			else {
				uiSoundCursor->mSprite->mPos = { -2.0f, -0.7f, 0.3f };
			}
			break;
		case UiManager::PAUSE_IDLE:
			break;
		default:
			break;
		}
	}
	if (KInput::Get()->GetKeyTrigger(DIK_UPARROW)) {
		XA_Play(SE_Select);
		if (pauseSelect == RESUME) {
			pauseSelect = SOUND;
		}
		else {
			int num = pauseSelect;
			num--;
			pauseSelect = static_cast<PAUSESELECT>(num);
		}
	}
	if (KInput::Get()->GetKeyTrigger(DIK_DOWNARROW)) {
		XA_Play(SE_Select);
		//制限
		if (pauseSelect == SOUND) {
			pauseSelect = RESUME;
		}
		else {
			int num = pauseSelect;
			num++;
			pauseSelect = static_cast<PAUSESELECT>(num);
		}
	}
}

void UiManager::DoSoundEvent()
{
	if (KInput::Get()->GetKeyTrigger(DIK_LEFTARROW)) {
		if (isSelectBgm) {

			XA_Play(SE_Select);//セレクトSE再生
			if (Game::Get()->GetBGMVolume() <= 0) {
				Game::Get()->SetBGMVolume(0);
			}
			else {
				Game::Get()->SetBGMVolume(Game::Get()->GetBGMVolume() - 1.0f);
			}
		}
		else {
			XA_Play(SE_Select);//セレクトSE再生
			if (Game::Get()->GetSEVolume() <= 0) {
				Game::Get()->SetSEVolume(0);
			}
			else {
				Game::Get()->SetSEVolume(Game::Get()->GetSEVolume() - 1.0f);
			}

		}
	}

	if (KInput::Get()->GetKeyTrigger(DIK_RIGHTARROW)) {
		if (isSelectBgm) {
			//制限をかける
			XA_Play(SE_Select);//セレクトSE再生
			if (Game::Get()->GetBGMVolume() >= 5) {
				Game::Get()->SetBGMVolume(5);
			}
			else {
				Game::Get()->SetBGMVolume(Game::Get()->GetBGMVolume() + 1.0f);
			}
		}
		else {
			XA_Play(SE_Select);//セレクトSE再生
			//制限をかける
			if (Game::Get()->GetSEVolume() >= 5) {
				Game::Get()->SetSEVolume(5);
			}
			else {
				Game::Get()->SetSEVolume(Game::Get()->GetSEVolume() + 1.0f);
			}
		}
	}

	Game::Get()->ApplyVolume();

	if (KInput::Get()->GetKeyTrigger(DIK_UPARROW)) {
		XA_Play(SE_Select);
		if (isSelectBgm) {
			isSelectBgm = false;
		}
		else {
			isSelectBgm = true;
		}
	}

	if (KInput::Get()->GetKeyTrigger(DIK_DOWNARROW)) {
		XA_Play(SE_Select);
		if (isSelectBgm) {
			isSelectBgm = false;
		}
		else {
			isSelectBgm = true;
		}
	}

}

void UiManager::TitleDraw()
{
	title->Draw();
}

void UiManager::TutorialDraw()
{
	tutorialPageIn[tutorial]->Draw();
	uiTutorial[tutorial]->Draw();
}


void UiManager::SelectDraw()
{
	uiSelectBg->Draw();
	for (int i = 0; i < 3; i++) {
		uiSelectStage[i]->Draw();
	}

	for (int i = 0; i < 3; i++) {
		uiSelectChapter[i]->Draw();
		uiClearMark[i]->Draw();
	}
	uiSelectCursor->Draw();

	DirectX3D::Get()->SetBlendState(DirectX3D::Get()->GetBlendMultiply());
	stageMask->Draw();
	chapterMask->Draw();
	DirectX3D::Get()->SetBlendState(DirectX3D::Get()->GetBlendAlpha());
}

void UiManager::StageDraw()
{
	if (!isPause && !isHint) {

		controlPanel->Draw();
		uiArrow->Draw();
		DirectX3D::Get()->SetBlendState(DirectX3D::Get()->GetBlendMultiply());
		hintBg->Draw();
		DirectX3D::Get()->SetBlendState(DirectX3D::Get()->GetBlendAlpha());

		if (!hintBg->GetActive())
		{
			uiStepNum->Print(-6.5f, 3.2f, Game::Get()->GetSceneManager()->mStageHolder[Game::Get()->GetSceneManager()->GetStage()]->GetStep(), Debug::CENTER);
		}

		for (int i = 0; i < 3; i++) 
		{
			stageTutorial[i]->Draw();
		}


	}
	else {

		if(isPause)
		{
			DirectX3D::Get()->SetBlendState(DirectX3D::Get()->GetBlendMultiply());
			pauseMask->Draw();
			DirectX3D::Get()->SetBlendState(DirectX3D::Get()->GetBlendAlpha());

			uiPauseBg->Draw();
			for (int i = 0; i < pauseNum; i++) {
				uiPauseButton[i]->Draw();
			}

			uiSoundBg->Draw();
			uiSoundCursor->Draw();

			for (int i = 0; i < 5; i++) {
				uiSoundOp_BGM[i]->Draw();
				uiSoundOp_SE[i]->Draw();
			}


			return;
		}else if(isHint)
		{
			DirectX3D::Get()->SetBlendState(DirectX3D::Get()->GetBlendMultiply());
			hintBg->Draw();
			DirectX3D::Get()->SetBlendState(DirectX3D::Get()->GetBlendAlpha());
			stageHint[Game::Get()->GetSceneManager()->GetStage()]->Draw();
			stageShapeHint[Game::Get()->GetSceneManager()->GetStage()]->Draw();
		}

	}
}
