#pragma once
#include <DirectXCollision.h>
#include <vector>

namespace Collide
{
	struct CollideData
	{
		DirectX::XMFLOAT3 extents;	//当たり判定用　Square
		float radius;				//当たり判定用　Sphere

	};

	enum ColliderType
	{
		NULL_TYPE,
		SPHERE,
		SQUARE,
		//TRIANGLE,
	};

	enum CollideDir
	{
		NULL_DIR,
		UP,
		DOWN,
		LEFT,
		RIGHT,
		OVERLAP,//重なる
	};

	struct ColliderDir
	{
		CollideDir ver;	//vertical
		CollideDir hor;	//horizontal


		bool operator==(const ColliderDir& other) const
		{
			return (ver == other.ver) && (hor == other.hor);
		}
	};

}

class BoxCollider;
class SphereCollider;

class Collider
{
protected:
	//xyz軸の半辺長
	Collide::CollideData mCollideData = {};
	//中心点の位置
	DirectX::XMFLOAT3 mCenter = {};
	//回転
	DirectX::XMFLOAT3 mRotation = {};

	Collide::ColliderType mType = Collide::NULL_TYPE;

	//コライダーは起動しているか
	bool isActive = true;
	

public:
	Collider();
	
	virtual ~Collider() = default;

	/// @brief 
	/// @param _type Typeの初期化
	virtual void InitType(Collide::ColliderType _type);

	/// @brief コライダーの初期化
	/// @param _size x&y 半辺長
	/// @param _center 中心点の位置
	virtual void InitCollider(const DirectX::XMFLOAT2 _size,const DirectX::XMFLOAT3 _center);

	const Collide::ColliderType GetColliderType() { return mType; };

	virtual void Update(const DirectX::XMFLOAT3 _center, const DirectX::XMFLOAT3 _rotation, const DirectX::XMFLOAT3 _extents);


	virtual bool isCollision(const BoxCollider& boxColliser) { return false; };
	virtual bool isCollision(const SphereCollider& sphereCollider) { return false; };
	virtual bool isCollision(const Collider& _col) { return false; };

	/// @brief 
	/// @param _col 比較対象のコライダー
	/// @return 本体に対して、対象オブジェクトの位置
	const Collide::ColliderDir GetCollideDir(const Collider& _col);

	
	const DirectX::XMFLOAT3 GetExtents(void) { return mCollideData.extents; }


};

