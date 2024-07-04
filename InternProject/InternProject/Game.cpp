#include <sstream>
#include "GameFrame.h"
#include "Scene.h"
#include "xa2.h"

extern Time gTime;

Game::~Game()
{
	delete mCamera2D;
	delete mCamera3D;

	XA_Release();
}

void Game::InitGame()
{
	//Init Camera
	InitCamera();

	//Init
	InitTool();

	//Init UI
	InitUI();

	//Init GameObject
	InitGameObject();


	//Start Game
	mSceneManager->SetNextScene(scene::TITLE);
	mFade->FadeIn();

}

void Game::Update()
{
	
	if (mSceneManager->GetNextScene() != scene::NONE)
	{
		if (mFade->mState != Fade::Fade_Out)//FadeIn 開始
		{
			mSceneManager->SetScene(mSceneManager->GetNextScene());
			mSceneManager->SetNextScene(scene::NONE);
			mFade->FadeIn();

			//ステージも
			if(mSceneManager->GetScene()==scene::STAGE)
			{
				if (mSceneManager->GetNextStage() != scene::STAGE_NULL)
				{
					mSceneManager->SetStage(mSceneManager->GetNextStage());
					mSceneManager->SetNextStage(scene::STAGE_NULL);
					
				}
				//ステージの初期化
				InitStage();
			}
			//Init Stage/StageSelect/Tutorial
			mUiManager->InitUi();
		}
	}

	switch(mSceneManager->GetScene())
	{
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
		ResultUpdate();
		break;
	}
		
	mFade->Update();



}

void Game::Draw()
{
	DirectX3D::Get()->ClearScreen();
	//ここに描画関数

	switch (mSceneManager->GetScene()) {
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
		ResultDraw();
	default:
		break;
	}

	mFade->Draw();

	//SwapChain
	DirectX3D::Get()->GetD3D_Data()->SwapChain->Present(0, 0);
}

void Game::ApplyVolume()
{
	for (int i = 0; i < 5; i++) {
		SOUND_LABEL sound = static_cast<SOUND_LABEL>(i);
		XA_SetVolume(sound, bgmVolume * 0.5);
	}
	for (int i = 4; i < 17; i++) {
		SOUND_LABEL sound = static_cast<SOUND_LABEL>(i);
		XA_SetVolume(sound, seVolume * 0.5);
	}
}

void Game::InitTool()
{
	mModelManager = std::make_unique<ModelManager>();
	mLayerManager= std::make_unique<LayerManager>();
	mDebugLog = std::make_unique<DebugManager>(1.f);
	mRailManger = std::make_unique<RailManager>();
	mSceneManager = std::make_unique<SceneManager>();
	mResultManager = std::make_unique<ResultManager>();
	mUiManager = std::make_unique<UiManager>();
	mFade = std::make_unique<Fade>();
	mShaker = std::make_unique<CameraShaker>();
	mShaker->Init(0.1f, 3.0f, 20);
	mClearManager = std::make_unique<ClearManager>();
	mResultAnimator = std::make_unique<ResultAnimator>();

	InitSound();
}

void Game::InitCamera()
{
	mCamera2D = new Camera();
	mCamera3D = new Camera();
	//Set Camera
	mCamera2D->SetProjMode(Camera::_2D);
	mCamera2D->SetCamPos({ 0,0,-1 });
	mCamera2D->SetFocus({ 0,0,1 });
	mCamera2D->Update();//Generate MatrixView

	mCamera3D->SetProjMode(Camera::_3D);
	//位置設定
	mCamera3D->SetCamPos({ 0.0f, 7.119f, -21.626f });
	//Focus設定
	mCamera3D->SetFocus({ 0.0f, 0.0f, -(21.626f - 7.0f / ROTATEX) });
	mCamera3D->Update();

	//Set Main Camera
	SetMainCamera(mCamera3D);
}

void Game::InitObject()
{


}

void Game::InitUI()
{

	//stageMask
	stageMask = std::make_unique<CanvasUI>();
	stageMask->InitCanvas({ 1280.f,720.f }, { 1,1 }, mModelManager->stageMask.Get());
	stageMask->mSprite->mPos.z = mLayerManager->SetLayers(Layer::MASK_BACK);

	resultMask = std::make_unique<CanvasUI>();
	resultMask->InitCanvas({ 1280.f,720.f }, { 1,1 }, mModelManager->resultMask.Get());
	resultMask->mSprite->mPos.z = mLayerManager->SetLayers(Layer::MASK_BACK);

	mResultManager->Init();
	mUiManager->Init();
	mUiManager->InitUi();

}

