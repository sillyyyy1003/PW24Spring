#include "DebugLog.h"
#include <sstream>

DebugLog::DebugLog()
{
	Init("DebugLog.txt");
}

DebugLog::~DebugLog()
{
}

bool DebugLog::Init(const char* _fileName)
{
	ofs = std::ofstream(_fileName);
	if(!ofs)
	{
		std::cout << "DebugLog Failed" << std::endl;
		return false;
	}

	std::cout << "DebugLog Success" << std::endl;
	return true;
}

void DebugLog::Log(const std::string& str)
{
	DebugLog::Get()->OutputLog(str);
}

void DebugLog::Log(const char* _str)
{
	std::string str(_str);
	Log(str);
}

void DebugLog::Log(const float num)
{
	std::stringstream ss;
	ss << num;
	std::string str = ss.str();
	Log(str);
}

void DebugLog::OutputLog(std::string str)
{
	ofs <<  str << std::endl;
	std::cout << str << std::endl;
}
