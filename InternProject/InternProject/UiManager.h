#pragma once
#include <memory>
#include "CanvasUI.h"

class ResultProcess;

enum  TUTORIAL_SKILL
{
	INTRODUCE,
	MOVE1,
	MOVE2,
	MOVE3,
	MOVE4,
	SIZECHANGE,
	COMBINITION,
	END,
};

enum {
	MOVETUTORIAL = 0,
	SPACETUTORIAL = 1,
	HINTTUTORIAL = 2,
	IDLETUTORIAL = 99,
	FINISHED = 100,
};


/// @brief 各種類UIを司る
class UiManager
{
public:
	bool isPause = false;//ステージ用pause

private:

	int mStageNum = 0;//stage数
	int mChapterNum = 0;//チャプター数

	//TUTORIAL
	bool isTutorOver = false;//チュートリアル用アニメが終了したかどうか？

	//STAGE SELECT
	bool isSelectStage = true;
	int mSelectCounter = 0;//Cursor上下移動用

	//Stage
	bool isSound = false;
	int pauseNum = 4;
	bool isSelectBgm = true;

	//stageTutorial

	int tutorialNum = 0;
	bool isNextTutorial = false;
	int tutorialCounter = 0;

	std::unique_ptr<CanvasUI> title;

	std::unique_ptr<CanvasUI> uiTutorial[8];
	std::unique_ptr<CanvasUI> tutorialPageIn[8];
	int mTutorialNum = 8;


	TUTORIAL_SKILL tutorial = INTRODUCE;
	

	//セレクト
	enum SELECTSTAGE {
		STAGE1,
		STAGE2,
		STAGE3,
		STAGE_IDLE,
	};

	enum SELECTCHAPTER {
		CHAPTER1,
		CHAPTER2,
		CHAPTER3,
		CHAPTER_IDLE,
	};

	SELECTSTAGE selectStage = STAGE_IDLE;
	SELECTCHAPTER selectChapter = CHAPTER_IDLE;


	std::unique_ptr<CanvasUI> uiSelectBg;//背景
	std::unique_ptr<CanvasUI> uiSelectCursor;//ステージセレクトのカーソル
	std::unique_ptr<CanvasUI> uiSelectStage[3];//ステージ
	std::unique_ptr<CanvasUI>  uiSelectChapter[3];//チャプター
	std::unique_ptr<CanvasUI>  uiClearMark[3];//クリアの印
	std::unique_ptr<CanvasUI>  stageMask;//Stage側を暗くするマスク
	std::unique_ptr<CanvasUI> chapterMask;//chapter側を暗くするマスク


	enum PAUSESELECT {
		RESUME=0,
		RESTART = 1,
		BACKSELECT = 2,
		SOUND = 3,
		PAUSE_IDLE,
	};
	PAUSESELECT pauseSelect = PAUSE_IDLE;

	std::unique_ptr<CanvasUI> uiPauseBg;		//PAUSEの背景
	std::unique_ptr<CanvasUI> uiPauseButton[4];
	std::unique_ptr<CanvasUI> pauseMask;		//pauseの時画面を全体的に暗くなるmask

	std::unique_ptr<CanvasUI> uiSoundCursor;	//サウンド用カーソル
	std::unique_ptr<CanvasUI> uiSoundBg;		//SOUNDの背景
	std::unique_ptr<CanvasUI> uiSoundOp_BGM[5];	//BGM設定
	std::unique_ptr<CanvasUI> uiSoundOp_SE[5];	//SE設定

	std::unique_ptr<CanvasUI> stageTutorial[3];	//最初のステージのTutorial

	std::unique_ptr<CanvasUI> stageHint[3];
	std::unique_ptr<CanvasUI> stageShapeHint[3];
	std::unique_ptr<CanvasUI> hintBg;
	bool isHint;//ヒントが出されたかどうか？



	std::unique_ptr<ResultProcess> uiStepNum;
	std::unique_ptr<CanvasUI> controlPanel;//上に置いてあるパネル
	std::unique_ptr<CanvasUI> uiArrow;

public:
	UiManager();
	~UiManager();

	void Init();


	void Update();

	//描画
	void Draw();

	/// @brief uiのパラメーターを設定する
	void InitUi();


	void SetPause(bool isPause) { this->isPause = isPause; };
	bool GetPause() { return isPause; };
	void SetSound(bool isSound) { this->isSound = isSound; };
	bool GetSound() { return isSound; };

	bool GetHint() { return isHint; };

	void PauseSwitch();
private:

	//アニメションと位置設定
	void InitTitle();//タイトル
	void InitTutorial();//チュートリアル
	void InitStageSelect();//選択画面
	void InitStage();

	//Update
	void TitleUpdate();
	void TutorialUpdate();

	void SelectUpdate();
	void ObjectMove(CanvasUI* pObject, float moveSpeed, float bounceHeight);
	void DoSelectKey();
	void SetSelectStatus();

	void StageUpdate();
	void DoStageKey();
	void HintUpdate();
	void StageTutorial();

	void DoPauseEvent();
	void DoSoundEvent();


	//描画
	void TitleDraw();
	void TutorialDraw();
	void SelectDraw();
	void StageDraw();
};