void Game::InitGameObject()
{

	///背景オブジェクト設定
	for (int i = 0; i < 3; i++)
	{
		stageBg[i] = std::make_unique<StaticObject>();

		stageBg[i]->InitObject({ 1280,720 }, { 6,1 }, mModelManager->stageBg[i].Get());
		stageBg[i]->mObj->mRotation.x = 19.8f;//カメラと垂直状態を保持するため
		stageBg[i]->mObj->mScale = {2.21f,2.21f,1.f};//カメラと垂直状態を保持するため
		//y
		float y = 21.626f - 7.0f / ROTATEX;
		y += 1;
		y = y * ROTATEX;

		//y座標の導入
		stageBg[i]->mObj->mPos = { 0.0f,-y,1.f };
		stageBg[i]->mObj->GetAnimation()->SetAnimeSpeed(0.05f);
		stageBg[i]->mObj->GetAnimation()->SetLoop(true);
	}

	//ステージオブジェクト設定
	coconut = std::make_unique<GameObject2D>();
	lamp = std::make_unique<GameObject2D>();
	housePlate = std::make_unique<GameObject2D>();

	lamp1_2 = std::make_unique<GameObject2D>();
	triangleBlock = std::make_unique<GameObject2D>();
	iphone = std::make_unique<GameObject2D>();

	sandwich = std::make_unique<GameObject2D>();
	newspaper = std::make_unique<GameObject2D>();
	bucket = std::make_unique<GameObject2D>();
	picnicBasket = std::make_unique<GameObject2D>();

	//STAGE1
	coconut->InitObject({ 190.f,192.f }, { 1,1 }, mModelManager->coconut[GameObject::object].Get());
	coconut->InitShadow({ 158.f,159.f }, { 1,1 }, mModelManager->coconut[GameObject::shadow].Get(), Collide::SPHERE);

	lamp->InitObject({ 216.0f, 579.0f }, { 1,1 }, mModelManager->lamp[GameObject::object].Get());
	lamp->InitShadow({ 216.0f, 579.0f }, { 1,1 }, mModelManager->lamp[GameObject::shadow].Get(),Collide::SQUARE);

	housePlate->InitObject({ 110.0f, 216.0f }, { 1,1 }, mModelManager->housePlate[GameObject::object].Get());
	housePlate->InitShadow({ 50.0f, 105.0f }, { 1,1 }, 
mModelManager->housePlate[GameObject::shadow].Get(),Collide::SQUARE);

	//STAGE2
	lamp1_2->InitObject({ 264.0f, 267.0f }, { 1,1 }, mModelManager->lamp1_2[GameObject::object].Get());
	lamp1_2->InitShadow({ 217.5f, 217.5f}, { 1,1 }, mModelManager->lamp1_2[GameObject::shadow].Get(), Collide::SQUARE);

	iphone->InitObject({ 186.0f, 141.0f }, { 1,1 }, mModelManager->iphone[GameObject::object].Get());
	iphone->InitShadow({ 205.0f, 155.0f }, { 1,1 }, mModelManager->iphone[GameObject::shadow].Get(), Collide::SQUARE);

	triangleBlock->InitObject({ 378.0f, 348.0f }, { 1,1 }, mModelManager->triangleBlock[GameObject::object].Get());
	triangleBlock->InitShadow({ 190.5f, 172.5f }, { 1,1 },
		mModelManager->triangleBlock[GameObject::shadow].Get(), Collide::SQUARE);

	//STAGE3 
	sandwich->InitObject({ 211.5f, 238.5f }, { 1,1 }, mModelManager->sandwich[GameObject::object].Get());
	sandwich->InitShadow({ 126.0f, 144.0f }, { 1,1 }, mModelManager->sandwich[GameObject::shadow].Get(), Collide::SQUARE);

	newspaper->InitObject({ 301.5f, 229.5f }, { 1,1 }, mModelManager->newspaper[GameObject::object].Get());
	newspaper->InitShadow({ 361.8f, 300.0f }, { 1,1 }, mModelManager->newspaper[GameObject::shadow].Get(), Collide::SQUARE);

	bucket->InitObject({ 255.0f, 219.0f }, { 1,1 }, mModelManager->bucket[GameObject::object].Get());
	bucket->InitShadow({ 306.0f, 262.8f }, { 1,1 },
		mModelManager->bucket[GameObject::shadow].Get(), Collide::SQUARE);

	picnicBasket->InitObject({ 306.0f, 240.0f }, { 1,1 }, mModelManager->picnicBasket[GameObject::object].Get());
	picnicBasket->InitShadow({ 275.4f, 216.0f }, { 1,1 },
		mModelManager->picnicBasket[GameObject::shadow].Get(), Collide::SQUARE);

	housePlate->SetName("HousePlate");
	lamp->SetName("Lamp");
	coconut->SetName("Coconut");
	lamp1_2->SetName("Lamp1_2");
	iphone->SetName("Iphone");
	triangleBlock->SetName("TriangleBlock");
	bucket->SetName("Bucket");
	newspaper->SetName("Newspaper");
	sandwich->SetName("Sandwich");
	picnicBasket->SetName("PicnicBasket");

	traceEffect = std::make_unique<Effect>();
	traceEffect->InitEffect({ 256,256 }, { 3,4 }, mModelManager->cursor.Get());
	traceEffect->SetActive(true);
	traceEffect->SetTrace(true);
	traceEffect->mSprite->GetAnimation()->SetLoop(true);
	traceEffect->SetSpeed(0.2f);
	traceEffect->mSprite->mRotation.x = 95.f;
}

