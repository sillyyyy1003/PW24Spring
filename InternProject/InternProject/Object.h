#pragma once
#include "Model.h"
using namespace DirectX;


//3D用Obj 基底
class Object
{
private:

	DirectX::XMFLOAT3 mPos = { 0.f,0.f,0.f };//位置
	DirectX::XMFLOAT3 mRotation= { 0.f,0.f,0.f };//回転
	DirectX::XMFLOAT3 mScale = { 1.0f,1.0f,1.0f };//スケール
	DirectX::XMFLOAT3 mSpeed = { 0.f,0.f,0.f };//移動速度
	DirectX::XMFLOAT4 mMaterialDiffuse = { 1.0f,1.0f,1.0f,1.0f };//Material Color

	DirectX::XMFLOAT3 mForward = { 0.f,0.f,0.f };//移動用ベクトル

	Model mModel = {};
	bool isLight = true;

public:
	DirectX::XMFLOAT3 mLightDir = { 0.0,0.0,0.0f };
	DirectX::XMFLOAT4 mAmbientLight = { 0.1f, 0.1f, 0.1f, 0.0f };
	//float diffusePower;

public:
	
	Object();
	~Object();

	void SetModel(const ModelData& _model);	

	//位置
	void SetPos(float _x, float _y, float _z);
	DirectX::XMFLOAT3 GetPos() { return mPos; };

	void SetRotate(float _x, float _y, float _z);
	void SetRotate(DirectX::XMFLOAT3 _rotate) { mRotation = _rotate; };
	DirectX::XMFLOAT3 GetRotate() { return mRotation; };

	void SetScale(float _x, float _y, float _z);
	void SetScale(DirectX::XMFLOAT3 _scale) { mScale = _scale; };
	DirectX::XMFLOAT3 GetScale() { return mScale; };

	void SetSpeed(float _x, float _y, float _z);
	DirectX::XMFLOAT3 GetSpeed() { return mSpeed; };

	void SetLight(bool isLight) { this->isLight = isLight; };
	bool GetisLight() { return isLight; };

	//ゲームループ
	virtual void Update();

	//描画
	virtual void Draw();

private:
	DirectX::XMFLOAT3 GenerateRotate();
	void GenerateMatrix(ConstBuffer& cb);



};

