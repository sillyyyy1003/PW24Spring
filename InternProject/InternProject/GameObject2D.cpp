// ReSharper disable All
#include "GameObject2D.h"
#include "DebugLog.h"
#include "DebugManager.h"
#include "Game.h"
#include "KInput.h"
#include "SceneManager.h"
#include "WinMain.h"
#include "xa2.h"

extern Time gTime;

void GameObject2D::DoKeyInput()
{
	mInputCount++;
	//mInputCount = gTime.GetNowCount();
	if ((KInput::Get()->GetKeyPress(DIK_DOWNARROW) || KInput::Get()->GetKeyPress(DIK_UPARROW) || KInput::Get()->GetKeyPress(DIK_RIGHTARROW) || KInput::Get()->GetKeyPress(DIK_LEFTARROW))) {
		if (!isInput) {
			//時間測定開始
			isInput = true;
			mLastPressTime = mInputCount;
		}
	}

	//入力判定開始
	if(isInput)
	{
		//5 FRAME以内
		if (mInputCount <= mLastPressTime + 5)
		{
			isGetInput = false;
			//垂直方向
			if (KInput::Get()->GetKeyTrigger(DIK_DOWNARROW) && !KInput::Get()->GetKeyTrigger(DIK_UPARROW))
			{
				mNowInput.verInput = GameObject::DOWN;
			}
			if (KInput::Get()->GetKeyTrigger(DIK_UPARROW) && !KInput::Get()->GetKeyTrigger(DIK_DOWNARROW))
			{
				mNowInput.verInput = GameObject::UP;
			}
			// 水平方向
			if (KInput::Get()->GetKeyTrigger(DIK_LEFTARROW) && !KInput::Get()->GetKeyTrigger(DIK_RIGHTARROW))
			{
				mNowInput.horInput = GameObject::LEFT;
			}
			if (KInput::Get()->GetKeyTrigger(DIK_RIGHTARROW) && !KInput::Get()->GetKeyTrigger(DIK_LEFTARROW))
			{
				mNowInput.horInput = GameObject::RIGHT;
			}
		}
		else {
			//方向の受け入り完成
			isGetInput = true;
			//入力終了
			isInput = false;
			
		}
		
	}
	else
	{
		//方向を初期化にする
		mNowInput.horInput = GameObject::NONE;
		mNowInput.verInput = GameObject::NONE;
	}

}

