#include "CameraShaker.h"

void CameraShaker::ShakerUpdate()
{  // ランダムな変位を生成
    DirectX::XMFLOAT3 displacement = RandomDisplacement();

    // カメラの位置と注視点を更新
    mNewCameraPos = DirectX::XMFLOAT3(mOriginalCameraPos.x + displacement.x,
        mOriginalCameraPos.y + displacement.y,
        mOriginalCameraPos.z + displacement.z);
    mNewCameraFocus = DirectX::XMFLOAT3(mOriginalCameraFocus.x + displacement.x,
        mOriginalCameraFocus.y + displacement.y,
        mOriginalCameraFocus.z + displacement.z);
}

DirectX::XMFLOAT3 CameraShaker::RandomDisplacement()
{
    std::uniform_real_distribution<float> distribution(-mIntensity, mIntensity);
    float dx = distribution(mRandomEngine);
    float dy = distribution(mRandomEngine);
    float dz = distribution(mRandomEngine);
    return DirectX::XMFLOAT3(dx, dy, dz);
}

void CameraShaker::Update(Camera* mCamera)
{
    if (isShake)
    {
        // カメラシェイカーを更新
        ShakerUpdate();

        if (elapsedTime > mTotalTime)
        {
            // カメラを元の位置に戻す
            mNewCameraPos = mOriginalCameraPos;
            mNewCameraFocus = mOriginalCameraFocus;
        }

        // 新しいカメラの位置と注視点を取得
        DirectX::XMFLOAT3 newCameraPos = GetNewCameraPos();
        DirectX::XMFLOAT3 newCameraFocus = GetNewCameraFocus();

        // ここで新しいカメラの位置と注視点を使用して描画などの処理を行う
        mCamera->SetCamPos(newCameraPos);
        mCamera->SetFocus(newCameraFocus);
        mCamera->Update();

        if (elapsedTime > mTotalTime)
        {
            isShake = false;
        }

        // 更新時間を加算
        elapsedTime++;

    }
    else
    {
        // 更新時間を初期化
        elapsedTime = 0;
        // カメラの初期位置と注視点を設定
        SetOriginalCameraParams(mCamera->GetCamPos(), mCamera->GetFocus());
    }
}

void CameraShaker::Init(float intensity, float frequency, float totalTime)
{

    mIntensity = intensity;
    mFrequency = frequency;
    mTotalTime = totalTime;
    // 乱数生成器を初期化
    mRandomEngine.seed(std::random_device()());
}

void CameraShaker::SetOriginalCameraParams(const DirectX::XMFLOAT3& cameraPos, const DirectX::XMFLOAT3& cameraFocus)
{
    
	mOriginalCameraPos = cameraPos;
	mOriginalCameraFocus = cameraFocus;
    
}
