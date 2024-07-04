#pragma once
#include "Camera.h"
#include <DirectXMath.h>
#include <random>



/// @brief shake the camera when objects can't move
class CameraShaker
{
private:
	bool isShake = false;//カメラを揺らすか

    float elapsedTime = 0; // カメラが揺れる時間
    float mIntensity = 0; // カメラの揺れの強度
    float mFrequency = 0; // カメラの揺れの周波数
    float mShakeTime = 0; // 揺れ効果の残り時間
    float mTotalTime = 0;


    DirectX::XMFLOAT3 mOriginalCameraPos; // オリジナルのカメラの位置
    DirectX::XMFLOAT3 mOriginalCameraFocus; // オリジナルのカメラの注視点

    DirectX::XMFLOAT3 mNewCameraPos; // 揺れ後の新しいカメラの位置
    DirectX::XMFLOAT3 mNewCameraFocus; // 揺れ後の新しいカメラの注視点

    std::default_random_engine mRandomEngine; // 乱数生成器

    // カメラを揺らすメソッド
    void ShakerUpdate();

    // ランダムな変位を生成する関数
    DirectX::XMFLOAT3 RandomDisplacement();

public:
	void Update(Camera* mCamera);

    CameraShaker() {};

	~CameraShaker() = default;

	bool GetShaker() const { return isShake; }
	void SetShaker(bool isShake) { this->isShake = isShake; };

	/// @brief 初期化
	/// @param intensity 強度
	/// @param frequency 周波数
	/// @param totalTime 継続時間
	void Init(float intensity, float frequency, float totalTime);

    /// @brief オリジナルのカメラの位置と注視点を設定するメソッド
    void SetOriginalCameraParams(const DirectX::XMFLOAT3& cameraPos, const DirectX::XMFLOAT3& cameraFocus);

    /// @brief  新しいカメラの位置を取得するメソッド
    DirectX::XMFLOAT3 GetNewCameraPos() const { return mNewCameraPos;   }

    /// @brief  新しいカメラの注視点を取得するメソッド
    DirectX::XMFLOAT3 GetNewCameraFocus() const { return mNewCameraFocus;    }

};