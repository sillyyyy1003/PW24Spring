#include "GameFrame.h"

extern Time gTime;

Game::~Game()
{
	delete mAssetManager;
	delete mCamera2D;
	delete mCamera3D;
	
	//delete mMainCamera; //リリースの必要がない

	delete mTestObj;
}

void Game::InitGame()
{
	//Init
	mAssetManager = new ModelManager();
	//mInput = KInput::Get();

	//Init Camera
	mCamera2D = new Camera();
	mCamera3D = new Camera();
	//Set Camera
	mCamera2D->SetProjMode(Camera::_2D);
	mCamera2D->SetCamPos({ 0,0,-1 });
	mCamera2D->SetFocus({ 0,0,1 });
	mCamera2D->Update();//Generate MatrixView

	mCamera3D->SetProjMode(Camera::_3D);
	mCamera3D->SetCamPos({ 0,2,-2 });
	mCamera3D->SetFocus({ 0,-1,1 });
	mCamera3D->Update();

	//Set Main Camera
	SetMainCamera(mCamera3D);

	//Init GameObject
	mTestObj = new Object;
	mTestObj->SetModel(mAssetManager->testModel);
	mTestObj->mLightDir = mCamera3D->GetCamPos();

}

void Game::Update()
{
	if (KInput::Get()->GetKeyPress(DIK_UPARROW))
	{
		DirectX::XMFLOAT3 scale = mTestObj->GetScale();
		scale.x += 0.01f;
		scale.y += 0.01f;
		scale.z += 0.01f;
		mTestObj->SetScale(scale);
	}

	if (KInput::Get()->GetKeyPress(DIK_DOWNARROW))
	{
		DirectX::XMFLOAT3 scale = mTestObj->GetScale();
		scale.x -= 0.01f;
		scale.y -= 0.01f;
		scale.z -= 0.01f;
		mTestObj->SetScale(scale);
	}


	if (KInput::Get()->GetKeyPress(DIK_LEFTARROW))
	{
		DirectX::XMFLOAT3 rotate = mTestObj->GetRotate();
		rotate.y -= 10.f;
		mTestObj->SetRotate(rotate);
	}

	if (KInput::Get()->GetKeyPress(DIK_RIGHTARROW))
	{
		DirectX::XMFLOAT3 rotate = mTestObj->GetRotate();
		rotate.y += 10.f;
		mTestObj->SetRotate(rotate);
	}



	mTestObj->Update();
}

void Game::Draw()
{
	DirectX3D::Get()->ClearScreen();
	//ここに描画関数
	
	mTestObj->Draw();

	//
	DirectX3D::Get()->GetD3D_Data()->SwapChain->Present(0, 0);
}