void GameObject2D::ObjectMove()
{

	DirectX::XMFLOAT3 moveSpeed = { 0,0,0 };
	if (mMoveX != 0 && mMoveZ != 0)
	{
		moveSpeed.x = mMoveX / 25;
		moveSpeed.z = mMoveZ / 25;
	}
	int oldPos;
	int targetPos; 

	switch (mMoveDir) {
	case Rail::UP:

		//moveSpeed.z = 0.1f;
		if (mMoveCount * moveSpeed.z <= mMoveZ) {

			mObj->mPos.z += moveSpeed.z;
			mObj->mScale.x -= 0.004f;
			mObj->mScale.y -= 0.004f;
		}
		else {
			//移動終了
			mMoveDir = Rail::STILL;
			//int pos = mRailPos.verPos * 5 + mRailPos.horPos;
			//移動終了後レールの情報更新
			oldPos = mRailPos.verPos * 5 + mRailPos.horPos;
			//Pointの情報を更新する
			mRailPos.verPos -= 1;
			// 移動したの情報更新する
			targetPos = mRailPos.verPos * 5 + mRailPos.horPos;
			
			
		}
		
		break;

	case Rail::UPRIGHT:
		//moveSpeed.x = 0.18f;
		//moveSpeed.z = 0.1f;
		if (mMoveCount * moveSpeed.z <= mMoveZ && mMoveCount * moveSpeed.x <= mMoveX) {

			mObj->mPos.z += moveSpeed.z;
			//大きさを調整する
			mObj->mScale.x -= 0.004f;
			mObj->mScale.y -= 0.004f;

			mObj->mPos.x += moveSpeed.x;
			if (std::abs(mObj->mPos.x) < std::numeric_limits<float>::epsilon()) {
				mObj->mPos.x = 0.0f;  // 修正为零，防止失去有效值
			}
		}
		else {
			//移動終了
			mMoveDir = Rail::STILL;
			//移動終了後レールの情報更新
			oldPos = mRailPos.verPos * 5 + mRailPos.horPos;
			//Pointの情報を更新する
			mRailPos.horPos += 1;
			mRailPos.verPos -= 1;
			targetPos = mRailPos.verPos * 5 + mRailPos.horPos;
		}
		
		break;

	case Rail::RIGHT:

		//moveSpeed.x = 0.18f;

		if ((mMoveCount * moveSpeed.x) <= mMoveX) {


			mObj->mPos.x += moveSpeed.x;

			// 检查x值是否接近零
			if (std::abs(mObj->mPos.x) < std::numeric_limits<float>::epsilon()) {
				mObj->mPos.x = 0.0f;  // 修正为零，防止失去有效值
			}

		}
		else {
			//移動終了
			mMoveDir = Rail::STILL;
			//移動終了後レールの情報更新
			oldPos = mRailPos.verPos * 5 + mRailPos.horPos;
			//Pointの情報を更新する
			mRailPos.horPos += 1;
			targetPos = mRailPos.verPos * 5 + mRailPos.horPos;
		}
		
		break;

	case Rail::DOWNRIGHT:

		//moveSpeed.x = 0.18f;
		//moveSpeed.z = 0.1f;
		if (mMoveCount * moveSpeed.z <= mMoveZ && mMoveCount * moveSpeed.x <= mMoveX) {

			mObj->mPos.z -= moveSpeed.z;
			//大きさを調整する
			mObj->mScale.x += 0.004f;
			mObj->mScale.y += 0.004f;
			mObj->mPos.x += moveSpeed.x;

			if (std::abs(mObj->mPos.x) < std::numeric_limits<float>::epsilon()) {
				mObj->mPos.x = 0.0f;  // 修正为零，防止失去有效值
			}
		}
		else {
			//移動終了
			mMoveDir = Rail::STILL;
			//移動終了後レールの情報更新
			oldPos = mRailPos.verPos * 5 + mRailPos.horPos;
			//Pointの情報を更新する
			mRailPos.horPos += 1;
			mRailPos.verPos += 1;
			targetPos = mRailPos.verPos * 5 + mRailPos.horPos;

		}
		
		break;

	case Rail::DOWN:

		//moveSpeed.z = 0.1f;

		if (mMoveCount * moveSpeed.z <= mMoveZ) {

			mObj->mPos.z -= moveSpeed.z;
			//大きさを調整する
			mObj->mScale.x += 0.004f;
			mObj->mScale.y += 0.004f;
		}
		else {
			//移動終了
			mMoveDir = Rail::STILL;
			//移動終了後レールの情報更新
			oldPos = mRailPos.verPos * 5 + mRailPos.horPos;
			//Pointの情報を更新する
			mRailPos.verPos += 1;
			targetPos = mRailPos.verPos * 5 + mRailPos.horPos;

		}
		break;

	case Rail::DOWNLEFT:
		//moveSpeed.x = 0.18f;
		//moveSpeed.z = 0.1f;
		if (mMoveCount * moveSpeed.z <= mMoveZ && mMoveCount * moveSpeed.x <= mMoveX) {
			mObj->mPos.z -= moveSpeed.z;
			//大きさを調整する
			mObj->mScale.x += 0.004f;
			mObj->mScale.y += 0.004f;
			mObj->mPos.x -= moveSpeed.x;
			if (std::abs(mObj->mPos.x) < std::numeric_limits<float>::epsilon()) {
				mObj->mPos.x = 0.0f;  // 修正为零，防止失去有效值
			}
		}
		else {
			//移動終了
			mMoveDir = Rail::STILL;
			//移動終了後レールの情報更新
			oldPos = mRailPos.verPos * 5 + mRailPos.horPos;
			//Pointの情報を更新する
			mRailPos.horPos -= 1;
			mRailPos.verPos += 1;
			targetPos = mRailPos.verPos * 5 + mRailPos.horPos;
		}
		
		break;

	case Rail::LEFT:

		//moveSpeed.x = 0.18f;
		if (mMoveCount * moveSpeed.x <= mMoveX) {
			mObj->mPos.x -= moveSpeed.x;
			if (std::abs(mObj->mPos.x) < std::numeric_limits<float>::epsilon()) {
				mObj->mPos.x = 0.0f;  // 修正为零，防止失去有效值
			}
		}
		else {
			//移動終了
			mMoveDir = Rail::STILL;
			//いち
			oldPos = mRailPos.verPos * 5 + mRailPos.horPos;
			//Pointの情報を更新する
			mRailPos.horPos -= 1;
			targetPos = mRailPos.verPos * 5 + mRailPos.horPos;
		}
		
		break;

	case Rail::UPLEFT:

		//moveSpeed.x = 0.18f;
		//moveSpeed.z = 0.1f;
		if (mMoveCount * moveSpeed.z <= mMoveZ && mMoveCount * moveSpeed.x <= mMoveX)
		{

			//大きさを調整する
			mObj->mScale.x -= 0.004f;
			mObj->mScale.y -= 0.004f;
			mObj->mPos.z += moveSpeed.z;
			mObj->mPos.x -= moveSpeed.x;
			if (std::abs(mObj->mPos.x) < std::numeric_limits<float>::epsilon()) {
				mObj->mPos.x = 0.0f;  // 修正为零，防止失去有效值
			}

		}
		else {
			//移動終了
			mMoveDir = Rail::STILL;

			//移動終了後レールの情報更新
			oldPos = mRailPos.verPos * 5 + mRailPos.horPos;
			//Pointの情報を更新する
			mRailPos.horPos -= 1;
			mRailPos.verPos -= 1;
			targetPos = mRailPos.verPos * 5 + mRailPos.horPos;
		}
		
		break;

	case Rail::STILL:

		break;
	}

	//Counter++
	mMoveCount++;

	//When Get Target Pos
	if(mMoveDir==Rail::STILL)
	{
		mMoveCount = 0;
		//移動前の情報更新
		Game::Get()->GetRailManager()->mInfo[oldPos].isVacant = true;
		Game::Get()->GetRailManager()->mInfo[targetPos].isVacant = false;
		//移動完成後ステップ加算
		int stageInfo = Game::Get()->GetSceneManager()->GetActiveStage();
		Game::Get()->GetSceneManager()->mStageHolder[stageInfo]->StepCount();

		isGetInput = false;
	
	}

}

