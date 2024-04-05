#include "ModelManager.h"
#include "WaveFrontReader.h"
#include "WICTextureLoader.h"

ModelManager::ModelManager()
{ 
    /*
    プラスα：もっとやりやすい読み込み方法をかんがえよう
    */
    test = LoadTexture(L"Assets/Img/ASCIILib.png");

}

ModelManager::~ModelManager()
{
    SAFE_RELEASE(test);
}

void ModelManager::InitAsset()
{
    //test = LoadTexture(L"Assets/Img/ASCIILib");
}

WaveFrontReader<uint16_t> ModelManager::Load3DModel(const wchar_t* fileName)
{
	WaveFrontReader<uint16_t> reader;
    HRESULT hr;
    hr = reader.Load(fileName, true);

    //読み込み失敗のファイル名変換
    char nameStr[128];
    char outStr[128];
    wsprintfA(outStr, "%sを読み込み失敗", nameStr);

    if (FAILED(hr))
    {
        MessageBoxA(NULL, outStr, "ERROR", MB_OK | MB_ICONERROR);
        return WaveFrontReader<uint16_t>();
    }
     
    return reader;
}

ID3D11ShaderResourceView* ModelManager::LoadTexture(const wchar_t* fileName)
{
    ID3D11ShaderResourceView* texture;
    HRESULT hr;

    hr = DirectX::CreateWICTextureFromFile(DirectX3D::Get()->GetD3D_Device(), fileName, NULL, &texture);

    char nameStr[256];
    char outStr[256];
    wsprintfA(outStr, "Failed to Read %s", nameStr);

    if (FAILED(hr)) {
        MessageBoxA(NULL, outStr, "ERROR", MB_OK | MB_ICONERROR);
        return nullptr;
    }

    return texture;
}
