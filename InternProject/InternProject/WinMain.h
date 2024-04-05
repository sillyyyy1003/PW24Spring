#pragma once

#define WINDOW_CLASS L"InternProject"
#define WINDOW_TITLE L"24_Kaku"
#define WINDOW_WIDTH	(1920)
#define WINDOW_HEIGHT	(1080)

//関数定義
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL MyCreateWindow(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

struct Time {

private:
	LARGE_INTEGER liWork;
	long long frequency;	//refresh frequency
	long long countPerFrame;	//count per frame


	long long oldCount;
	long long nowCount;

public:
	float deltaTime;
	int frameRate = 60;

public:

	void InitTime(int _frameRate) {
		QueryPerformanceFrequency(&liWork);
		frequency = liWork.QuadPart;//Get machine refresh frequency
 
		frameRate = _frameRate;
		countPerFrame = frequency / frameRate;
		deltaTime = 1.0f / frameRate;

		oldCount = liWork.QuadPart;
		nowCount = oldCount;
	}

	//check if there is Enough Time(）
	bool isCountRight() {
		if (nowCount >= oldCount + countPerFrame) {
			oldCount = nowCount;
			return true;
		}
		else {
			return false;
		}
	}

	//Get Time per Loop
	void GetTimeCount() {
		QueryPerformanceCounter(&liWork);//Get time
		nowCount = liWork.QuadPart;//Set time got to nowCount
	}

};

extern Time gTime;