#pragma once
#include "CanvasUI.h"
#include "string.h"

namespace Debug
{
	enum TEXT_ALIGN
	{
		CENTER,
		LEFT,
		RIGHT,
	};


}

class DebugManager
{
private:
	//最大表示可能文字数
	static const int maxChars = 256;

	CanvasUI* mDebugASCII[maxChars] = {};

	//初期位置(頭の文字の位置)
	float msPosX = 0;
	float msPosY = 0;

	//
	float mInterval = 0.0f;

	float mSize = 0.f;

public:
	/// @brief 
	/// @param _size 文字の大きさ
	DebugManager(float _size);
	~DebugManager();

	//文字をセット＆描画
	void UpdateChar(char* outputChar, Debug::TEXT_ALIGN _align);

	//文字列のスタート位置を設定
	void SetPosition(float posX, float posY);

	//文字を出力する
	void PrintDebugLog(float _posX, float _posY, const char* word, Debug::TEXT_ALIGN _align);


	//float型数字を出力する
	void PrintDebugLog(float _posX, float _posY, const float _num, Debug::TEXT_ALIGN _align);

	//int型数字を出力する
	void PrintDebugLog(float _posX, float _posY, const int _num, Debug::TEXT_ALIGN _align);

};