void GameObject2D::Update()
{
	
	if(isTarget)
	{
		mObj->SetisLight(true);

		//クリアしたら移動できなように制限をかける
		if(Game::Get()->GetSceneManager()->mStageHolder[Game::Get()->GetSceneManager()->GetStage()]->GetClear())
		{
			return;
		}

		if (mMoveDir != Rail::STILL)
		{
			ObjectMove();

		}else
		{
			//入力チェック
			DoKeyInput();

			//移動方向を決める　
			SetMove();

		}

	}else
	{
		mObj->SetisLight(false);
	}

	mObj->Update();

}

void GameObject2D::ShadowUpdate(float center, float interval)
{
	//影の移動(位置)
	ShadowPosUpdate(center,interval);

	//大きさ(移動)
	ShadowSizeUpdate(0.02f);

	//当たり判定
	mShadow->Update();
	
}

void GameObject2D::Draw()
{
	mObj->Draw();
}

void GameObject2D::SetRailPos(int horPos, int verPos)
{
	mRailPos.horPos = horPos;
	mRailPos.verPos = verPos;

	//ここでオブジェクトの大きさの初期値を調整する
	switch (mRailPos.verPos)
	{
	case 0://BACK
		mObj->mScale = { 0.8f,0.8f,1.0f };
		mShadow->mSprite->mScale.x = 1.0f;
		mShadow->mSprite->mScale.y = 1.0f;
		mShadow->mSize = ShadowObject::SMALL;

		break;
	case 1://MIDDLE
		mObj->mScale = { 0.9f,0.9f,1.0f };
		mShadow->mSprite->mScale.x = 1.5f;
		mShadow->mSprite->mScale.y = 1.5f;
		mShadow->mSize = ShadowObject::MEDIUM;
		break;
	case 2:
		mObj->mScale = { 1.0f,1.0f,1.0f };
		mShadow->mSprite->mScale.x = 2.0f;
		mShadow->mSprite->mScale.y = 2.0f;
		mShadow->mSize = ShadowObject::LARGE;
		break;
	default:
		break;
	}
}

