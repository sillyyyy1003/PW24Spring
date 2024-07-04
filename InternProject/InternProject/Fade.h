#pragma once
#include "CanvasUI.h"



class Fade
{
private:

	//FADEの速度
	float mFadeSpeed = 0.02f;


public:
	std::unique_ptr<CanvasUI> mFadePanel;//画面に被るSprite

	Fade();
	~Fade();

	void Update();
	void Draw();

	void FadeIn();
	void FadeOut();

	enum
	{
		None,	// 何もフェードしていない状態
		Fade_In,// フェードイン中
		Fade_Out// フェードアウト中
	};

	//Fadeの状態を扱う
	int mState;

};

