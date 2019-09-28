#include <cassert>
#include <sstream>

#include "Logger.h"

namespace anarchy::utils
{
	void Logger::LogInfo(AC_ConstCharPtr outputStr)
	{
		AC_OStringStream os_;
		os_ << outputStr << std::endl;
		OutputDebugString(os_.str().c_str());
	}

	void Logger::LogInfo(AC_String outputStr)
	{
		LogInfo(outputStr.c_str());
	}

	void Logger::LogWarning(bool condition, AC_ConstCharPtr outputStr)
	{
		::MessageBoxA(nullptr, "Warning!!! Please check the output window!!!", "Warning!", MB_OK);
		AC_OStringStream os_;
		os_ << outputStr << std::endl;
		OutputDebugString(os_.str().c_str());
	}

	void Logger::LogWarning(bool condition, AC_String outputStr)
	{
		LogWarning(condition, outputStr.c_str());
	}

	void Logger::LogError(bool condition, AC_ConstCharPtr outputStr)
	{
		::MessageBoxA(nullptr, "Error!!! Please check the output window!!!", "Error!", MB_OK);
		assert(condition);
		AC_OStringStream os_;
		os_ << outputStr << std::endl;
		OutputDebugString(os_.str().c_str());
	}

	void Logger::LogError(bool condition, AC_String outputStr)
	{
		LogError(condition, outputStr.c_str());
	}
}