#include <cassert>
#include <sstream>

#include "Logger.h"
#include "../../Framework/Includes/FrameworkGlobals.h"

namespace anarchy::utils
{
	void Logger::LogInfo(LogCategory logCategory, AC_ConstCharPtr outputStr)
	{
		ProcessAndLogString(logCategory, outputStr);
	}

	void Logger::LogInfo(LogCategory logCategory, AC_String outputStr)
	{
		LogInfo(logCategory, outputStr.c_str());
	}

	void Logger::LogWarning(LogCategory logCategory, bool condition, AC_ConstCharPtr outputStr)
	{
		::MessageBoxA(nullptr, "Warning!!! Please check the output window!!!", "Warning!", MB_OK);
		ProcessAndLogString(logCategory, outputStr);
	}

	void Logger::LogWarning(LogCategory logCategory, bool condition, AC_String outputStr)
	{
		LogWarning(logCategory, condition, outputStr.c_str());
	}

	void Logger::LogError(LogCategory logCategory, bool condition, AC_ConstCharPtr outputStr)
	{
		::MessageBoxA(nullptr, "Error!!! Please check the output window!!!", "Error!", MB_OK);
		assert(condition);
		ProcessAndLogString(logCategory, outputStr);
	}

	void Logger::LogError(LogCategory logCategory, bool condition, AC_String outputStr)
	{	
		LogError(logCategory, condition, outputStr.c_str());
	}
	
	void Logger::ProcessAndLogString(LogCategory logCategory, AC_ConstCharPtr outputString)
	{
		AC_ConstCharPtr logCategoryString = GetStringForCategory(logCategory);
		AC_OStringStream os_;
		os_ << logCategoryString << outputString << std::endl;
		OutputDebugString(os_.str().c_str());
	}
	
	AC_ConstCharPtr Logger::GetStringForCategory(LogCategory logCategory)
	{
		switch (logCategory)
		{
		case LogCategory::Debug: return "[Debug]: ";
			break;
		case LogCategory::System: return "[System]: ";
			break;
		case LogCategory::Engine: return "[Engine]: ";
			break;
		case LogCategory::Graphics: return "[Graphics]: ";
			break;
		case LogCategory::Physics: return "[Physics]: ";
			break;
		case LogCategory::Tool: return "[Tool]: ";
			break;
		case LogCategory::Framework: return "[Framework]: ";
			break;
		default: return "[UnClassified]: ";
			break;
		}
	}
}