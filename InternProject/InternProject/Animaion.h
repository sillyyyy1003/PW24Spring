﻿#pragma once
#include "DirectX3D.h"
#include <vector>

/*
每一种类型的动画均为横一排 资源制作时需注意
*/
//For 2D Obj & 2D Effect
class Animaion
{

private:
	DirectX::XMFLOAT2 mOffsetUV = { 0.0f,0.0f };
	
	DirectX::XMINT2 mFrame = { 0,0 };

	DirectX::XMINT2 mSplit = { 1,1 };

	//AnimeTable Counter
	float mAnimeCounter = 0.0f;

	//AnimeSpeed
	float mAnimeSpeed = 0.0f;

	//Is Loop or Not
	bool isLoop = false;

	//is Now Playing or Not
	bool isPlaying = false;

	//AnimeTable Array
	std::vector<int> mAnimeTable;


	/*
		以下代码用于当图片不是一行可能存在多个动画时使用
	*/
	//横フレームの何番目からスタート
	int mStartFrame = 0;

	//横フレームの何番目まで終わる
	int mEndFrame = 0;

public:

	Animaion();

	~Animaion();

	virtual void InitAnime(DirectX::XMINT2 _split);

	virtual void Update();

	virtual void UpdateIsPlaying();

	virtual void UpdateUV();

	//AnimeSpeed
	float GetAnimeSpeed() { return mAnimeSpeed; };
	void SetAnimeSpeed(float _speed) { mAnimeSpeed = _speed; }

	//Loop Switch
	void SetLoop(bool isLoop) { this->isLoop = isLoop; };
	bool GetLoop() { return isLoop; };

	//Play Switch
	void SetPlaying(bool isPlaying) { this->isPlaying = isPlaying; };
	bool GetPlaying() { return isPlaying; };

	//横何番目を設定する
	void SetFrameX(int _frameX);

	//縦何番目を設定する->AnimePattern
	void SetFrameY(int _frameY);





};


