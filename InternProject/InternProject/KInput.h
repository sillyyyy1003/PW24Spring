#pragma once
#define DIRECTINPUT_VERSION 0x0800
#include<dinput.h>
#include<string>


//Keyboard Input
class KInput
{
private:

	IDirectInput8* mDInput = nullptr;
	IDirectInputDevice8* mDevKeyboad = nullptr;
	IDirectInputDevice8* mDevMouse = nullptr;

	unsigned char mKeyBuffer[256] = {};
	unsigned char mOldKeyBuffer[256] = {};

	DIMOUSESTATE2 mMouseState = {};
	DIMOUSESTATE2 mOldMouseState = {};

	float value = 0.f;//GetAxis用出力値

	KInput() {};

	~KInput();
public:
	//Getter
	static KInput* Get();

	//初期化
	void Initialize(HWND hWnd, HINSTANCE hInstance);

	//
	void Update();

	//while the key is pressed
	bool GetKeyPress(int key);

	//if the key is pressed (once at a time)
	bool GetKeyTrigger(int key);

	//if the mousebutton is presed
	bool GetMousePress(int key);

	//if the key is released
	bool GetKeyRelease(int key);

	//Get Mousemove Position
	POINT GetMouseMove();

	/// <summary>
	/// Returns the value of the virtual axis identified by axisName
	/// </summary>
	/// <returns>The Horizontal and Vertical ranges change from 0 to +1 or -1 with increase/decrease in 0.05f steps</returns>
	float GetAxis(std::string _axisName);

	/// <summary>
	/// Returns the value of the virtual axis identified by axisName
	/// </summary>
	/// <returns>The Horizontal and Vertical change to 1/-1 immediately</returns>
	float GetAxisRaw(std::string _axisName);

};