void Game::InitSound()
{
	// サウンド初期化
	HRESULT hr;
	hr = XA_Initialize();
	if (FAILED(hr))
	{
		MessageBoxA(NULL, "サウンド初期化失敗", "エラー", MB_OK | MB_ICONERROR);
	}

}

void Game::InitStage()
{
	switch(mSceneManager->GetStage())
	{
	case scene::STAGE1_1:
		InitStage1_1();
		break;
	case scene::STAGE1_2:
		InitStage1_2();
		break;
	case scene::STAGE1_3:
		InitStage1_3();
		break;
	}
	//stage
	mUiManager->InitUi();
	//Result Animator Init
	mResultAnimator->Init();

}

void Game::InitStage1_1()
{

	//Set Obj Pos
	housePlate->mObj->mPos = { -4.2f,-5.f,-5.f };
	lamp->mObj->mPos = { 0.0f,-5.f,-2.5f };
	coconut->mObj->mPos =  { -4.2f, -5.f, -2.5f };

	//Set Shadow Pos
	coconut->mShadow->mSprite->mPos.z = 0.0f;
	lamp->mShadow->mSprite->mPos.z = -0.1f;
	housePlate->mShadow->mSprite->mPos.z = -0.2f;

	//影のy軸
	coconut->mShadow->mSprite->mPos.y = 7.1f;
	lamp->mShadow->mSprite->mPos.y = 4.3f;
	housePlate->mShadow->mSprite->mPos.y = 2.3f;

	//レール上の位置を設定する
	coconut->SetRailPos(1, 0);
	lamp->SetRailPos(2, 0);
	housePlate->SetRailPos(1, 1);

	mObjectList.clear();
	mObjectList.shrink_to_fit();
	mObjectList.push_back(coconut.get());
	mObjectList.push_back(lamp.get());
	mObjectList.push_back(housePlate.get());

	for(auto &it:mObjectList)
	{
		it->mMoveX = 4.2f;
		it->mMoveZ = 2.5f;
	}

	//レールの設定
	mRailManger->InitRailPos();
	//ステージの設定
	mSceneManager->mStageHolder[scene::StageInfo::STAGE1_1]->Init();
	//使うステージだけ起動
	mSceneManager->mStageHolder[scene::StageInfo::STAGE1_1]->SetActive(true);
	//STAGE状態をリセット
	mSceneManager->mStageHolder[scene::StageInfo::STAGE1_1]->ResetStage();

	//全部のオブジェクトをINACTIVEに設定する
	for (auto& element : mObjectList) {
		element->SetTarget(false);
		element->ResetMove();
	}
	//移動ターゲットを設定
	coconut->SetTarget(true);
	mResultManager->SetStandard({ 12,14,19,22 });
	
}

