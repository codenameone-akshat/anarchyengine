#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <windows.h>

#include "../../Framework/Includes/FrameworkAliases.h"

namespace anarchy::utils
{
	enum class LogCategory
	{
		Debug,
		System,
		Engine,
		Graphics,
		Physics,
		Tool,
		Framework
	};

	class Logger
	{
	public:
		Logger() = delete;
		~Logger() = delete;

		static void LogInfo(LogCategory logCategory, AC_ConstCharPtr outputStr);
		static void LogInfo(LogCategory logCategory, AC_String outputStr);
		static void LogWarning(LogCategory logCategory, bool condition, AC_ConstCharPtr outputStr);
		static void LogWarning(LogCategory logCategory, bool condition, AC_String outputStr);
		static void LogError(LogCategory logCategory, bool condition, AC_ConstCharPtr outputStr);
		static void LogError(LogCategory logCategory, bool condition, AC_String outputStr);
	
	private:

		static void ProcessAndLogString(LogCategory logCategory, AC_ConstCharPtr outputString);
		static AC_ConstCharPtr GetStringForCategory(LogCategory logCategory);
	};
}

#endif // _LOGGER_H_