#include <sstream>

#include "Logger.h"
#include "../../Framework/Includes/FrameworkGlobals.h"
#include "../../Framework/Includes/FrameworkDefines.h"

namespace anarchy::utils
{
	void Logger::LogInfo(LogCategory logCategory, framework::AC_String outputStr)
	{
		ProcessAndLogString(logCategory, outputStr);
	}

	void Logger::LogInfo(LogCategory logCategory, ID3DBlob* outputBufferPtr)
	{
		ProcessAndLogString(logCategory, outputBufferPtr);
	}

	void Logger::LogWarning(LogCategory logCategory, bool condition, framework::AC_String outputStr)
	{
		if (!condition)
		{
			ProcessAndLogString(logCategory, outputStr);
			ACBreak;
		}
	}

	void Logger::LogWarning(LogCategory logCategory, bool condition, ID3DBlob* outputBufferPtrr)
	{
		if (!condition)
		{
			ProcessAndLogString(logCategory, outputBufferPtrr);
			ACBreak;
		}
	}

	void Logger::LogError(LogCategory logCategory, bool condition, framework::AC_String outputStr)
	{
		if (!condition)
		{
			ProcessAndLogString(logCategory, outputStr);
			ACForceCrash;
		}
	}

	void Logger::LogError(LogCategory logCategory, bool condition, ID3DBlob* outputBufferPtr)
	{
		if (!condition)
		{
			ProcessAndLogString(logCategory, outputBufferPtr);
			ACForceCrash;
		}
	}

	void Logger::ProcessAndLogString(LogCategory logCategory, framework::AC_String outputString)
	{
		framework::AC_String logCategoryString = GetStringForCategory(logCategory);
		framework::AC_OStringStream os_;
		os_ << logCategoryString << outputString << std::endl;
		OutputDebugString(os_.str().c_str());
	}

	void Logger::ProcessAndLogString(LogCategory logCategory, ID3DBlob* outputBufferPtr)
	{
		framework::AC_String outputString = static_cast<const char*>(outputBufferPtr->GetBufferPointer());
		framework::AC_String logCategoryString = GetStringForCategory(logCategory);
		framework::AC_OStringStream os_;
		os_ << logCategoryString << outputString << std::endl;
		OutputDebugString(os_.str().c_str());
	}

	framework::AC_String Logger::GetStringForCategory(LogCategory logCategory)
	{
		framework::AC_String outputCategory = "[" + LogCategory_Strings[static_cast<std::underlying_type_t<LogCategory>>(logCategory)] + "]: ";
		return outputCategory;
	}
}