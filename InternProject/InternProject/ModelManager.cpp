#include "ModelManager.h"
#include "WaveFrontReader.h"
#include "WICTextureLoader.h"
#include "Model.h"

ModelManager::ModelManager()
{ 
    /*
    プラスα：もっとやりやすい読み込み方法をかんがえよう
    */
    test = Model::LoadTexture(L"Assets/Img/ASCIILib.png");
    testModel = Model::Create3DModel(L"Assets/Cube.obj");

}

ModelManager::~ModelManager()
{
    SAFE_RELEASE(test);
    
}

