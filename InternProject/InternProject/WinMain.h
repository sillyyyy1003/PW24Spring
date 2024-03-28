#pragma once

#define WINDOW_CLASS L"InternProject"
#define WINDOW_TITLE L"24_Kaku"
#define WINDOW_WIDTH	(1920)
#define WINDOW_HEIGHT	(1080)

//関数定義
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL MyCreateWindow(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);