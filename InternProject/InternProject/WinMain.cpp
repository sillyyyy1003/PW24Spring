#include "framework.h"
#include "WinMain.h"
#include "DirectX3D.h"
#include "Game.h"
#include "KInput.h"

#define MAX_LOADSTRING 128

//グローバル変数
HINSTANCE hInstance;
HWND hWnd;
Game* gGame;
Time gTime;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	
	MyRegisterClass(hInstance);

	// 执行应用程序初始化:
	if (!MyCreateWindow(hInstance, nCmdShow))
	{
		return FALSE;
	}

	//FPS COUNTER(For Debug)
	int fpsCounter = 0;
	long long oldTick = GetTickCount64();//現在時間を保存
	long long nowTick = oldTick; // 現在時間取得用

	//Init DirectX3D 
	DirectX3D::Get()->DirectXInit(hWnd);

	//Init Game
	gGame = Game::Get();
	gGame->InitGame();

	//Init Timer
	gTime.InitTime(60);//Set fps rate as 60

	KInput::Get()->Initialize(hWnd, hInstance);

	MSG msg;

	for (;;) {
		BOOL isAnyMessage = PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
	
		if (isAnyMessage)// 何かメッセージがあるか判定
		{
			DispatchMessage(&msg);
			if (msg.message == WM_QUIT) {
				break;
			}
		}
		else
		{
			gTime.GetTimeCount();

			if (gTime.isCountRight()) {

				KInput::Get()->Update();

				//==============Update==============//
				gGame->Update();
				//==============Update==============//


				//==============描画==============//
				DirectX3D::Get()->ClearScreen();
				//To Do:
				//ここに描画内容を
				gGame->Draw();

				DirectX3D::Get()->GetD3D_Data()->SwapChain->Present(0, 0);
				//==============描画==============//


				/*
				* fpsCounter++; // ゲームループ実行回数をカウント＋１
				
				
			}
			//現在時間取得
			nowTick = GetTickCount64();


			//１秒経過したか？
			if (nowTick >= oldTick + 1000)
			{
				char str[32];
				wsprintfA(str, "FPS=%d", fpsCounter);
				SetWindowTextA(hWnd, str);
				fpsCounter = 0;
				oldTick = nowTick;
				*/
			}
				
		}

	}


	DirectX3D::Get()->DirectXRelease();

	//----------------------------//
	// ウィンドウズの終了処理
	//----------------------------//
	UnregisterClass(WINDOW_CLASS, hInstance);
	return (int)msg.wParam;


}

ATOM MyRegisterClass(HINSTANCE hInstance) {
	
	WNDCLASSEX wc;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_CLASSDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	//ウインドウクラスの名前を変更
	wc.lpszClassName = WINDOW_CLASS;
	wc.hIconSm = NULL;

	return RegisterClassEx(&wc);
}

BOOL MyCreateWindow(HINSTANCE _hInstance, int nCmdShow)
{
    hInstance = _hInstance; // 将实例句柄存储在全局变量中

	//スクリーンサイズを郭とク
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    //UNICODE
	hWnd = CreateWindowEx(0,// 拡張ウィンドウスタイル
		WINDOW_CLASS,// ウィンドウクラスの名前
		WINDOW_TITLE,// ウィンドウの名前
		WS_OVERLAPPEDWINDOW,// ウィンドウスタイル WS_POPUPWINDOW(No Frame&Title)
		CW_USEDEFAULT,// ウィンドウの左上Ｘ座標
		CW_USEDEFAULT,// ウィンドウの左上Ｙ座標 
		WINDOW_WIDTH,// ウィンドウの幅
		WINDOW_HEIGHT,// ウィンドウの高さ
		NULL,// 親ウィンドウのハンドル
		NULL,// メニューハンドルまたは子ウィンドウID
		hInstance,// インスタンスハンドル
		NULL);// ウィンドウ作成データ

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:// ウィンドウ破棄のメッセージ
		PostQuitMessage(0);// “WM_QUIT”メッセージを送る　→　アプリ終了
		break;

	case WM_CLOSE:  // xボタンが押されたら
		DestroyWindow(hWnd);  // “WM_DESTROY”メッセージを送る
		break;

		// キーが押されたイベント
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) { DestroyWindow(hWnd); }
		break;

		// キーが離されたイベント
	case WM_KEYUP:
		break;

	default:
		// 上のcase以外の場合の処理を実行
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
		break;
	}

	return 0;
}
