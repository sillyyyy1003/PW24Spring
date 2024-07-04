#include "DirectX3D.h"

#include <atltypes.h>		// CRectを使うためのヘッダーファイル
#include "PixelShader.h"
#include "VertexShader.h"
#include "Model.h"


// ライブラリのリンク設定
#pragma comment (lib, "d3d11.lib")

static UINT g_ScreenWidth;      //画面の幅
static UINT g_ScreenHeight;     //画面の高さ  

void DirectX3D::DirectXInit(HWND hWnd)
{
    //メモリ確保
    pD3D = (D3D_DATA*)malloc(sizeof(D3D_DATA));
    ::ZeroMemory(pD3D, sizeof(D3D_DATA));

    //デバイス作成関数を呼び出す
    CreateDevice(hWnd);

    //深度バッファ作成関数を呼び出す
    CreateDepthStencil();

    //レンダーターゲット作成関数を呼び出す
    CreateRenderTarget();

    //シェーダー作成関数を呼び出す
    CreateShader();

    //ビューポート設定関数を呼び出す
    SetViewPort();

    //サンプラー作成関数を呼び出す
    CreateSampler();

    //定数バッファ作成関数を呼び出す
    CreateBuffer();

    //ブレンドステート作成関数を呼び出す
    CreateBlendState();
}

BOOL DirectX3D::CreateDevice(HWND hWnd)
{
    HRESULT  hr;
    UINT flags = 0;


    //ウインドウのクライアント領域（実際に描画できる範囲）のサイズを取得
    ::CRect rect;
    ::GetClientRect(hWnd, &rect);
    g_ScreenWidth = rect.Width();
    g_ScreenHeight = rect.Height();

    D3D_FEATURE_LEVEL pLevels[] = { D3D_FEATURE_LEVEL_11_0 };
    D3D_FEATURE_LEVEL level;


    DXGI_SWAP_CHAIN_DESC scDesc;
    ZeroMemory(&scDesc, sizeof(scDesc));

    scDesc.BufferCount = 1;
    scDesc.BufferDesc.Width = rect.Width();
    scDesc.BufferDesc.Height = rect.Height();
    scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scDesc.OutputWindow = hWnd;
    scDesc.SampleDesc.Count = 1;
    scDesc.SampleDesc.Quality = 0;
    scDesc.Windowed = TRUE;

    // デバイスとスワップチェインを同時に作成する関数の呼び出し
    hr = D3D11CreateDeviceAndSwapChain(NULL,
        D3D_DRIVER_TYPE_HARDWARE,
        NULL,
        flags,
        pLevels,
        1,
        D3D11_SDK_VERSION,
        &scDesc,
        &(pD3D->SwapChain),
        &(pD3D->Device),
        &level,
        &(pD3D->Context));

    if (FAILED(hr)) // 上の関数呼び出しが失敗してないかifでチェック
    {
        return FALSE;
        //エラー表示
        MessageBoxA(NULL, "デバイス作成失敗", "エラー", MB_OK | MB_ICONERROR);
    }
}

BOOL DirectX3D::CreateRenderTarget(void)
{
    HRESULT hr;
    ID3D11Texture2D* pBackBuffer;

    //バッファを取得
    hr = pD3D->SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);


    if (FAILED(hr))
    {
        //取得失敗した場合
        return FALSE;
        //エラー表示
        MessageBoxA(NULL, "バッファ取得失敗", "エラー", MB_OK | MB_ICONERROR);
    }
    else
    {
        // レンダーターゲットを作成する関数を呼び出す
        hr = pD3D->Device->CreateRenderTargetView(pBackBuffer, NULL, &pD3D->RenderTarget);
        pBackBuffer->Release();

        if (FAILED(hr)) {
            return FALSE;
            //エラー表示
            MessageBoxA(NULL, "レンダーターゲット作成失敗", "エラー", MB_OK | MB_ICONERROR);
        }
    }

}

