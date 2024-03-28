#include "Game.h"
#include "Camera.h"
#include "AssetManager.h"
#include "Canvas2D.h"

void Game::InitGame()
{
	//Init
	mAssetManager = new AssetManager();

	//Init Camera
	mCamera2D = new Camera();
	mCamera3D = new Camera();
	//Set Camera
	mCamera2D->SetProjMode(Camera::_2D);
	mCamera3D->SetProjMode(Camera::_3D);

	mCamera2D->SetCamPos({ 0,0,-1 });
	mCamera2D->SetFocus({ 0,0,1 });
	mCamera2D->Update();//Generate MatrixView

	//Set Main Camera
	SetMainCamera(mCamera3D);

	//Init GameObject
	mTest = new Canvas2D();
	mTest->InitCanvas(DirectX::XMFLOAT2(1, 1.5), DirectX::XMINT2(12, 8),mAssetManager->test);
	mTest->SetPos(DirectX::XMFLOAT3(0.f, 0.f, 0.2f));
}

void Game::Update()
{
	mTest->Update();
	
}

void Game::Draw()
{
	mTest->Draw();
}
