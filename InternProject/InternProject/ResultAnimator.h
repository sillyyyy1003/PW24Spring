#pragma once
#include "CanvasUI.h"

/// @brief クリア後のアニメ演出
class ResultAnimator
{
	
	float mWaitLimit = 60.0f;//画像が止まってから次の画像をが来るまでの待機時間
	float mRotateTime = 2.0f;//画像の回転回数(定位置につくまでに何回転させるか）//２回転
	float mMoveSpeed = 1.7f;//画像の動く速度

private:

	float mWaitCount = 0;
	float mWatiCount2 = 0;

	std::unique_ptr<CanvasUI> mStageAnime[3][3];
	std::unique_ptr<CanvasUI> mSkip;

	bool Move();

public:

	/*bool isAnime = false;*/
	ResultAnimator();
	~ResultAnimator() = default;

	void Init();
	void Update();;
	void Draw();
	
	

};

