#pragma once
#include "Sprite3D.h"

class Effect
{
private:
	//オブジェクトに追跡しますか？
	bool isTrace = false;

	//作動中かどうか？
	bool isActive = false;

public:
	std::unique_ptr<Sprite3D> mSprite = nullptr;

public:
	explicit Effect();
	~Effect();

	/// @brief エフェクトの初期化
	/// @param _size 
	/// @param _split 
	/// @param _assets 
	void InitEffect(DirectX::XMFLOAT2 _size, DirectX::XMINT2 _split, ID3D11ShaderResourceView* _assets);

	/// @brief 追跡機能を使う
	void Update();

	/// @brief 描画
	void Draw();

	/// @brief 描画と作動の切り替え
	/// @param isActive SetLoop·Active·Playing
	void SetActive(bool isActive);

	/// @brief エフェクトの速度設定
	/// @param speed 
	void SetSpeed(float speed) { mSprite->GetAnimation()->SetAnimeSpeed(speed); };

	void SetTrace(bool _isTrace) { this->isTrace = _isTrace; };
};

