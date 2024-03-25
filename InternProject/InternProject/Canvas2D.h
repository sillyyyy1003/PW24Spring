#pragma once
#include "Model.h"

class Camera;
class Animation;

//2D:Using Sprite&Texture
class Canvas2D
{
private:

	//PARAMETER
	DirectX::XMFLOAT3 mPos = {};//ワールド座標
	DirectX::XMFLOAT3 mRotation = {};//回転
	DirectX::XMFLOAT3 mScale = { 1.0f,1.0f,1.0f };//スケール
	DirectX::XMFLOAT4 mMaterialDiffuse = { 1.0f,1.0f,1.0f,1.0f };//Material Color

	//モデル
	Model* pModel = {};

	Camera* pCamera = {};

	Animation* pAnimation = {};

	

private:

	//シェーダーに渡す行列の処理を行う関数
	void GenerateMatrix(ConstBuffer& cb);

public:

	Canvas2D();

	~Canvas2D();

	//オブジェクト設定
	void InitCanvas();

	//
	virtual void Update();

	//描画
	virtual void Draw();




};

