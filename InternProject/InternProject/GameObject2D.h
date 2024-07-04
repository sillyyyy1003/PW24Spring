#pragma once
#include "Object2D.h"
#include "RailManager.h"
#include "ShadowObject.h"

namespace  GameObject
{
	struct RailPos
	{
		int verPos = 0;	//縦	 0:BACK 1:MIDDLE 2:FRONT
		int horPos = 0;	//横 0:LEFT1 1:LEFT2 2:MIDDLE 3:RIGHT1 4:RIGHT2

		//OverLoad ==
		bool operator==(const RailPos&other)const
		{
			return(verPos == other.verPos && horPos == other.horPos);
		}

		bool operator!=(const RailPos&other)const
		{
			return(verPos != other.verPos || horPos != other.horPos);

		}
	public:
		int GetPoint() const
		{
			int num = verPos * 5 + horPos;
			return num;
		}
	};

	//入力判定用
	enum Input
	{
		NONE,
		UP,
		RIGHT,
		DOWN,
		LEFT,
		
	};

	struct InputCom
	{
		Input verInput = NONE;
		Input horInput = NONE;

		bool operator!=(const InputCom& other)
		{
			return verInput != other.verInput || horInput != other.horInput;
		}

		bool operator==(const InputCom& other)
		{
			return verInput == other.verInput && horInput == other.horInput;
		}
	};

	enum Object
	{
		object = 0,
		shadow = 1,
	};
}

/// @brief レール上のオブジェクト
class GameObject2D 
{
private:
	
	GameObject::RailPos mRailPos={};	//レール上の位置
	Rail::Dir mMoveDir = Rail::STILL;	//移動の方向
	

	GameObject::InputCom mNowInput;
	long long mInputCount = 0;//入力待ちカウンター
	long long mLastPressTime = 0;//入力
	bool isInput = false;//時間測定開始
	bool isGetInput = false;//方向を受ける

	bool isTarget = false;//今の操作対象オブジェクト？

	bool isMove = false;//移動中かどうか？

	int mMoveCount = 0;

public :

	std::unique_ptr<Object2D> mObj = nullptr;
	std::unique_ptr<ShadowObject> mShadow = nullptr;

	std::string mName;

	float mMoveX = 0;//X軸
	float mMoveZ = 0;//Z軸

private:
	void DoKeyInput(void);

	
	

public:
	GameObject2D() = default;
	~GameObject2D() = default;

	/// @brief 本体初期化
	/// @param _size 大きさ
	/// @param _split 分割
	/// @param _assets モデル
	void InitObject(DirectX::XMFLOAT2 _size, DirectX::XMINT2 _split, ID3D11ShaderResourceView* _assets);

	/// @brief 影の初期化
	/// @param _size 大きさ
	/// @param _split 分割
	/// @param _assets モデル
	/// @param _type 当たり判定の形状
	void InitShadow(DirectX::XMFLOAT2 _size, DirectX::XMINT2 _split, ID3D11ShaderResourceView* _assets, Collide::ColliderType _type);

	const GameObject::RailPos GetRailPos() { return mRailPos; };

	void SetTarget(bool _isTarget) { isTarget = _isTarget; }
	bool GetIsTarget(void) const { return isTarget; };

	void SetName(std::string _name) { mName = _name; }
	std::string GetName(void) const { return mName; };

	void ObjectMove();

	/// @brief 本体のUpdate
	void Update(void);

	/// @brief 影のUpdate
	/// @param center 移動用中心点
	/// @param interval 移動用間隔
	void ShadowUpdate(float center, float interval);

	void Draw();

	/// @brief レール上位置設定 大きさを設定
	/// @param horPos 横　0:LEFT1 1:LEFT2 2:MIDDLE 3:RIGHT1 4:RIGHT
	/// @param verPos 縦　0:BACK 1:MIDDLE 2:FRONT
	void SetRailPos(int horPos, int verPos);

	/// @brief 移動・入力関連全部リセット
	void ResetMove();

	/// @brief 今の移動状態を取得
	/// @return 
	Rail::Dir GetDir() { return mMoveDir; };

private:
	/// @brief 移動できない時の表示
	void ObjectVibration();

	/// @brief 移動の方向を決める
	void SetMove();

	bool IsMoveable(Rail::Dir dir);

	/// @brief 
	/// @param input 入力方向
	/// @return 移動できるかどうか
	bool IsMoveable(GameObject::InputCom input);

	/// @brief 影の位置更新
	/// @param _center 中心点
	/// @param _interval 間隔
	void ShadowPosUpdate(float _center, float _interval);

	/// @brief 本体の行動によって、影のサイズの変換)
	///	mSizeの更新はここで行う
	/// @param speed サイズ変換の速度
	void ShadowSizeUpdate(float speed);
};

