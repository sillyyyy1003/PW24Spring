#pragma once

namespace scene
{
	enum SCENE
	{
		NONE,
		TITLE,
		STAGE,
		RESULT,
	};

	//FOR SCENE TRANSITION
	enum TRANSITION
	{


	};
}

class Scene
{
private:
	scene::SCENE mScene = scene::NONE;
	scene::SCENE mNextScene = scene::NONE;

public:

	Scene(void);

	//Set This Scene
	void SetScene(scene::SCENE _scene) { mScene = _scene; };
	scene::SCENE GetScene() { return mScene; };

	//Set Next Scene
	void SetNextScene(scene::SCENE _nextScene) { mNextScene = _nextScene; };
	scene::SCENE GetNextScene() { return mNextScene; };

	void ChangeScene(scene::SCENE _scene,scene::TRANSITION _transition);

};