void Game::InitStage1_2()
{

	//Z:FRONT:-10 MIDDLE:-7.5 BACK:-5
	lamp1_2->mObj->mPos = { 0.0f,-5.0f,-7.5f };
	iphone->mObj->mPos = { -4.2f,-5.0f,-7.5f };
	triangleBlock->mObj->mPos = { 0.0f,-5.0f,-2.5f };



	//Set Shadow Pos
	lamp1_2->mShadow->mSprite->mPos.z = 0.0f;
	iphone->mShadow->mSprite->mPos.z = -0.1f;
	triangleBlock->mShadow->mSprite->mPos.z = -0.2f;

	//影のy軸
	lamp1_2->mShadow->mSprite->mPos.y = 3.09f;
	iphone->mShadow->mSprite->mPos.y = 4.275f;
	triangleBlock->mShadow->mSprite->mPos.y = 2.2f;

	//レール上の位置を設定する
	lamp1_2->SetRailPos(2, 2);
	iphone->SetRailPos(1, 2);
	triangleBlock->SetRailPos(2, 0);



	mObjectList.clear();
	mObjectList.shrink_to_fit();
	mObjectList.push_back(lamp1_2.get());
	mObjectList.push_back(iphone.get());
	mObjectList.push_back(triangleBlock.get());

	for (auto& it : mObjectList)
	{
		it->mMoveX = 4.2f;
		it->mMoveZ = 2.5f;
	}

	//レールの設定
	mRailManger->InitRailPos();
	//ステージの設定
	mSceneManager->mStageHolder[scene::StageInfo::STAGE1_2]->Init();
	//使うステージだけ起動
	mSceneManager->mStageHolder[scene::StageInfo::STAGE1_2]->SetActive(true);
	//STAGE状態をリセット
	mSceneManager->mStageHolder[scene::StageInfo::STAGE1_2]->ResetStage();

	//全部のオブジェクトをINACTIVEに設定する
	for (auto& element : mObjectList) {
		element->SetTarget(false);
		element->ResetMove();
	}
	//移動ターゲットを設定
	lamp1_2->SetTarget(true);
	mResultManager->SetStandard({ 8,10,15,18 });
	
}

void Game::InitStage1_3()
{
	//Set Obj Pos
	//Z:FRONT:-10 MIDDLE:-7.5 BACK:-5
	bucket->mObj->mPos = { -4.2f,-5.0f,-2.5f };
	newspaper->mObj->mPos = { 0.0f,-5.0f,-2.5f };
	sandwich->mObj->mPos = { 4.2f,-5.0f,-2.5f };
	picnicBasket->mObj->mPos = { 4.2f,-5.0f,-7.5f };


	bucket->mShadow->mSprite->mPos.z = 0.5f;
	newspaper->mShadow->mSprite->mPos.z = 0.4f;
	sandwich->mShadow->mSprite->mPos.z = 0.3f;
	picnicBasket->mShadow->mSprite->mPos.z = 0.2f;


	//影のy軸
	bucket->mShadow->mSprite->mPos.y = 5.0f;
	newspaper->mShadow->mSprite->mPos.y = 2.5f;
	sandwich->mShadow->mSprite->mPos.y = 2.46f;
	picnicBasket->mShadow->mSprite->mPos.y = 3.45f;


	//レール上の位置を設定する
	bucket->SetRailPos(1, 0);
	newspaper->SetRailPos(2, 0);
	sandwich->SetRailPos(3, 0);
	picnicBasket->SetRailPos(3, 2);

	//objectListを初期化
	mObjectList.clear();
	mObjectList.shrink_to_fit();
	mObjectList.push_back(picnicBasket.get());
	mObjectList.push_back(sandwich.get());
	mObjectList.push_back(newspaper.get());
	mObjectList.push_back(bucket.get());

	for (auto& it : mObjectList)
	{
		it->mMoveX = 4.2f;
		it->mMoveZ = 2.5f;
	}

	//レールの設定
	mRailManger->InitRailPos();
	//ステージの設定
	mSceneManager->mStageHolder[scene::StageInfo::STAGE1_3]->Init();
	//使うステージだけ起動
	mSceneManager->mStageHolder[scene::StageInfo::STAGE1_3]->SetActive(true);
	//STAGE状態をリセット
	mSceneManager->mStageHolder[scene::StageInfo::STAGE1_3]->ResetStage();

	//全部のオブジェクトをINACTIVEに設定する
	for (auto& element : mObjectList) {
		element->SetTarget(false);
		element->ResetMove();
	}
	//移動ターゲットを設定
	bucket->SetTarget(true);
	mResultManager->SetStandard({ 24,26,30,33 });
}

