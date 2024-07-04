#include "LayerManager.h"

LayerManager::LayerManager()
{
	Layers[Layer::FADE] = 0.1f;
	Layers[Layer::FRONT_UI] = 0.2f;
	Layers[Layer::MASK_FRONT] = 0.3f;
	Layers[Layer::UI_WORD] = 0.4f;
	Layers[Layer::UI_CURSOR] = 0.4f;
	Layers[Layer::UI_BOX] = 0.5f;
	Layers[Layer::UI_PANEL] = 0.6f;
	Layers[Layer::MASK_BACK] = 0.8f;
	Layers[Layer::BACKGROUND] = 0.9f;
}

float LayerManager::SetLayers(Layer::LayerName _name)
{
	float num = 0.f;

	//レイヤーの名前を探す
	if(Layers.find(_name)!=Layers.end())
	{
		num = Layers[_name];

	}
	//z軸の位置を設定する
	return num;

}
