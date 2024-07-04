#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <format>

class DebugLog
{
private:
	std::ofstream ofs;

private:
	DebugLog();
	~DebugLog();
	void OutputLog(std::string str);
public:

	bool Init(const char* _fileName);
	static void Log(const std::string& str);
	static void Log(const char* str);
	static void Log(float num);

	/// @brief 唯一のインスタンスを返す
	/// @return 
	static DebugLog* Get(){static DebugLog Instance; return &Instance;};
};

