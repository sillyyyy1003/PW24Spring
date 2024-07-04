#pragma once
#include <memory>

#include "Scene.h"
#include "Stage.h"

class SceneManager :public Scene
{
public:

	//ステージの情報扱う
	Stage** mStageHolder = nullptr;

	
public:

	//初期化
	SceneManager();

	~SceneManager();// デストラクタ


	/*Update*/
	void Update();

	//今作動中のステージを返す
	int GetActiveStage(void);

};

