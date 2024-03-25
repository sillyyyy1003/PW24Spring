#include "Camera.h"
using namespace DirectX;

void Camera::SetCameraPos(DirectX::XMFLOAT3 _pos)
{
	mCameraPos = _pos;
}

void Camera::SetFocus(DirectX::XMFLOAT3 _focus)
{
	mFocusPos = _focus;
}

void Camera::SetUpDir(DirectX::XMFLOAT3 _up)
{
	mUpDir = _up;
}

DirectX::XMMATRIX Camera::GetMatrixProj(void)
{
    
    XMMATRIX matrix2D= XMMatrixOrthographicLH(RATIO_W, RATIO_H, 0.0f, 3.0f);
    XMMATRIX matrix3D = XMMatrixPerspectiveFovLH(XMConvertToRadians(45.0f), RATIO_W / RATIO_H, 0.01f, 100.0f);

    switch (mProjMode)
    {
        case _2D:
            return matrix2D;
            break;
        case _3D:
            return matrix3D;
            break;
    }
}

void Camera::Update()

{    //XMLoadFloat3 -> XMFLOAT3をXMVECTORに読み込み
    DirectX::XMVECTOR eye = DirectX::XMLoadFloat3(&mCameraPos);
    DirectX::XMVECTOR focus = DirectX::XMLoadFloat3(&mFocusPos);
    DirectX::XMVECTOR up = DirectX::XMLoadFloat3(&mUpDir);

    //ビュー変換行列を計算
    mMatrixView = DirectX::XMMatrixLookAtLH(eye, focus, up);
}
