#pragma once
#include "DirectX3D.h"
#include "WaveFrontReader.h"

//Pictrue&Model 
class ModelManager
{
public:
    //2D
    ID3D11ShaderResourceView* test;

    //3D
    ModelData testModel;

public:

    ModelManager();

    ~ModelManager();

    void InitAsset();

};

