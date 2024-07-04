#pragma once
#include "Collider.h"

/// @brief 円形のコライダー
class SphereCollider:public Collider
{
private:
	
	DirectX::BoundingSphere mSphereCollider;

public:
	/// @brief 
	/// @param _type コライダーの形状
	SphereCollider();
	~SphereCollider() override = default;

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


	const DirectX::BoundingSphere& GetCollider(void) const	{ return mSphereCollider; };


private:

	//BoundingSphere更新
	void UpdateSphereCollider(DirectX::XMFLOAT3 _rotation);

};

