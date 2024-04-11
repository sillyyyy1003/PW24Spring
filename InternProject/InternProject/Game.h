#pragma once


class Camera;
class Sprite2D;
class ModelManager;
class KInput;
class Object;

class Game
{
private:
	Game() {};
	~Game();

private:

	//Tool 
	ModelManager* mAssetManager;
	//KInput* mInput;

	//Camera
	Camera* mMainCamera;
	Camera* mCamera2D;
	Camera* mCamera3D;

	//GameObject
	Object* mTestObj;


public:

	static Game* Get() { static Game Instance; return &Instance; };
	
	Camera* GetCamera2D() { return mCamera2D; };
	Camera* GetCamera3D() { return mCamera3D; }
	void SetMainCamera(Camera* _camera) { mMainCamera = _camera; };

	//初期化
	void InitGame();

	//更新
	void Update();

	//描画
	void Draw();
};

