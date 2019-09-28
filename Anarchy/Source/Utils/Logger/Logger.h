#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <windows.h>

#include "../../Framework/Includes/FrameworkAliases.h"

namespace anarchy::utils
{
	class Logger
	{
	public:
		Logger() = delete;
		~Logger() = delete;

		static void LogInfo(AC_ConstCharPtr outputStr);
		static void LogInfo(AC_String outputStr);
		static void LogWarning(bool condition, AC_ConstCharPtr outputStr);
		static void LogWarning(bool condition, AC_String outputStr);
		static void LogError(bool condition, AC_ConstCharPtr outputStr);
		static void LogError(bool condition, AC_String outputStr);
	};
}

#endif // _LOGGER_H_