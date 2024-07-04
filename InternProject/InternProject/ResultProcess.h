#pragma once
#include "DebugManager.h"
#include "CanvasUI.h"

/// @brief ステップ数を表す
class ResultProcess
{
private:
	static const int maxChars = 256;

	CanvasUI* mStepNum[maxChars] = {};

	//初期位置(頭の文字の位置)
	float msPosX = 0;
	float msPosY = 0;

	//間隔を設定する
	float mInterval = 0.0f;

	//キャラの設定
	float mSize = 0.f;
	float mPosz = 0.2f;

public:
	ResultProcess();
	~ResultProcess();

	void SetSize(float _size) { mSize = _size; };

	void SetPosition(float posX, float posY);

	/// @brief 任意のタイミングで初期化するため
	/// @param posX 文字の位置
	/// @param posY 文字の位置
	/// @param size 文字の大きさ
	/// @param interval 間隔
	void Init(float posX, float posY, float size, float interval);

	//文字を出力する
	void Print(float _posX, float _posY, const char* word, Debug::TEXT_ALIGN _align);

	//float型数字を出力する
	void Print(float _posX, float _posY, const float _num, Debug::TEXT_ALIGN _align);

	//int型数字を出力する
	void Print(float _posX, float _posY, const int _num, Debug::TEXT_ALIGN _align);

private:

	//文字をセット＆描画
	void UpdateChar(char* outputChar, Debug::TEXT_ALIGN _align);


};

