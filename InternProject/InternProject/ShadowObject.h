#pragma once
#include "Collider.h"
#include "Object2D.h"

/// @brief 判定用の影
class ShadowObject
{
public:

	enum SIZE
	{
		IDLE,
		SMALL,
		MEDIUM,
		LARGE,
	};
	SIZE mSize = IDLE;

	std::unique_ptr<Object2D> mSprite = nullptr;

	//当たり判定用の
	std::unique_ptr<Collider> mCollider;
	DirectX::XMFLOAT3 mExtents = {};


public:
	/// @brief 影オブジェクトコライダー作成
	/// @param _type 
	explicit ShadowObject(Collide::ColliderType _type);

	void InitShadow(DirectX::XMFLOAT2 _size,DirectX::XMINT2 _split,ID3D11ShaderResourceView* _assets);

	void Update();

	/// @brief コライダーの初期化
	/// @param _size コライダーの大きさ
	void InitCollider(DirectX::XMFLOAT2 _size);

	void Draw();


};


