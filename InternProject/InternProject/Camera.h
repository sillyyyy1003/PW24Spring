#pragma once
#include "DirectX3D.h"


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

	PROJ_MODE mProjMode= _2D;
	

public:
	//カメラ位置設定
	void SetCamPos(DirectX::XMFLOAT3 _pos) ;

	void SetFocus(DirectX::XMFLOAT3 _focus);

	void SetUpDir(DirectX::XMFLOAT3 _up);

	DirectX::XMMATRIX GetMatrixProj();

	void Update();

	void SetProjMode(PROJ_MODE _mode) { mProjMode = _mode; };

	DirectX::XMMATRIX GetMatrixView() { return mMatrixView; };

};

