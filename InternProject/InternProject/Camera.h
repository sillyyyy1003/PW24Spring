#pragma once
#include "DirectX3D.h"
#define ROTATEX		(0.360022f)	//カメラの回転角度tan19.8°

class Camera
{
public:

	//投影モード
	enum PROJ_MODE {
		_2D,
		_3D,
	};

private:
	//カメラ用の行列
	DirectX::XMMATRIX mMatrixView;
	//カメラの位置
	DirectX::XMFLOAT3 mCameraPos = {0.0f,0.0f,-1.0f};
	//注視点
	DirectX::XMFLOAT3 mFocusPos = DirectX::XMFLOAT3(0.0f, 0.0f, 1.0f);
	//カメラの上方向
	DirectX::XMFLOAT3 mUpDir = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);

	//DirectX::XMFLOAT3 mCameraPos = DirectX::XMFLOAT3(0.0f, 7.119f, -21.626f);
	////注視点
	//DirectX::XMFLOAT3 mFocusPos = DirectX::XMFLOAT3(0.0f, 0.0f, -(21.626f - 7.0f / ROTATEX));
	////カメラの上方向
	//DirectX::XMFLOAT3 mUpDir = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);
	PROJ_MODE mProjMode= _2D;
	

public:
	//カメラ位置設定
	void SetCamPos(DirectX::XMFLOAT3 _pos) ;
	const DirectX::XMFLOAT3 GetCamPos() { return mCameraPos; };

	//注視点設定
	void SetFocus(DirectX::XMFLOAT3 _focus);
	const DirectX::XMFLOAT3 GetFocus() { return mFocusPos; };

	//カメラの上方向設定
	void SetUpDir(DirectX::XMFLOAT3 _up);
	const DirectX::XMFLOAT3 GetUpDir() { return mUpDir; };

	//投影行列作成と取得
	DirectX::XMMATRIX GetMatrixProj();

	void Update();

	//投影モード設定
	void SetProjMode(PROJ_MODE _mode) { mProjMode = _mode; };

	//カメラ行列
	DirectX::XMMATRIX GetMatrixView() { return mMatrixView; };

};

