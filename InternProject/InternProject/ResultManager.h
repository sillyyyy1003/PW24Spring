#pragma once
#include <memory>
#include <vector>

#include "CanvasUI.h"
#include "ResultProcess.h"

namespace Result
{
	enum StartNum
	{
		ZERO,
		ONE,
		TWO,
		THREE,
		FOUR,
		FIVE,
	};

	enum Button
	{
		AGAIN,
		RETURN,
		NEXT,
		NONE,
	};
	
}

class ResultManager
{
private:

	std::vector<int> starStandard;

	int mStarNum = 0;//いくつの星を獲得

	int mResultCounter = 0;//オブジェクト移動用

	int mButtonNum = 0;//ボタンを管理する

	bool isInput = false;//ENTER入力あるかどうか？

	std::unique_ptr<CanvasUI> resultTitle;//リザルトタイトル
	std::unique_ptr<CanvasUI> resultBg;//リザルト背景
	std::unique_ptr<CanvasUI> resultButton[3];//リザルトボタン
	std::unique_ptr<CanvasUI> clearStepTitle;//ステップ数タイトル
	std::unique_ptr<CanvasUI> clearScoreTitle;//★数タイトル
	std::unique_ptr<CanvasUI> star[5];//明るい★
	std::unique_ptr<CanvasUI> starShadow[5];//暗い★
	std::unique_ptr<ResultProcess> resultProcessor;//ステップ数

public:

	ResultManager();
	~ResultManager();

	void Init();
	void Update();
	void Draw();

	/// @brief 星獲得の基準を設定
	/// @param _standard step数の集合
	void SetStandard(std::vector<int> _standard);

	/// @brief ボタンの数字
	/// @param num 
	void SetButtonNum(int num) { mButtonNum = num; };

private:
	/// @brief キー入力
	void DoKeyEvent();

	///入力によってオブジェクトのUpdate
	void ButtonUpdate();

	/// @brief ボタンの上下移動
	/// @param ui ボタン
	/// @param moveSpeed　移動のスピード 
	/// @param moveHeight 移動の幅
	void ObjectMove(CanvasUI* ui, float moveSpeed, float moveHeight);


	/// @brief 評価をもらう 
	/// @param resultStep　ステップ数 
	/// @param StarNum 星の基準
	/// @return 獲得できる星
	int GetScore(int resultStep, std::vector<int> StarNum);

};

