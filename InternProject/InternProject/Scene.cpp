#include "Scene.h"
#include "Game.h"
#include "xa2.h"

Scene::Scene(void)
{


}

scene::StageInfo Scene::CalNextStage(scene::StageInfo stage)
{
	int stageNum = stage;
	stageNum++;

	if (stageNum > 2)
	{
		return scene::STAGE_EASTER;
	}else
	{
		return static_cast<scene::StageInfo>(stageNum);
	}

}

void Scene::ChangeScene(scene::SCENE _scene, scene::TRANSITION _transition)
{
	SetNextScene(_scene);
	switch(_transition)
	{
	case scene::FADE:
		Game::Get()->GetFade()->FadeOut();
		break;
	}
	//全ての音声を消す
	XA_Stop(BGM_TITLE);
	XA_Stop(BGM_Stage1);
	XA_Stop(BGM_Stage2);
	XA_Stop(BGM_Stage3);
	XA_Stop(BGM_SelectStage);

}
