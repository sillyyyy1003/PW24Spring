#include "KInput.h"
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

KInput::~KInput()
{
	if (mDevMouse != nullptr)
	{
		mDevMouse->Release();
		mDevMouse = nullptr;
	}
	if (mDevKeyboad != nullptr)
	{
		mDevKeyboad->Release();
		mDevKeyboad = nullptr;
	}
	if (mDInput != nullptr)
	{
		mDInput->Release();
		mDInput = nullptr;
	}
}

KInput* KInput::Get()
{
	static KInput instance;
	return &instance;
}

void KInput::Initialize(HWND hWnd, HINSTANCE hInstance)
{
	HRESULT	hr;
	hr = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&mDInput, NULL);
	if (FAILED(hr)) {
		return;
	}

	mDInput->CreateDevice(GUID_SysKeyboard, &mDevKeyboad, NULL);
	if (FAILED(hr)) {
		return;
	}

	hr = mDevKeyboad->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr)) {
		return;
	}

	hr = mDevKeyboad->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(hr)) {
		return;
	}

	mDInput->CreateDevice(GUID_SysMouse, &mDevMouse, NULL);
	if (FAILED(hr)) {
		return;
	}

	hr = mDevMouse->SetDataFormat(&c_dfDIMouse2);
	if (FAILED(hr)) {
		return;
	}

	hr = mDevMouse->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(hr)) {
		return;
	}

	mDevKeyboad->Acquire();
	mDevMouse->Acquire();
}

void KInput::Update()
{
	memcpy_s(mOldKeyBuffer, sizeof(mOldKeyBuffer), mKeyBuffer, sizeof(mKeyBuffer));

	HRESULT hr;

	hr = mDevKeyboad->GetDeviceState(sizeof(mKeyBuffer), &mKeyBuffer);

	if (FAILED(hr))
	{
		mDevKeyboad->Acquire();
		mDevKeyboad->GetDeviceState(sizeof(mKeyBuffer), &mKeyBuffer);
	}

	mOldMouseState = mMouseState;

	hr = mDevMouse->GetDeviceState(sizeof(mMouseState), &mMouseState);

	if (FAILED(hr))
	{
		mDevMouse->Acquire();
		mDevMouse->GetDeviceState(sizeof(mMouseState), &mMouseState);
	}
}

bool KInput::GetKeyPress(int key)
{
	return (mKeyBuffer[key] & 0x80) != 0;
}

bool KInput::GetKeyTrigger(int key)
{
	if ((mOldKeyBuffer[key] & 0x80) == 0 && (mKeyBuffer[key] & 0x80) != 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool KInput::GetMousePress(int key)
{
	return (mMouseState.rgbButtons[key] & 0x80) != 0;
}

bool KInput::GetKeyRelease(int key)
{
	//if old frame is pressed & new frame is released
	if ((mOldKeyBuffer[key] & 0x80) !=0&&(mKeyBuffer[key] & 0x80) == 0) {
		return true;
	}
	else {
		return false;
	}
}


POINT KInput::GetMouseMove()
{
	POINT pt;
	pt.x = mMouseState.lX;
	pt.y = mMouseState.lY;

	return pt;
}


const float KInput::GetAxis(std::string _axisName)
{
	float step = 0.05f;//increase step


	if (_axisName == "Vertical")
	{
		//if released the key
		if (KInput::Get()->GetKeyRelease(DIK_UPARROW)|| KInput::Get()->GetKeyRelease(DIK_DOWNARROW))
		{
			value = 0;
		}

		//同時に押したら
		if (KInput::Get()->GetKeyPress(DIK_UPARROW) && KInput::Get()->GetKeyPress(DIK_DOWNARROW))
		{
			value = 0;
		}
		else if (KInput::Get()->GetKeyPress(DIK_UPARROW)) 
		{
			//make sure value>=0
			value = max(value, 0);
			value += step;
			//restrict value to(0,1)
			value = min(value, 1);

		}
		else if (KInput::Get()->GetKeyPress(DIK_DOWNARROW))
		{
			//make sure value<=0
			value = min(value, 0);
			value -= step;
			//restrict value to(-1,0)
			value = max(value, -1);
		}

	}
	else if (_axisName == "Horizontal")
	{
		//if released the key
		if (KInput::Get()->GetKeyRelease(DIK_LEFTARROW) || KInput::Get()->GetKeyRelease(DIK_RIGHTARROW))
		{
			value = 0;
		}
		//同時に押したら
		if (KInput::Get()->GetKeyPress(DIK_LEFTARROW) &&
			KInput::Get()->GetKeyPress(DIK_RIGHTARROW))
		{
			//reset value
			value = 0;
		}
		else if (KInput::Get()->GetKeyPress(DIK_LEFTARROW))
		{
			//make sure value<=0
			value = min(value, 0);
			value -= step;

			//restrict value to(-1,0)
			value = max(value, -1);


		}
		else if (KInput::Get()->GetKeyPress(DIK_RIGHTARROW))
		{
			//make sure value>=0
			value = max(value, 0);
			value += step;

			//restrict value to(0,1)
			value = min(value, 1);
		}
	}

	return value;
}



const float KInput::GetAxisRaw(std::string _axisName)
{
	if (_axisName == "Vertical")
	{
		//if released the key
		if (KInput::Get()->GetKeyRelease(DIK_UPARROW) || KInput::Get()->GetKeyRelease(DIK_DOWNARROW))
		{
			value = 0;
		}

		//同時に押したら
		if (KInput::Get()->GetKeyPress(DIK_UPARROW) && KInput::Get()->GetKeyPress(DIK_DOWNARROW))
		{
			value = 0;
		}
		else if (KInput::Get()->GetKeyPress(DIK_UPARROW))
		{
			value = 1;
		}
		else if (KInput::Get()->GetKeyPress(DIK_DOWNARROW))
		{
			value = -1;
		}


	}
	else if (_axisName == "Horizontal")
	{
		//if released the key
		if (KInput::Get()->GetKeyRelease(DIK_UPARROW) || KInput::Get()->GetKeyRelease(DIK_DOWNARROW))
		{
			value = 0;
		}

		//同時に押したら
		if (KInput::Get()->GetKeyPress(DIK_LEFTARROW) &&
			KInput::Get()->GetKeyPress(DIK_RIGHTARROW))
		{
			//reset value
			value = 0;

		}
		else if (KInput::Get()->GetKeyPress(DIK_LEFTARROW))
		{//return -1~0

			value = -1;

		}
		else if (KInput::Get()->GetKeyPress(DIK_RIGHTARROW))
		{
			value = 1;
		}

	}

	return value;
}
