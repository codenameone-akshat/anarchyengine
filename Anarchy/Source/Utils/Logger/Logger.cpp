#include <cassert>
#include <sstream>

#include "Logger.h"
#include "../../Framework/Includes/FrameworkGlobals.h"

namespace anarchy::utils
{
	void Logger::LogInfo(LogCategory logCategory, framework::AC_String outputStr)
	{
		ProcessAndLogString(logCategory, outputStr);
	}

	void Logger::LogWarning(LogCategory logCategory, bool condition, framework::AC_String outputStr)
	{
		::MessageBoxA(nullptr, "Warning!!! Please check the output window!!!", "Warning!", MB_OK);
		ProcessAndLogString(logCategory, outputStr);
	}

	void Logger::LogError(LogCategory logCategory, bool condition, framework::AC_String outputStr)
	{
		::MessageBoxA(nullptr, "Error!!! Please check the output window!!!", "Error!", MB_OK);
		assert(condition);
		ProcessAndLogString(logCategory, outputStr);
	}

	void Logger::ProcessAndLogString(LogCategory logCategory, framework::AC_String outputString)
	{
		framework::AC_String logCategoryString = GetStringForCategory(logCategory);
		framework::AC_OStringStream os_;
		os_ << logCategoryString << outputString << std::endl;
		OutputDebugString(os_.str().c_str());
	}

	framework::AC_String Logger::GetStringForCategory(LogCategory logCategory)
	{
		framework::AC_String outputCategory = "[" + m_logCategoryStrings[static_cast<std::underlying_type_t<LogCategory>>(logCategory) - 1] + "]: ";
		return outputCategory;
	}
}