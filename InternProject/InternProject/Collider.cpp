#include "Collider.h"
#include "DirectXUti.h"

Collider::Collider()
{
}


void Collider::InitType(Collide::ColliderType _type)
{
	mType = _type;
}

void Collider::InitCollider(DirectX::XMFLOAT2 _size, DirectX::XMFLOAT3 _center)
{
	mCollideData.extents.x = _size.x / 2;
	mCollideData.extents.y = _size.y / 2;
	mCollideData.extents.z = 0.1f;
	mCollideData.radius = mCollideData.extents.x;
	mCenter = _center;
}

void Collider::Update(DirectX::XMFLOAT3 _center, DirectX::XMFLOAT3 _rotation, DirectX::XMFLOAT3 _extents)
{
	mCenter = _center;
	mCollideData.extents = _extents;
	mCollideData.radius = _extents.x;
	mRotation = _rotation;
}

const Collide::ColliderDir Collider::GetCollideDir(const Collider& _col)
{

	Collide::ColliderDir resultDir = {};

	//x軸の位置
	int result = CompResult(this->mCenter.x, _col.mCenter.x);
	switch (result)
	{
	case 0:
		resultDir.hor = Collide::OVERLAP;
		break;
	case 1:
		resultDir.hor = Collide::LEFT;
		break;
	case -1:
		resultDir.hor = Collide::RIGHT;
		break;
	}

	//y軸の位置
	result = CompResult(this->mCenter.x, _col.mCenter.x);
	switch (result)
	{
	case 0:
		resultDir.hor = Collide::OVERLAP;
		break;
	case 1:
		resultDir.hor = Collide::DOWN;
		break;
	case -1:
		resultDir.hor = Collide::UP;
		break;
	}

	return resultDir;

}



