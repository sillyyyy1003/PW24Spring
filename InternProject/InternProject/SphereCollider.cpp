#include "SphereCollider.h"
#include "BoxCollider.h"

SphereCollider::SphereCollider()
{
}

void SphereCollider::InitCollider(const DirectX::XMFLOAT2 _size, const DirectX::XMFLOAT3 _center)
{
	 Collider::InitCollider(_size, _center);
	mSphereCollider.Center = mCenter;
	mSphereCollider.Radius = mCollideData.radius;
}

void SphereCollider::Update(const DirectX::XMFLOAT3 _center, const DirectX::XMFLOAT3 _rotation,
	const DirectX::XMFLOAT3 _extents)
{
	if(!isActive)
	{
		return;
	}else
	{
		 Collider::Update(_center, _rotation, _extents);
		//SphereColliderに渡す
		UpdateSphereCollider(_rotation);
	}
	
}

bool SphereCollider::isCollision(const SphereCollider& _collider)
{
	if (this->mSphereCollider.Intersects(_collider.GetCollider())) {
		return true;
	}
	return false;
	
}

bool SphereCollider::isCollision(const BoxCollider& _collider)
{
	if (this->mSphereCollider.Intersects(_collider.GetCollider())) {
		return true;
	}
	return false;

}

bool SphereCollider::isCollision(const Collider& _collider)
{
	return  Collider::isCollision(_collider);

}


void SphereCollider::UpdateSphereCollider(DirectX::XMFLOAT3 _rotation)
{
	mSphereCollider.Center = mCenter;
	mSphereCollider.Radius = mCollideData.radius;
}
