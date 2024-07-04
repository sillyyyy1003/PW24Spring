#pragma once
class Stage
{
private:
	bool isHint = false;//ヒント出されたかステージ最初のヒント
	bool isShapeHint = false;//形のヒント
	bool isClear = false;//ステージクリアしたかどうか
	bool isCompleted = false;//一回クリアしたか

	int mMoveStep = 0;//移動の数
	bool isActive = false;//ステージは作動中かどうか

public:
	Stage() = default;
	~Stage() = default;

	/// @brief Initialization
	void Init(void);

	void Update(void);

	
	void SetActive(bool _isActive) { isActive = _isActive; };
	bool GetActive() { return isActive; };


	void SetClear(bool _isClear) { this->isClear = _isClear; };
	bool GetClear(void) { return isClear; };

	
	void SetCompleted(bool _isCompleted) { this->isCompleted = _isCompleted; };
	bool GetCompleted(void) { return isCompleted; };

	//Count Step
	void StepCount(void);

	void HintPunish(int step) { mMoveStep += step; };
	int GetStep(void) { return mMoveStep; };

	//Reset Clear Status& Step Number
	void ResetStage(void) { mMoveStep = 0; isClear = false; };

	//hintの判断
	bool GetHint(void) { return isHint; };
	void SetHint(bool _isHint) { this->isHint = _isHint; };

	bool GetShapeHint() { return isShapeHint; };
	void SetShapeHint(bool _isHint) { this->isShapeHint = _isHint; };
};

