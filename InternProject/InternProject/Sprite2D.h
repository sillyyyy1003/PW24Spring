#pragma once
#include "Animation.h"
#include "Model.h"

/// @brief 2Dオブジェクト基底
///	UI等に使われてる
class Sprite2D
{
public:
	//PARAMETER
	DirectX::XMFLOAT3 mPos = {};//ワールド座標
	DirectX::XMFLOAT3 mRotation = {};//回転
	DirectX::XMFLOAT3 mScale = { 1.0f,1.0f,1.0f };//スケール
	DirectX::XMFLOAT4 mMaterialDiffuse = { 1.0f,1.0f,1.0f,1.0f };//Material Color
protected:
	
	std::unique_ptr<Model> pModel;
	std::unique_ptr<Anime::Animation> pAnimation;

	bool isLight = true;


private:

	//シェーダーに渡す行列の処理を行う関数
	void GenerateMatrix(ConstBuffer& cb);

public:

	Sprite2D();

	virtual ~Sprite2D();

	//位置の設定
	const DirectX::XMFLOAT3 GetPos() { return mPos; };
	void SetPos(float x, float y, float z);
	

	const DirectX::XMFLOAT3 GetRotate() { return mRotation; };
	void SetRotate(float x, float y, float z);

	const DirectX::XMFLOAT3 GetScale() { return mScale; };


	/// @brief オブジェクト設定
	/// @param _size オブジェクトの大きさ
	/// @param _split 縦横分割
	/// @param _assets 図形
	/// @param _pattern アニメションパタン
	///	@param _align 縦方向の中心点
	void InitSprite(DirectX::XMFLOAT2 _size,DirectX::XMINT2 _split,ID3D11ShaderResourceView* _assets,Anime::AnimePattern _pattern, ModelSet::VerticalAlign _align);

	virtual void Update();

	//描画
	virtual void Draw();

	//光
	bool GetisLight() { return isLight; };
	void SetisLight(bool isLight) { this->isLight = isLight; };

	//マテリアル色設定
	void SetMaterialDiffuse(Color sRGB);

	Anime::Animation* GetAnimation(){ return pAnimation.get();};
	Model* GetModel() { return pModel.get(); };

};

