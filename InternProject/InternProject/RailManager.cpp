#include "RailManager.h"
#include "Game.h"

namespace RailData
{
	bool RailDataList[3][15][8]
	{
		//stage1
		{
			//back row
			//up	ru  r	rd d	ld l	lu
			{	0,	0,	1,	0,	0,	0,	0,	0},//0
			{	0,	0,	1,	0,	1,	0,	1,	0},//1
			{	0,	0,	1,	0,	0,	0,	1,	0},//2
			{	0,	0,	1,	0,	0,	0,	1,	0},//3
			{	0,	0,	0,	0,	0,	0,	1,	0},//4

			//mid row
			{	0,	0,	0,	0,	0,	0,	0,	0},
			{	1,	0,	0,	0,	1,	0,	0,	0},
			{	0,	0,	0,	0,	0,	0,	0,	0},
			{	0,	0,	0,	0,	0,	0,	0,	0},
			{	0,	0,	0,	0,	0,	0,	0,	0},

			//front row
			{	0,	0,	0,	0,	0,	0,	0,	0},
			{	1,	0,	0,	0,	0,	0,	0,	0},
			{	0,	0,	0,	0,	0,	0,	0,	0},
			{	0,	0,	0,	0,	0,	0,	0,	0},
			{	0,	0,	0,	0,	0,	0,	0,	0},
		},
		//stage2
		{

			{	0,	0,	0,	0,	0,	0,	0,	0},//0
			{	0,	0,	0,	0,	0,	0,	0,	0},//1
			{	0,	0,	0,	0,	1,	0,	0,	0},//2
			{	0,	0,	0,	0,	0,	0,	0,	0},//3
			{	0,	0,	0,	0,	0,	0,	0,	0},//4

			//mid row
			{	0,	0,	0,	0,	0,	0,	0,	0},
			{	0,	0,	0,	0,	0,	0,	0,	0},
			{	1,	0,	0,	1,	0,	1,	0,	0},
			{	0,	0,	0,	0,	0,	0,	0,	0},
			{	0,	0,	0,	0,	0,	0,	0,	0},

			//front row
			{	0,	0,	0,	0,	0,	0,	0,	0},
			{	0,	1,	1,	0,	0,	0,	0,	0},
			{	0,	0,	1,	0,	0,	0,	1,	0},
			{	0,	0,	0,	0,	0,	0,	1,	1},
			{	0,	0,	0,	0,	0,	0,	0,	0},
		},

		//stage3
		{
			{	0,	0,	0,	0,	0,	0,	0,	0},//0
			{	0,	0,	1,	0,	0,	0,	0,	0},//1
			{	0,	0,	1,	0,	0,	1,	1,	0},//2
			{	0,	0,	1,	0,	0,	1,	1,	0},//3
			{	0,	0,	0,	0,	0,	0,	1,	0},//4

			//mid row
			{	0,	0,	0,	0,	0,	0,	0,	0},
			{	0,	1,	0,	1,	0,	0,	0,	0},
			{	0,	1,	0,	0,	0,	0,	0,	0},
			{	0,	0,	0,	0,	0,	0,	0,	0},
			{	0,	0,	0,	0,	0,	0,	0,	0},

			//front row
			{	0,	0,	0,	0,	0,	0,	0,	0},
			{	0,	0,	0,	0,	0,	0,	0,	0},
			{	0,	0,	1,	0,	0,	0,	0,	1},
			{	0,	0,	0,	0,	0,	0,	1,	0},
			{	0,	0,	0,	0,	0,	0,	0,	0},
		},
	};

}

RailManager::RailManager()
{
	InitRail();
}

RailManager::~RailManager()
{
}

void RailManager::InitRail()
{
	for (int i = 0; i < 15; i++)
	{
		//1全部をオープンにする
		mInfo[i].isVacant = true;

		//2
		for (int j = 0; j < 8; j++) 
		{
			mInfo[i].isMoveable[j] = false;
		}
	}
}

void RailManager::InitRailPos()
{
	//レールリセット
	InitRail();

	//通路セット
	for (int i = 0; i < 15; i++) {

		for (int j = 0; j < 8; j++) {

			if (RailData::RailDataList[Game::Get()->GetSceneManager()->GetStage()][i][j] == 0) {

				mInfo[i].isMoveable[j] = false;
			}
			else {
				mInfo[i].isMoveable[j] = true;
			}

		}

	}

	//位置のセット
	for (auto& element : Game::Get()->GetObjectList()) {

		//位置を獲得
		int pos = element->GetRailPos().verPos * 5 + element->GetRailPos().horPos;

		//情報更新
		mInfo[pos].isVacant = false;
	}
}