BOOL DirectX3D::CreateDepthStencil(void)
{
    HRESULT hr;

    // 深度ステンシルバッファを作成
    // ※深度バッファ（Zバッファ）→奥行を判定して前後関係を正しく描画できる
    D3D11_TEXTURE2D_DESC txDesc;
    ZeroMemory(&txDesc, sizeof(txDesc));
    txDesc.Width = g_ScreenWidth;
    txDesc.Height = g_ScreenHeight;
    txDesc.MipLevels = 1;
    txDesc.ArraySize = 1;
    txDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    txDesc.SampleDesc.Count = 1;
    txDesc.SampleDesc.Quality = 0;
    txDesc.Usage = D3D11_USAGE_DEFAULT;
    txDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    txDesc.CPUAccessFlags = 0;
    txDesc.MiscFlags = 0;
    hr = pD3D->Device->CreateTexture2D(&txDesc, NULL, &(pD3D->DepthStencilTexture));

    if (FAILED(hr))
    {
        //エラー表示
        return FALSE;
        MessageBoxA(NULL, "CreateTexture2d Fail", "エラー", MB_OK | MB_ICONERROR);
    }
    else
    {
        D3D11_DEPTH_STENCIL_VIEW_DESC dsDesc;
        ZeroMemory(&dsDesc, sizeof(dsDesc));
        dsDesc.Format = txDesc.Format;
        dsDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
        dsDesc.Texture2D.MipSlice = 0;
        hr = pD3D->Device->CreateDepthStencilView(pD3D->DepthStencilTexture, &dsDesc, &pD3D->DepthStencilView);
        if (FAILED(hr))
        {
            return FALSE;
            //エラー表示
            MessageBoxA(NULL, "深度ステンシルバッファ作成失敗", "エラー", MB_OK | MB_ICONERROR);
        }
    }
}

BOOL DirectX3D::CreateShader(void)
{
    HRESULT hr;
    //頂点シェーダー作成
    hr = pD3D->Device->CreateVertexShader(&g_vs_main, sizeof(g_vs_main), NULL, &(pD3D->VertexShader));
    if (FAILED(hr))
        return FALSE;

    hr = pD3D->Device->CreatePixelShader(&g_ps_main, sizeof(g_ps_main), NULL, &(pD3D->PixelShader));
    if (FAILED(hr))
        return FALSE;


    D3D11_INPUT_ELEMENT_DESC vertexDesc[]
    {
        //POSITION
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },

        // UV TEXTURE
       { "TEX",    0, DXGI_FORMAT_R32G32_FLOAT, 0,  D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },

       // NORMALS
	 { "NORMAL",    0, DXGI_FORMAT_R32G32B32_FLOAT, 0,D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },

    };

    //インプットレイアウト作成
    hr = pD3D->Device->CreateInputLayout(vertexDesc, ARRAYSIZE(vertexDesc), g_vs_main, sizeof(g_vs_main), &(pD3D->InputLayout));
    if (FAILED(hr))
        return FALSE;
}

void DirectX3D::SetViewPort(void)
{
    //画面分割などに使う、描画領域の指定のこと
    pD3D->Viewport.TopLeftX = 0;
    pD3D->Viewport.TopLeftY = 0;
    pD3D->Viewport.Width = (float)g_ScreenWidth;
    pD3D->Viewport.Height = (float)g_ScreenHeight;
    pD3D->Viewport.MinDepth = 0.0f;
    pD3D->Viewport.MaxDepth = 1.0f;
}

BOOL DirectX3D::CreateSampler(void)
{
    //テクスチャ拡大縮小時のアルゴリズム
    HRESULT hr;

    D3D11_SAMPLER_DESC smpDesc;

    ::ZeroMemory(&smpDesc, sizeof(D3D11_SAMPLER_DESC));
    // 適用されるフィルター（アルゴリズム）の種類
    smpDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
    smpDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
    smpDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
    smpDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
    hr = pD3D->Device->CreateSamplerState(&smpDesc, &(pD3D->Sampler));
    if (FAILED(hr)) {
        return FALSE;
        //エラー表示
        MessageBoxA(NULL, "サンプラー作成失敗", "エラー", MB_OK | MB_ICONERROR);
    }
}

BOOL DirectX3D::CreateBuffer(void)
{
    HRESULT hr;

    D3D11_BUFFER_DESC cbDesc;
    cbDesc.ByteWidth = sizeof(ConstBuffer);// 今から作る定数バッファのサイズ
    cbDesc.Usage = D3D11_USAGE_DEFAULT;
    cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;// 定数バッファ作成を指定
    cbDesc.CPUAccessFlags = 0;
    cbDesc.MiscFlags = 0;
    cbDesc.StructureByteStride = 0;

    hr = pD3D->Device->CreateBuffer(&cbDesc, NULL, &ConstantBuffer);

    if (FAILED(hr)) {
        return FALSE;
        //エラー表示
        MessageBoxA(NULL, "定数バッファ作成失敗", "エラー", MB_OK | MB_ICONERROR);
    }


}

