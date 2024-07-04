#pragma once

namespace Rail
{
	enum Dir
	{
		UP,//0
		UPRIGHT,//1
		RIGHT,//2
		DOWNRIGHT,//3
		DOWN,//4
		DOWNLEFT,//5
		LEFT,//6
		UPLEFT,//7
		STILL = 99,
	};

	struct PointInfo
	{
		bool isVacant;
		bool isMoveable[8];
	};
}

class RailManager
{
public:
	Rail::PointInfo mInfo[15];

public:
	
	RailManager();
	~RailManager();
	/// @brief レール上全て位置の初期化
	void InitRail();

	/// @brief 毎ステージ前オブジェクト初期位置のレール情報初期化
	void InitRailPos(void);


	
};

