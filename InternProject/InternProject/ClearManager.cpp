#include "ClearManager.h"
#include "DebugLog.h"
#include "Game.h"
#include "xa2.h"

void ClearManager::Update()
{
	switch(Game::Get()->GetSceneManager()->GetStage())
	{
	case scene::STAGE1_1:
		ClearStage1_1();
		break;
	case scene::STAGE1_2:
		ClearStage1_2();
		break;
	case scene::STAGE1_3:
		ClearStage1_3();
		break;
	}
}

void ClearManager::ClearStage1_1()
{
	bool isStageClear = false;

	//could use unordered_map
	//縦	 0:BACK 1:MIDDLE 2:FRONT
	//横 0:LEFT1 1:LEFT2 2:MIDDLE 3:RIGHT1 4:RIGHT2
	if(isClear("Coconut",{1,1})&&isClear("Lamp",{0,1})&&isClear("HousePlate",{2,1}))
	{
		isStageClear = true;
	}

	if(isStageClear)
	{
		Game::Get()->GetSceneManager()->mStageHolder[Game::Get()->GetSceneManager()->GetStage()]->SetClear(true);

		
		Game::Get()->GetSceneManager()->ChangeScene(scene::RESULT, scene::FADE);
		Game::Get()->SetResultAnime(true);
		XA_Play(SE_Interval1);
	}
}

void ClearManager::ClearStage1_2()
{
	bool isStageClear = false;

	//could use unordered_map
	//縦	 0:BACK 1:MIDDLE 2:FRONT
	//横 0:LEFT1 1:LEFT2 2:MIDDLE 3:RIGHT1 4:RIGHT2
	if (isClear("Lamp1_2", { 1,2 }) && isClear("Iphone", { 0,2 }) && isClear("TriangleBlock", { 2,2}))
	{
		isStageClear = true;
	}

	if (isStageClear)
	{
		Game::Get()->GetSceneManager()->mStageHolder[Game::Get()->GetSceneManager()->GetStage()]->SetClear(true);
		Game::Get()->GetSceneManager()->ChangeScene(scene::RESULT, scene::FADE);
		Game::Get()->SetResultAnime(true);
		XA_Play(SE_Interval2);
	}
}

void ClearManager::ClearStage1_3()
{
	//could use unordered_map
	//縦	 0:BACK 1:MIDDLE 2:FRONT
	//横 0:LEFT1 1:LEFT2 2:MIDDLE 3:RIGHT1 4:RIGHT2
	bool isStageClear = false;
	if (isClear("Bucket", { 0,3 }) && isClear("Newspaper", { 0,4 }) && isClear("Sandwich", { 2,3 }) && isClear("PicnicBasket", { 2,2 }))
	{
		isStageClear = true;
	}

	if (isStageClear)
	{
		Game::Get()->GetSceneManager()->mStageHolder[Game::Get()->GetSceneManager()->GetStage()]->SetClear(true);
		Game::Get()->GetSceneManager()->ChangeScene(scene::RESULT, scene::FADE);
		Game::Get()->SetResultAnime(true);
		XA_Play(SE_Interval3);
	}
}

bool ClearManager::isClear(std::string name, GameObject::RailPos pos)
{
	//
	if (&FindObj(name, Game::Get()->GetObjectList()) != &(Game::Get()->dufaultObj))
	{
		if(FindObj(name,Game::Get()->GetObjectList()).GetRailPos()==pos)
		{
			return true;
		}
		return false;
	}else
	{
		DebugLog::Log("Can't Find " + name);
		return false;
	}
}

GameObject2D& ClearManager::FindObj(std::string name, std::vector<GameObject2D*> vObj)
{
	auto it = std::find_if(vObj.begin(), vObj.end(), [&name](const GameObject2D* obj) {
		return obj->mName == name;
		});
	if (it != vObj.end())
	{
		return **it;
	}
	else
	{
		return Game::Get()->dufaultObj;
		DebugLog::Log("Can't Find" + name);
	}
}