void Game::TitleUpdate()
{
	mUiManager->Update();
}

void Game::TutorialUpdate()
{
	mUiManager->Update();
}

void Game::SelectUpdate()
{
	mUiManager->Update();
}

void Game::StageUpdate()
{
	if(KInput::Get()->GetKeyTrigger(DIK_ESCAPE))
	{
		mUiManager->PauseSwitch();
	}



	if(!mUiManager->GetPause()&&!mSceneManager->mStageHolder[mSceneManager->GetStage()]->GetHint()&&!mSceneManager->mStageHolder[mSceneManager->GetStage()]->GetShapeHint())
	{
		//オブジェクトの切り替え
		SwitchObject();

		switch(mSceneManager->GetStage())
		{
		case scene::STAGE1_1:
			//ステージ本体
			UpdateStage1_1();
			break;
		case scene::STAGE1_2:
			//ステージ本体
			UpdateStage1_2();
			break;
		case scene::STAGE1_3:
			//ステージ本体
			UpdateStage1_3();
		case scene::STAGE_EASTER:
			UpdateStageEaster();
			break;
		}



		//Camera Shake
		mShaker->Update(mCamera3D);
		mClearManager->Update();
	}

	mUiManager->Update();

}

void Game::SwitchObject()
{


	if(KInput::Get()->GetKeyTrigger(DIK_SPACE))
	{
		for(auto object=mObjectList.begin();object!=mObjectList.end();object++)
		{
			//
			if ((*object)->GetIsTarget())
			{
				//もしオブジェクトが移動中、switch無効
				if((*object)->GetDir()!=Rail::STILL)
				{
					return;
				}

				DebugLog::Log((*object)->GetName());

				(*object)->SetTarget(false);
				auto nextObject = std::next(object);

				if(nextObject!=mObjectList.end())//列末じゃない場合
				{
					//次のオブジェクトを移動できる
					XA_Play(SE_Select);//セレクトSE再生
					(*nextObject)->SetTarget(true);
				}else//頭に戻る
				{

					XA_Play(SE_Select);//セレクトSE再生
					nextObject = mObjectList.begin();
					(*nextObject)->SetTarget(true);
				}

				break;
			}
		}
	}

}

void Game::UpdateStage1_1()
{
	//背景
	stageBg[scene::STAGE1_1]->Update();

	//MOVE SE


	//本体の更新
	for (auto& element : mObjectList)
	{
		element->Update();
	}

	//影の更新
	coconut->ShadowUpdate(0, 4.4f);
	lamp->ShadowUpdate(0, 4.4f);
	housePlate->ShadowUpdate(0, 4.5f);

	//エフェクト
	traceEffect->Update();

}

void Game::UpdateStage1_2()
{
	//背景
	stageBg[scene::STAGE1_2]->Update();

	//本体の更新
	for (auto& element : mObjectList)
	{
		element->Update();
	}

	//影の更新
	lamp1_2->ShadowUpdate(0.35f, 4.f);
	iphone->ShadowUpdate(-1.33f, 4.f);
	triangleBlock->ShadowUpdate(0, 4.f);

	//エフェクト
	traceEffect->Update();
}

void Game::UpdateStage1_3()
{
	//背景
	stageBg[scene::STAGE1_3]->Update();

	//本体の更新
	for (auto& element : mObjectList)
	{
		element->Update();
	}

	//影の更新
	newspaper->ShadowUpdate(0.0f, 3.6f);
	sandwich->ShadowUpdate(1.0f, 2.8f);
	picnicBasket->ShadowUpdate(1.5f, 3.0f);
	bucket->ShadowUpdate(3.f, 3.2f);

	//エフェクト
	traceEffect->Update();
}

void Game::UpdateStageEaster()
{
}

void Game::ResultUpdate()
{
	stageBg[mSceneManager->GetStage()]->Update();
	if(isResultAnime)
	{
		mResultAnimator->Update();
	}else
	{
		mResultManager->Update();
	}
}

void Game::TitleDraw()
{
	mUiManager->Draw();
}

void Game::TutorialDraw()
{
	mUiManager->Draw();
}

void Game::SelectDraw()
{
	mUiManager->Draw();
}