BOOL DirectX3D::CreateBlendState(void)
{
    HRESULT hr;
    // →透過処理や加算合成を可能にする色の合成方法
    //加算合成→エフェクトなどに使用する色が明るくなる合成方法
    D3D11_BLEND_DESC BlendState;
    ZeroMemory(&BlendState, sizeof(D3D11_BLEND_DESC));
    BlendState.AlphaToCoverageEnable = FALSE;
    BlendState.IndependentBlendEnable = FALSE;
    BlendState.RenderTarget[0].BlendEnable = TRUE;
    BlendState.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
    BlendState.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;//背景色にかけ合わせる係数(透過)
    BlendState.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
    BlendState.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
    BlendState.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
    BlendState.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
    BlendState.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

    //透過処理の設定を作る
    hr = pD3D->Device->CreateBlendState(&BlendState, &(pD3D->BlendAlpha));
    if (FAILED(hr)) {
        return FALSE;
        //エラー表示
        MessageBoxA(NULL, "BlendStateAlpha Failed", "エラー", MB_OK | MB_ICONERROR);
    }


    //加算合成の設定を作る
    BlendState.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;//背景色にかけあわせる係数(加算)
    hr = pD3D->Device->CreateBlendState(&BlendState, &(pD3D->BlendAdd));
    if (FAILED(hr)) {
        return FALSE;
        //エラー表示
        MessageBoxA(NULL, "BlendStateAddictive Failed", "エラー", MB_OK | MB_ICONERROR);
    }

    //乗算合成の設定を作る
    BlendState.RenderTarget[0].SrcBlend = D3D11_BLEND_DEST_COLOR;
    BlendState.RenderTarget[0].DestBlend = D3D11_BLEND_ZERO;
    BlendState.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
    hr = pD3D->Device->CreateBlendState(&BlendState, &(pD3D->BlendMultiply));
    if (FAILED(hr)) {
        return FALSE;
        //エラー表示
        MessageBoxA(NULL, "BlendStateAddictive Failed", "エラー", MB_OK | MB_ICONERROR);
    }

    //ブレンドステートの設定
    pD3D->Context->OMSetBlendState(pD3D->BlendAlpha, NULL, 0xffffffff);
}

void DirectX3D::ClearScreen(void)
{
    // 画面塗りつぶし色
    float clearColor[4] = { 0.0f,0.0f, 0.0f, 1.0f }; //red,green,blue,alpha

    // 描画先のキャンバスと使用する深度バッファを指定する
    pD3D->Context->OMSetRenderTargets(1, &pD3D->RenderTarget, pD3D->DepthStencilView);
    // 描画先キャンバスを塗りつぶす
    pD3D->Context->ClearRenderTargetView(pD3D->RenderTarget, clearColor);
    // 深度バッファをリセットする
    pD3D->Context->ClearDepthStencilView(pD3D->DepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

    UINT strides = sizeof(Vertex3D);
    UINT offsets = 0;
    pD3D->Context->IASetInputLayout(pD3D->InputLayout);

    // マテリアル色を定数バッファにセット
    pD3D->Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    pD3D->Context->VSSetShader(pD3D->VertexShader, NULL, 0);
    pD3D->Context->RSSetViewports(1, &pD3D->Viewport);
    pD3D->Context->PSSetShader(pD3D->PixelShader, NULL, 0);

    // ピクセルシェーダーにサンプラーを渡す
    pD3D->Context->PSSetSamplers(0, 1, &pD3D->Sampler);
    // 定数バッファを頂点シェーダーにセットする
    pD3D->Context->VSSetConstantBuffers(0, 1, &ConstantBuffer);
    //定数バッファをピクセルシェーダーににセットする
    pD3D->Context->PSSetConstantBuffers(0, 1, &ConstantBuffer);
}

void DirectX3D::DirectXRelease(void)
{
    //POINTERメモリを解放
    SAFE_RELEASE(pD3D->Device);
    SAFE_RELEASE(pD3D->Context);
    SAFE_RELEASE(pD3D->SwapChain);
    SAFE_RELEASE(pD3D->RenderTarget);
    SAFE_RELEASE(pD3D->DepthStencilView);
    SAFE_RELEASE(pD3D->DepthStencilTexture);
    SAFE_RELEASE(pD3D->InputLayout);
    SAFE_RELEASE(pD3D->VertexShader);
    SAFE_RELEASE(pD3D->PixelShader);
    SAFE_RELEASE(pD3D->BlendAlpha);
    SAFE_RELEASE(pD3D->BlendAdd);
    SAFE_RELEASE(pD3D->BlendMultiply);
    SAFE_RELEASE(pD3D->Sampler);

    //malloc関数で確保したメモリを解放
    if (pD3D != NULL)
    {
        free(pD3D); //mallocで確保したメモリを解放する関数
        pD3D = NULL;
    }
}

void DirectX3D::SetBlendState(ID3D11BlendState* _blendState)
{
    pD3D->Context->OMSetBlendState(_blendState, NULL, 0xffffffff);
}
