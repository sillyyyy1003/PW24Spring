#pragma once
#include <memory>

#include "CameraShaker.h"
#include "ClearManager.h"
#include "DebugManager.h"
#include "ModelManager.h"
#include "LayerManager.h"
#include "Fade.h"
#include "GameObject2D.h"
#include "RailManager.h"
#include "Effect.h"
#include "ResultAnimator.h"
#include "ResultManager.h"
#include "SceneManager.h"
#include "StaticObject.h"
#include "UiManager.h"


class Camera;
class KInput;
class Object;


class Game
{
private:
	Game() {};
	~Game();

private:

	//Tool 
	std::unique_ptr<ModelManager> mModelManager;
	std::unique_ptr<LayerManager> mLayerManager;
	std::unique_ptr<RailManager> mRailManger;
	std::unique_ptr<SceneManager> mSceneManager;
	std::unique_ptr<ResultManager> mResultManager;
	std::unique_ptr<UiManager> mUiManager;
	std::unique_ptr<CameraShaker> mShaker;
	std::unique_ptr<Fade> mFade;//FadeIn/Out
	std::unique_ptr<ClearManager> mClearManager;
	std::unique_ptr<ResultAnimator> mResultAnimator;

	std::unique_ptr<DebugManager> mDebugLog;//デバッグ用

	//操作できるかどうか
	bool isControl = true;
	//アニメ演出しているか
	bool isResultAnime = false;
	//移動SE
	bool isPlaySE;

	//Camera
	Camera* mMainCamera = nullptr;
	Camera* mCamera2D = nullptr;
	Camera* mCamera3D = nullptr;

	//GameObject
	std::vector<GameObject2D*> mObjectList;//並び替え用

	std::unique_ptr<StaticObject>  stageBg[3];//ステージ1背景

	std::unique_ptr<GameObject2D>  coconut;
	std::unique_ptr<GameObject2D>  lamp;
	std::unique_ptr<GameObject2D>  housePlate;

	std::unique_ptr<GameObject2D>  lamp1_2;
	std::unique_ptr<GameObject2D>  triangleBlock;
	std::unique_ptr<GameObject2D>  iphone;

	std::unique_ptr<GameObject2D>  sandwich;
	std::unique_ptr<GameObject2D>  newspaper;
	std::unique_ptr<GameObject2D>  bucket;
	std::unique_ptr<GameObject2D>  picnicBasket;


	std::unique_ptr<Effect>	traceEffect;

	//mask
	std::unique_ptr<CanvasUI> stageMask;
	std::unique_ptr<CanvasUI> resultMask;
	
	//初期設定
	float seVolume = 3;
	float bgmVolume = 3;


public:
	int isTutorialFinish[3] = {};

public:

	static Game* Get() { static Game Instance; return &Instance; };

	Camera* GetCamera2D() { return mCamera2D; };
	Camera* GetCamera3D() { return mCamera3D; }
	void SetMainCamera(Camera* _camera) { mMainCamera = _camera; };

	GameObject2D dufaultObj;

	//初期化
	void InitGame();

	//更新
	void Update();

	//描画
	void Draw();

	/// @brief
	/// ステージの初期化(Dataの設定など
	void InitStage();

	//Getter Serious
	ModelManager* GetModelManager() { return mModelManager.get(); };
	LayerManager* GetLayerManager() { return mLayerManager.get(); };
	Fade* GetFade() { return mFade.get(); }
	RailManager* GetRailManager() { return mRailManger.get(); };
	SceneManager* GetSceneManager() { return mSceneManager.get(); };
	CameraShaker* GetCameraShaker() { return mShaker.get(); };
	ResultManager* GetResultManager() { return mResultManager.get(); };

	std::vector<GameObject2D*> GetObjectList() { return mObjectList; };

	void SetIsControl(bool isControl) { this->isControl = isControl; };
	bool GetIsControl() { return isControl; };

	void SetResultAnime(bool isResultAnime) { this->isResultAnime = isResultAnime; };
	bool GetResultAnime() { return isResultAnime; };

	void SetSEVolume(float num) { seVolume = num; };
	float GetSEVolume() { return seVolume; };
	void SetBGMVolume(float num) { bgmVolume = num; };
	float GetBGMVolume() { return bgmVolume; };

	void ApplyVolume();

private:


	/// @brief 各Manager初期化
	void InitTool();
	/// @brief カメラ関連の初期化
	void InitCamera();
	/// @brief　オブジェクトの初期化
	void InitObject();
	/// @brief UIの初期化
	void InitUI();
	/// @brief ゲームオブジェクトの初期化
	void InitGameObject();
	/// @brief サウンドの初期化
	void InitSound();


	//ステージの初期化を行う関数：キャラの位置、大きさなど
	void InitStage1_1(void);
	void InitStage1_2(void);
	void InitStage1_3(void);

	/// @brief Title
	void TitleUpdate();

	/// @brief tutorial
	void TutorialUpdate();

	/// @brief ステージ選択
	void SelectUpdate();


	/// @brief Stage
	void StageUpdate();

	void SwitchObject();

	/// @brief stage1_1
	void UpdateStage1_1();
	void UpdateStage1_2();
	void UpdateStage1_3();
	void UpdateStageEaster();



	/// @brief result
	void ResultUpdate();

	void TitleDraw();

	void TutorialDraw();

	void SelectDraw();

	void StageDraw();

	void DrawStage1_1();
	void DrawStage1_2();
	void DrawStage1_3();

	void SortShadowDraw();
	void SortObjectDraw();


	void ResultDraw();


};