void GameObject2D::ResetMove()
{
	mMoveDir = Rail::STILL;

	//移動用のカウンター
	mMoveCount = 0;

	//入力待ちカウンター
	mInputCount = 0;

	//入力
	mLastPressTime = 0;

	//時間測定開始
	isInput = false;

	//方向を受ける
	isGetInput = false;

	//移動しているかどうか？
	isMove = false;

	//入力の結果
	mNowInput = { GameObject::NONE,GameObject::NONE };

	//入力の時間計算
	int m_countTime = 0;
}

void GameObject2D::InitObject(DirectX::XMFLOAT2 _size, DirectX::XMINT2 _split, ID3D11ShaderResourceView* _assets)
{
	mObj = std::make_unique<Object2D>();
	mObj->InitObject(_size, _split, _assets, Anime::SINGLE_PATTERN, ModelSet::BOTTOM);
}

void GameObject2D::InitShadow(DirectX::XMFLOAT2 _size, DirectX::XMINT2 _split, ID3D11ShaderResourceView* _assets, Collide::ColliderType _type)
{
	mShadow = std::make_unique<ShadowObject>(_type);
	mShadow->InitShadow(_size, _split, _assets);
}

void GameObject2D::ObjectVibration()
{
	//振動スタート
	if (!Game::Get()->GetCameraShaker()->GetShaker()) {
		//音声
		XA_Play(SE_Limitation);
		Game::Get()->GetCameraShaker()->SetShaker(true);
	}
}

void GameObject2D::SetMove()
{
	if (!isGetInput)
	{
		return;
	}
	else
	{
		GameObject::InputCom noneInput = { GameObject::NONE, GameObject::NONE };
		//移動できるかどうかをチェック
		if (!IsMoveable(mNowInput))
		{
			ObjectVibration();
		}
		
	}

}

