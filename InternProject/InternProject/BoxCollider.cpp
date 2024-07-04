#include "BoxCollider.h"
#include "SphereCollider.h"


BoxCollider::BoxCollider()
{
}

void BoxCollider::InitCollider(const DirectX::XMFLOAT2 _size, const DirectX::XMFLOAT3 _center)
{
    //基底データを更新
	Collider::InitCollider(_size, _center);

    mBoxCollider.Center = this->mCenter;
    mBoxCollider.Extents = this->mCollideData.extents;
    mBoxCollider.Orientation = { 0,0,0,0 };
}

void BoxCollider::UpdateRotation()
{
    DirectX::XMFLOAT4 orientation;
    //degreeからradiansに変換
    float roll = DirectX::XMConvertToRadians(mRotation.x);      //x軸回転
    float pitch = DirectX::XMConvertToRadians(mRotation.y);     //y軸回転
    float yaw = DirectX::XMConvertToRadians(mRotation.z);       //z軸回転

    //xmfloat4に変換する
    DirectX::XMVECTOR vector = DirectX::XMQuaternionRotationRollPitchYaw(pitch, yaw, roll);
    DirectX::XMStoreFloat4(&orientation, vector);

    //計算できた値を代入
    mBoxCollider.Orientation = orientation;
}

void BoxCollider::UpdateBoxCollider()
{
    mBoxCollider.Center = mCenter;
    mBoxCollider.Extents = this->mCollideData.extents;
    UpdateRotation();
}


void BoxCollider::Update(const DirectX::XMFLOAT3 _center, const DirectX::XMFLOAT3 _rotation, const DirectX::XMFLOAT3 _extents)
{
    if (!isActive)
    {
        return;
    }
    else
    {
        //本体更新
        Collider::Update(_center, _rotation, _extents);
        //BoxColliderに渡す
        UpdateBoxCollider();
        UpdateRotation();//

        //mBoxCollider.Center = _center;
        //mBoxCollider.Extents = _extents;
    }

}

bool BoxCollider::isCollision(const SphereCollider& _collider)
{
    if (this->mBoxCollider.Intersects(_collider.GetCollider())) {
        return true;
    }

	return false;

}

bool BoxCollider::isCollision(const BoxCollider& _collider)
{
    if (this->mBoxCollider.Intersects(_collider.GetCollider())) {
        return true;
    }
	return false;

}

bool BoxCollider::isCollision(const Collider& _collider)
{
	return  Collider::isCollision(_collider);
}
