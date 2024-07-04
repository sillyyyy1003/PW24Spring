#pragma once
#include <unordered_map>

namespace Layer {
	enum LayerName
	{
		FADE,			//FadeIn/Out用　一番手前
		FRONT_UI,		//前景UI
		MASK_FRONT,		//前景に置いてあるmask
		MASK_BACK,		//背景に置いてあるmask
		UI_WORD,		//表示する文字
		UI_CURSOR,		//手前のカーソル
		UI_BOX,			//messageBox
		UI_PANEL,		//UIの背景
		BACKGROUND,		//背景
	};
}

class LayerManager
{
private:
	
	std::unordered_map<Layer::LayerName, float> Layers;

public:
	/// @brief
	///	レイヤーデータの初期化
	LayerManager();

	/// @brief 
	/// @param _name レイヤーの名前
	/// @return 位置を設定
	float SetLayers(Layer::LayerName _name);


};

