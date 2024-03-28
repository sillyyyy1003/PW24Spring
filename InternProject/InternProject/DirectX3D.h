#pragma once
#include <d3d11.h>
#include <DirectXMath.h>


//マクロ解放
#define SAFE_RELEASE(p)      { if( NULL != p ) { p->Release(); p = NULL; } }

//縦横比
#define RATIO_H		(9.0f)		//アスペクト比(縦)
#define RATIO_W		(16.0f)		//アスペクト比(横)

//Direct3D関連変数をまとめる構造体
struct D3D_DATA
{
	ID3D11Device* Device;						//デバイス(设备)
	ID3D11DeviceContext* Context;					//コンテキスト(设备上下文)
	IDXGISwapChain* SwapChain;				//スワップチェイン(交换链)
	ID3D11RenderTargetView* RenderTarget;		//レンダーターゲット(RenderTargetView)
	ID3D11DepthStencilView* DepthStencilView;	//深度バッファ(深度缓冲)
	ID3D11Texture2D* DepthStencilTexture;	//深度バッファ用テキスチャー
	ID3D11InputLayout* InputLayout;				//インプットレイアウト(顶点数据馈送到图形管道)
	ID3D11VertexShader* VertexShader;				//頂点シェーダー(顶点着色器)
	ID3D11PixelShader* PixelShader;					//ピクセルシェーダー(像素着色器)
	D3D11_VIEWPORT			Viewport;						//ビューポート(视口)
	ID3D11BlendState* BlendAlpha;					// アルファブレンディング用ブレンドステート(Alpha混合 透明效果)
	ID3D11BlendState* BlendAdd;					//加算合成用ブレンドステート(加法混合 明亮效果)
	ID3D11BlendState* BlendMultiply;				//乗算合成用ブレンドステート(色彩增值)
	ID3D11SamplerState* Sampler;						//ポイント補完用サンプラー(采样器)
};


class DirectX3D
{
private:

	DirectX3D() {};

	D3D_DATA* pD3D = nullptr;

	ID3D11Buffer* ConstantBuffer;



public:

	static DirectX3D* Get() { static DirectX3D instance; return &instance; };
	//pD3Dを返す
	D3D_DATA* GetD3D_Data() { return pD3D; };
	ID3D11Device* GetD3D_Device() { return pD3D->Device; };
	ID3D11DeviceContext* GetD3D_Context() { return pD3D->Context; };
	ID3D11Buffer* GetConstantBuffer() { return ConstantBuffer; };

	//DirectX初期化
	void DirectXInit(HWND hWnd);

	//Device&SwapChain作成
	BOOL CreateDevice(HWND hWnd);

	//レンダーターゲット作成
	BOOL CreateRenderTarget(void);

	//深度ステンシルバッファ作成
	BOOL CreateDepthStencil(void);

	//シェーダーオブジェクト作成
	BOOL CreateShader(void);

	//ビューポート作成
	void SetViewPort(void);

	//サンプラー作成
	BOOL CreateSampler(void);

	//定数バッファ作成
	BOOL CreateBuffer(void);

	//ブレンドステート作成
	BOOL CreateBlendState(void);

	//画面塗りつぶし設定
	void ClearScreen(void);

	//メモリ解放処理
	void DirectXRelease(void);

};

