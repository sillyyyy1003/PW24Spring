#pragma once
#include "Model.h"

namespace Anime
{
	class Animation;
}

class Camera;

//2D:Sprite
class Sprite2D
{
private:

	//PARAMETER
	DirectX::XMFLOAT3 mPos = {};//ワールド座標
	DirectX::XMFLOAT3 mRotation = {};//回転
	DirectX::XMFLOAT3 mScale = { 1.0f,1.0f,1.0f };//スケール
	DirectX::XMFLOAT4 mMaterialDiffuse = { 1.0f,1.0f,1.0f,1.0f };//Material Color

	Model* pModel = {};
	Anime::Animation* pAnimation = {};

	bool isLight = false;

private:

	//シェーダーに渡す行列の処理を行う関数
	void GenerateMatrix(ConstBuffer& cb);

public:

	Sprite2D();

	~Sprite2D();

	//位置の設定
	const DirectX::XMFLOAT3 GetPos() { return mPos; };
	void SetPos(float x, float y, float z);

	const DirectX::XMFLOAT3 GetRotate() { return mRotation; };
	void SetRotate(float x, float y, float z);

	//オブジェクト設定
	void InitCanvas(DirectX::XMFLOAT2 _size,DirectX::XMINT2 _split,ID3D11ShaderResourceView* _assets);

	virtual void Update();

	//描画
	virtual void Draw();

	//光
	bool GetisLight() { return isLight; };
	void SetisLight(bool isLight) { this->isLight = isLight; };

	//マテリアル色設定
	void SetMaterialDiffuse(Color sRGB);
	const DirectX::XMFLOAT4 GetMaterialDiffuse() { return mMaterialDiffuse; };

	

};

