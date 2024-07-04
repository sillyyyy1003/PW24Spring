#pragma once
#define STAGE_NUM	(9)//STAGE AMOUNT


namespace scene
{
	enum SCENE
	{
		NONE,
		TITLE,
		TUTORIAL,
		STAGESELECT,
		STAGE,
		RESULT,
	};

	//FOR SCENE TRANSITION
	enum TRANSITION
	{
		FADE,

	};

	enum StageInfo
	{
		STAGE1_1 = 0,
		STAGE1_2 = 1,
		STAGE1_3 = 2,
		STAGE_NULL,

		STAGE_EASTER = 999 ,
	};

	enum ResultInfo
	{
		RESULT1_1,
		RESULT1_2,
		RESULT1_3,
	};

	
}

class Scene
{
private:
	scene::SCENE mScene = scene::NONE;
	scene::SCENE mNextScene = scene::NONE;

	scene::StageInfo mStage;
	scene::StageInfo mNextStage = scene::STAGE_NULL;
	scene::ResultInfo mResult;

public:

	Scene(void);

	//Set This Scene
	void SetScene(scene::SCENE _scene) { mScene = _scene; };
	scene::SCENE GetScene() { return mScene; };

	//Set Next Scene
	void SetNextScene(scene::SCENE _nextScene) { mNextScene = _nextScene; };
	scene::SCENE GetNextScene() { return mNextScene; };

	void SetStage(scene::StageInfo _stage) { mStage = _stage; };
	scene::StageInfo GetStage() { return mStage; };

	void SetNextStage(scene::StageInfo _stage) { mNextStage = _stage; };

	/// @brief 次のステージ
	/// @return 
	scene::StageInfo GetNextStage() { return mNextStage; };

	/// @brief 次のステージを計算する
	/// @param stage 今のステージ
	/// @return 次のステージ
	scene::StageInfo CalNextStage(scene::StageInfo stage);

	void ChangeScene(scene::SCENE _scene,scene::TRANSITION _transition);




};

