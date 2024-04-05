#pragma once
#include "DirectX3D.h"
#include "WaveFrontReader.h"

//Pictrue&Model 
class ModelManager
{
public:

    ID3D11ShaderResourceView* test;

public:

    ModelManager();

    ~ModelManager();

    void InitAsset();

    WaveFrontReader<uint16_t> Load3DModel(const wchar_t* fileName);

    static ID3D11ShaderResourceView* LoadTexture(const wchar_t* fileName);

};

