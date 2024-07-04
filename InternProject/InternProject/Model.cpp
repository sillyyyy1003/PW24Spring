// ReSharper disable All
#include "Model.h"
#include <codecvt>
#include "DebugLog.h"
#include "DirectX3D.h"
#include "WaveFrontReader.h"
#include "WICTextureLoader.h"


Model::Model()
{
}

Model::~Model()
{
    /*SAFE_RELEASE(model.vertexBuffer);
    SAFE_RELEASE(model.texture);
    SAFE_RELEASE(model.indexBuffer);*/

}

ModelData Model::Create2DModel(DirectX::XMFLOAT2 _size, DirectX::XMINT2 split, ModelSet::VerticalAlign _align)
{
    float left, right, top, bot, z = 0.0f;

    left = -_size.x / 2.0f * SCREEN_PARA;
    right = _size.x / 2.0f * SCREEN_PARA;
    switch (_align)
    {
    case ModelSet::TOP:
        bot = -_size.y * SCREEN_PARA;
        top = 0;
        break;
    case ModelSet::MIDDLE:
        top = (_size.y / 2.0f) * SCREEN_PARA;
        bot = -(_size.y / 2.0f) * SCREEN_PARA;
        break;
    case ModelSet::BOTTOM:
        bot = 0;
        top = (_size.y) * SCREEN_PARA;
        break;
    default:
        break;
    }

    const float u = 1.0f / split.x;
    const float v = 1.0f / split.y;

    Vertex3D vertexList[] = {

        {{left,top,0.0f},   {0.0f,0.0f}},
        {{right,bot,0.0f},  {u, v} },
        {{left,bot,0.0f},   {0.0f,v}},

        {{left,top,0.0f},   {0.0f,0.0f}},
        {{right,top,0.0f},  {u,0.0f}},
        {{right,bot,0.0f},  {u,v}},

    };


    D3D11_BUFFER_DESC bufferDesc;
    bufferDesc.ByteWidth = sizeof(vertexList);
    bufferDesc.Usage = D3D11_USAGE_DEFAULT;
    bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bufferDesc.CPUAccessFlags = 0;
    bufferDesc.MiscFlags = 0;
    bufferDesc.StructureByteStride = 0;

    D3D11_SUBRESOURCE_DATA subResourceData;
    subResourceData.pSysMem = vertexList;
    subResourceData.SysMemPitch = 0;
    subResourceData.SysMemSlicePitch = 0;

    HRESULT hr;
    ModelData model = {};
    hr = DirectX3D::Get()->GetD3D_Device()->CreateBuffer(&bufferDesc, &subResourceData, &(model.vertexBuffer));

    if (FAILED(hr)) {
        throw FALSE;
        MessageBoxA(NULL, "Create vertexBuffer Failed!", "ERROR!", MB_OK | MB_ICONERROR);
    }

    WORD indices[] = { 0, 1, 2, 3, 4, 5 };
    D3D11_BUFFER_DESC ibDesc;
    ibDesc.ByteWidth = sizeof(indices);
    ibDesc.Usage = D3D11_USAGE_DEFAULT;
    ibDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    ibDesc.CPUAccessFlags = 0;
    ibDesc.MiscFlags = 0;
    ibDesc.StructureByteStride = 0;

    D3D11_SUBRESOURCE_DATA irData;
    irData.pSysMem = indices;
    irData.SysMemPitch = 0;
    irData.SysMemSlicePitch = 0;

    hr = DirectX3D::Get()->GetD3D_Device()->CreateBuffer(&ibDesc, &irData, &model.indexBuffer);
    if (FAILED(hr)) {
        throw FALSE;
        MessageBoxA(NULL, "Create indexBuffer Failed!", "ERROR!", MB_OK | MB_ICONERROR);
    }

    model.indexNum = sizeof(indices) / sizeof(indices[0]);
    return model;
}

ModelData Model::Create3DModel(const wchar_t* fileName)
{
    WaveFrontReader<uint16_t> reader;
    HRESULT hr;
    hr = reader.Load(fileName, true);

    
    //wchar->string
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::string nameStr = converter.to_bytes(fileName);
    std::string outStr = "Failed To Read";
    outStr = outStr + nameStr;

    if (FAILED(hr))
    {
        DebugLog::Log(outStr);
        return ModelData();
    }

    const int numVertex = reader.vertices.size();
    Vertex3D* vertexList;
    vertexList = new Vertex3D[numVertex];

    for (int i = 0; i < numVertex; i++) {
        vertexList[i].position = reader.vertices[i].position;
        vertexList[i].uv = reader.vertices[i].textureCoordinate;
        vertexList[i].normal = reader.vertices[i].normal;

        vertexList[i].uv.y = 1.0f - vertexList[i].uv.y;

        vertexList[i].normal.x *= -1;
        vertexList[i].normal.y *= -1;
        vertexList[i].normal.z *= -1;
    }

    D3D11_BUFFER_DESC bufferDesc;
    bufferDesc.ByteWidth = sizeof(Vertex3D) * numVertex;
    bufferDesc.Usage = D3D11_USAGE_DEFAULT;
    bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bufferDesc.CPUAccessFlags = 0;
    bufferDesc.MiscFlags = 0;
    bufferDesc.StructureByteStride = 0;

    D3D11_SUBRESOURCE_DATA subResourceData;
    subResourceData.pSysMem = vertexList;
    subResourceData.SysMemPitch = 0;
    subResourceData.SysMemSlicePitch = 0;

    ModelData model = {};
    DirectX3D::Get()->GetD3D_Device()->CreateBuffer(&bufferDesc, &subResourceData, &model.vertexBuffer);

    D3D11_BUFFER_DESC ibDesc;
    ibDesc.ByteWidth = (UINT)(sizeof(WORD) * reader.indices.size());
    ibDesc.Usage = D3D11_USAGE_DEFAULT;
    ibDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    ibDesc.CPUAccessFlags = 0;
    ibDesc.MiscFlags = 0;
    ibDesc.StructureByteStride = 0;

    D3D11_SUBRESOURCE_DATA irData;
    irData.pSysMem = reader.indices.data();
    irData.SysMemPitch = 0;
    irData.SysMemSlicePitch = 0;

    hr = DirectX3D::Get()->GetD3D_Device()->CreateBuffer(&ibDesc, &irData, &model.indexBuffer);

    model.indexNum = reader.indices.size();

    //release the pointer used
    delete[] vertexList;

    wchar_t textureName[512];
    wcscpy_s(textureName, L"Assets/");
    wcscat_s(textureName, reader.materials[1].strTexture);
    model.texture = LoadTexture(textureName);

    return model;
}

ID3D11ShaderResourceView* Model::LoadTexture(const wchar_t* _fileName)
{
    ID3D11ShaderResourceView* texture;
    HRESULT hr;

    hr = DirectX::CreateWICTextureFromFile(DirectX3D::Get()->GetD3D_Device(), _fileName, NULL, &texture);

    //wchar->string
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::string nameStr = converter.to_bytes(_fileName);
    std::string outStr = "Failed To Read";
    outStr = outStr + nameStr;

    if (FAILED(hr))
    {
		DebugLog::Log(outStr);
        return nullptr;
    }

    return texture;
}


void Model::SetTexture(ID3D11ShaderResourceView* texture)
{
    model.texture = texture;
}
