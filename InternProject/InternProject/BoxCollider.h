#pragma once
#include "Collider.h"

/// @brief 箱
class BoxCollider : public Collider
{
private:
	//オブジェクトの回転もあるのでOBBを使う
	DirectX::BoundingOrientedBox mBoxCollider;

public:
	/// @brief 
	/// @param _type コライダーの形状
	BoxCollider();
	~BoxCollider() override = default;

	void InitCollider(const DirectX::XMFLOAT2 _size, const DirectX::XMFLOAT3 _center) override;

	/// @brief 
	/// @param _center 中心
	/// @param _rotation 回転
	/// @param _extents 半辺長
	void Update(const DirectX::XMFLOAT3 _center, const DirectX::XMFLOAT3 _rotation, const DirectX::XMFLOAT3 _extents) override;

	/// @brief 
	/// @param _collider Sphere
	/// @return 
	bool isCollision(const SphereCollider& _collider) override;


	/// @brief 
	/// @param _collider Box
	/// @return 
	bool isCollision(const BoxCollider& _collider) override;


	/// @brief 
	/// @param _collider Original Collider
	/// @return 
	bool isCollision(const Collider& _collider) override;

	const DirectX::BoundingOrientedBox& GetCollider(void)  const
	{ return mBoxCollider; };


private:

	//四角形の回転を更新する関数
	void UpdateRotation();
	//OBB更新
	void UpdateBoxCollider();


};