bool GameObject2D::IsMoveable(Rail::Dir dir)
{
	//現在の位置を取得
	int originalPos = mRailPos.GetPoint();
	Rail::PointInfo info = Game::Get()->GetRailManager()->mInfo[originalPos];

	int targetPos = 0;
	int targetDir = 0;

	switch (dir)
	{
	case Rail::UP:
		targetPos = (mRailPos.verPos - 1) * 5 + mRailPos.horPos;
		targetDir = Rail::UP;
		break;

	case Rail::UPRIGHT:
		targetPos = (mRailPos.verPos - 1) * 5 + mRailPos.horPos + 1;
		targetDir = Rail::UPRIGHT;
		break;

	case Rail::RIGHT:
		targetPos = mRailPos.verPos * 5 + mRailPos.horPos + 1;
		targetDir = Rail::RIGHT;
		break;

	case Rail::DOWNRIGHT:
		targetPos = (mRailPos.verPos + 1) * 5 + mRailPos.horPos + 1;
		targetDir = Rail::DOWNRIGHT;
		break;

	case Rail::DOWN:
		targetPos = (mRailPos.verPos + 1) * 5 + mRailPos.horPos;
		targetDir = Rail::DOWN;
		break;

	case Rail::DOWNLEFT:
		targetPos = (mRailPos.verPos + 1) * 5 + mRailPos.horPos - 1;
		targetDir = Rail::DOWNLEFT;
		break;

	case Rail::LEFT:
		targetPos = mRailPos.verPos * 5 + mRailPos.horPos - 1;
		targetDir = Rail::LEFT;
		break;

	case Rail::UPLEFT:
		targetPos = (mRailPos.verPos - 1) * 5 + mRailPos.horPos - 1;
		targetDir = Rail::UPLEFT;
		break;
	case Rail::STILL:
		break;
	}

	if (targetPos < 0 || targetPos>14) {

		DebugLog::Log("point calculate error！");
		return false;

	}

	//繋がってるかどうか？
	if (!info.isMoveable[targetDir]) {

		XA_Play(SE_Limitation);//動かせない場合のSE再生
		return false;
	}

	//目標位置は空いてるか？
	if (Game::Get()->GetRailManager()->mInfo[targetPos].isVacant) {
		
		return true;
	}
	else {
		return false;
	}

}

bool GameObject2D::IsMoveable(GameObject::InputCom input)
{
	
	//元のデータを取得
	int verPos = mRailPos.verPos;
	int horPos = mRailPos.horPos;

	int originPos = verPos * 5 + horPos;
	Rail::PointInfo info = Game::Get()->GetRailManager()->mInfo[originPos];
	

	switch(input.verInput)
	{
	case GameObject::Input::UP:
		verPos--;
		break;
	case GameObject::Input::DOWN:
		verPos++;
		break;
	default:
		break;
	}

	switch(input.horInput)
	{
	case GameObject::Input::LEFT:
		horPos--;
		break;
	case  GameObject::Input::RIGHT:
		horPos++;
		break;
	default:
		break;
	}

	//ターゲットの目標を計算
	int targetPos = verPos * 5 + horPos;

	//Error Check
	if (targetPos < 0 || targetPos>14) {
		DebugLog::Log("point Calculate Error！");
		return false;
	}

	int targetDir = 0;
	//移動方向を取得
	switch (mNowInput.horInput)
	{
		case GameObject::Input::LEFT:
			switch (mNowInput.verInput)
			{
			case GameObject::UP:
				targetDir = Rail::Dir::UPLEFT;
				break;
			case GameObject::DOWN:
				targetDir = Rail::Dir::DOWNLEFT;
				break;
			case GameObject::NONE:
				targetDir = Rail::Dir::LEFT;
			}
			break;
		case GameObject::Input::RIGHT:
			switch (mNowInput.verInput)
			{
			case GameObject::UP:
				targetDir = Rail::Dir::UPRIGHT;
				break;
			case GameObject::DOWN:
				targetDir = Rail::Dir::DOWNRIGHT;
				break;
			case GameObject::NONE:
				targetDir = Rail::Dir::RIGHT;
			}
			break;
		case GameObject::Input::NONE:
			switch (mNowInput.verInput)
			{
			case GameObject::UP:
				targetDir = Rail::Dir::UP;
				break;
			case GameObject::DOWN:
				targetDir = Rail::Dir::DOWN;
				break;
			case GameObject::NONE:
				isGetInput = false;
				return true;
				break;
			}
			break;
	}

	

	//繋がってるかどうか？
	if (!info.isMoveable[targetDir]) {
		XA_Play(SE_Limitation);//動かせない場合のSE再生
		//方向を初期化にする
		return false;
	}

	//目標位置は空いてるか？
	if (Game::Get()->GetRailManager()->mInfo[targetPos].isVacant) {
		//移動方向を渡す
		mMoveDir = static_cast<Rail::Dir>(targetDir);
		return true;
		
	}
	else {
		return false;
	}


}