void Game::StageDraw()
{

	/*switch(mSceneManager->GetStage())
	{
	case scene::STAGE1_1:
		DrawStage1_1();
		break;
	case scene::STAGE1_2:
		DrawStage1_2();
		break;
	case scene::STAGE1_3:
		DrawStage1_3();
		break;
	}*/

	stageBg[mSceneManager->GetStage()]->Draw();

	//描画の順番を並び変え
	SortShadowDraw();
	//オブジェクト
	SortObjectDraw();


	DirectX3D::Get()->SetBlendState(DirectX3D::Get()->GetBlendMultiply());
	stageMask->Draw();
	DirectX3D::Get()->SetBlendState(DirectX3D::Get()->GetBlendAlpha());

	mUiManager->Draw();

}

void Game::DrawStage1_1()
{
	stageBg[0]->Draw();

	//描画の順番を並び変え
	SortShadowDraw();

	//オブジェクト
	SortObjectDraw();


}

void Game::DrawStage1_2()
{
	stageBg[scene::STAGE1_2]->Draw();

	//描画の順番を並び変え
	SortShadowDraw();

	//オブジェクト
	SortObjectDraw();
}

void Game::DrawStage1_3()
{
	stageBg[scene::STAGE1_3]->Draw();

	//描画の順番を並び変え
	SortShadowDraw();

	//オブジェクト
	SortObjectDraw();
}

void Game::SortShadowDraw()
{
	std::sort(mObjectList.begin(), mObjectList.end(), [](GameObject2D* obj1, GameObject2D* obj2) {

		return obj1->mShadow->mSprite->mPos.z > obj2->mShadow->mSprite->mPos.z;
		});


	for (auto& element : mObjectList) {

		element->mShadow->Draw();
	}
}

void Game::SortObjectDraw()
{

	//並び替え
	std::sort(mObjectList.begin(), mObjectList.end(), [](GameObject2D* obj1, GameObject2D* obj2) {
		if (obj1->mObj->mPos.z == obj2->mObj->mPos.z) {
			return obj1->GetRailPos().horPos < obj2->GetRailPos().horPos;
		}
		return obj1->mObj->mPos.z < obj2->mObj->mPos.z;
		});


	for (auto it = mObjectList.begin(); it != mObjectList.end(); it++) {

		bool isOverlap = false;

		if (it != mObjectList.end() - 1) {
			auto nextIt = it + 1;
			while (nextIt != mObjectList.end()) {
				if ((*it)->GetRailPos().horPos == (*nextIt)->GetRailPos().horPos) {
					isOverlap = true;
				}
				nextIt += 1;
			}
		}

		//オブジェクトが重なったら
		if (isOverlap) {

			switch ((*it)->GetRailPos().verPos) {
			case 0:
				(*it)->mObj->mMaterialDiffuse = { 1.0f, 1.0f, 1.0f, 0.8f };
				break;
			case 1:
				(*it)->mObj->mMaterialDiffuse = { 1.0f, 1.0f, 1.0f, 0.6f };
				break;
			case 2:
				(*it)->mObj->mMaterialDiffuse = { 1.0f, 1.0f, 1.0f, 0.45f };
				break;
			}
		}
		else {
			(*it)->mObj->mMaterialDiffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
		}

		//もしターゲットとして
		if ((*it)->GetIsTarget())
		{
			(*it)->mObj->mMaterialDiffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
		}

	}


	//並び替え
	std::sort(mObjectList.begin(), mObjectList.end(), [](GameObject2D* obj1, GameObject2D* obj2) {
		if (obj1->mObj->mPos.z == obj2->mObj->mPos.z) {
			return obj1->GetRailPos().horPos < obj2->GetRailPos().horPos;
		}
		//return obj1->GetRailPos().verticalPos <  obj2->GetRailPos().verticalPos;
		return obj1->mObj->mPos.z > obj2->mObj->mPos.z;
		});


	//描画
	for (auto& element : mObjectList) {

		if (element->GetIsTarget()) {

			traceEffect->Draw();
		}

		element->Draw();
	}
}

void Game::ResultDraw()
{
	stageBg[mSceneManager->GetStage()]->Draw();
	DirectX3D::Get()->SetBlendState(DirectX3D::Get()->GetBlendMultiply());
	resultMask->Draw();
	DirectX3D::Get()->SetBlendState(DirectX3D::Get()->GetBlendAlpha());

	if (isResultAnime)
	{
		mResultAnimator->Draw();
	}else
	{
		mResultManager->Draw();
	}
}
