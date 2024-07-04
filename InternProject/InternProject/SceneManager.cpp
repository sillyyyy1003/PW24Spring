#include "SceneManager.h"

SceneManager::SceneManager()
{
	mStageHolder = new Stage * [STAGE_NUM];

	//ステージを初期化
	for (int i = 0; i < STAGE_NUM; i++)
	{
		mStageHolder[i] = new Stage();
	}
}

SceneManager::~SceneManager()
{
	for (int i = 0; i < STAGE_NUM; i++) {
		delete mStageHolder[i];
	}
}


void SceneManager::Update()
{
}

int SceneManager::GetActiveStage()
{
	int num = Scene::GetStage();
	return static_cast<scene::StageInfo>(num);
}