void GameObject2D::ShadowPosUpdate(float _center, float _interval)
{
	float pos[5] = {
		_center - 2 * _interval,
		_center - _interval,
		_center,
		_center + _interval,
		_center + 2 * _interval,
	};

	float moveSpeed = _interval / 25;

	switch (mMoveDir)
	{
	case Rail::UP:
		break;
	case Rail::UPRIGHT:
		if (moveSpeed * mMoveCount <= _interval)
		{
			mShadow->mSprite->mPos.x += moveSpeed;
		}
		break;
	case Rail::RIGHT:
		if (moveSpeed * mMoveCount <= _interval)
		{
			mShadow->mSprite->mPos.x += moveSpeed;
		}
		break;
	case Rail::DOWNRIGHT:
		if (moveSpeed * mMoveCount <= _interval)
		{
			mShadow->mSprite->mPos.x += moveSpeed;
		}
		break;
	case Rail::DOWN:
		break;
	case Rail::DOWNLEFT:
		if (moveSpeed * mMoveCount <= _interval)
		{
			mShadow->mSprite->mPos.x -= moveSpeed;
		}
		break;
	case Rail::LEFT:
		if (moveSpeed * mMoveCount <= _interval)
		{
			mShadow->mSprite->mPos.x -= moveSpeed;
		}
		break;
	case Rail::UPLEFT:
		if (moveSpeed * mMoveCount <= _interval)
		{
			mShadow->mSprite->mPos.x -= moveSpeed;
		}

		break;
	case Rail::STILL:
		//横 0:LEFT1 1:LEFT2 2:MIDDLE 3:RIGHT1 4:RIGHT2
		mShadow->mSprite->mPos.x = pos[mRailPos.horPos];
		break;
	default:
		break;
	}
}

void GameObject2D::ShadowSizeUpdate(float speed)
{

	if (isTarget) {
		switch (mMoveDir)
		{
		case Rail::UP:
			mShadow->mSprite->mScale.x -= speed;
			mShadow->mSprite->mScale.y -= speed;

			break;
		case Rail::UPRIGHT:
			mShadow->mSprite->mScale.x -= speed;
			mShadow->mSprite->mScale.y -= speed;

			break;
		case Rail::RIGHT:

			break;
		case Rail::DOWNRIGHT:
			mShadow->mSprite->mScale.x += speed;
			mShadow->mSprite->mScale.y += speed;

			break;
		case Rail::DOWN:
			mShadow->mSprite->mScale.x += speed;
			mShadow->mSprite->mScale.y += speed;
			break;
		case Rail::DOWNLEFT:
			mShadow->mSprite->mScale.x += speed;
			mShadow->mSprite->mScale.y += speed;

			break;
		case Rail::LEFT:

			break;
		case Rail::UPLEFT:
			mShadow->mSprite->mScale.x -= speed;
			mShadow->mSprite->mScale.y -= speed;

			break;
		case Rail::STILL:

			switch (mRailPos.verPos) {

			case 0:
				mShadow->mSize = ShadowObject::SIZE::SMALL;//当たり判定用
				mShadow->mSprite->mScale.x = 1.0f;
				mShadow->mSprite->mScale.y = 1.0f;
				break;

			case 1:
				mShadow->mSize = ShadowObject::SIZE::MEDIUM;//当たり判定用
				mShadow->mSprite->mScale.x = 1.5f;
				mShadow->mSprite->mScale.y = 1.5f;
				break;

			case 2:
				mShadow->mSize = ShadowObject::SIZE::LARGE;//当たり判定用
				mShadow->mSprite->mScale.x = 2.0f;
				mShadow->mSprite->mScale.y = 2.0f;
				break;
			}

			break;
		default:
			break;
		}
	}
}

