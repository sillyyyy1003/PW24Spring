#include "Game.h"
#include "Camera.h"
#include "ModelManager.h"
#include "Canvas2D.h"
#include "KInput.h"
#include "Animation.h"
#include "WinMain.h"

extern Time gTime;

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
	mCamera3D->SetProjMode(Camera::_3D);
	mCamera2D->SetCamPos({ 0,0,-1 });
	mCamera2D->SetFocus({ 0,0,1 });
	mCamera2D->Update();//Generate MatrixView

	//Set Main Camera
	SetMainCamera(mCamera3D);

	//Init GameObject
	mTest = new Canvas2D();
	mTest->InitCanvas(DirectX::XMFLOAT2(1, 1.5), DirectX::XMINT2(12,8), mAssetManager->test);
	mTest->SetPos(0.f, 0.f, 0.1f);



}

void Game::Update()
{

	if (KInput::Get()->GetKeyTrigger(DIK_RIGHTARROW)) {
		int frameX = mTest->GetAnimation()->GetFrame().x;
		frameX++;
		frameX = min(frameX, 7);
		mTest->GetAnimation()->SetFrameX(frameX);
	}

	if (KInput::Get()->GetKeyTrigger(DIK_LEFTARROW)) {
		int frameX = mTest->GetAnimation()->GetFrame().x;
		frameX--;
		frameX = max(frameX, 0);
		mTest->GetAnimation()->SetFrameX(frameX);
	}

	float h = KInput::Get()->GetAxisRaw("Vertical") * 3.f * gTime.deltaTime;
	float posY = mTest->GetPos().y;
	posY += h;

	mTest->SetPos(0, posY, 0.1);

	mTest->Update();
}

void Game::Draw()
{
	mTest->Draw();
	
}
