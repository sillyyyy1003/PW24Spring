#include "Stage.h"

void Stage::Init()
{
	//ステージをクリアしてない状態をセットする
	isClear = false;

	//移動数をリセットする
	mMoveStep = 0;

	isActive = false;

	isHint = false;
	isShapeHint = false;
}

void Stage::StepCount()
{
	if(isActive)
	{
		mMoveStep++;
	}
}
