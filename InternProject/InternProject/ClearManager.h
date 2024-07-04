#pragma once
#include "GameObject2D.h"


class ClearManager
{
public:
	ClearManager() = default;
	~ClearManager() = default;
	void Update();
private:

	void ClearStage1_1();
	void ClearStage1_2();
	void ClearStage1_3();

	bool isClear(std::string name, GameObject::RailPos pos);

	GameObject2D& FindObj(std::string name, std::vector<GameObject2D*> vObj);

};

