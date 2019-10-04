#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <array>
#include <tuple>

#include "../../Framework/Includes/FrameworkAliases.h"
#include "../../Framework/Includes/FrameworkHeaders.h"

namespace anarchy::utils
{
	enum class LogCategory : uint16_t
	{
		Debug = 1,
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

		static void LogInfo(LogCategory logCategory, AC_String outputStr);
		static void LogWarning(LogCategory logCategory, bool condition, AC_String outputStr);
		static void LogError(LogCategory logCategory, bool condition, AC_String outputStr);
	
	private:
		inline static const std::array<AC_String, static_cast<std::underlying_type_t<LogCategory>>(LogCategory::Framework)> m_logCategoryStrings =
		{
			"Debug",
			"System",
			"Engine",
			"Graphics",
			"Physics",
			"Tool",
			"Framework"
		};

		static void ProcessAndLogString(LogCategory logCategory, AC_String outputString);
		static AC_String GetStringForCategory(LogCategory logCategory);
	};
}

#endif // _LOGGER_H_