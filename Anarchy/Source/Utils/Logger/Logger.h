#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <array>
#include <tuple>
#include <d3d12.h>

#include "../../Framework/Includes/FrameworkAliases.h"
#include "../../Framework/Includes/FrameworkHeaders.h"
#include "../../Utils/MacroHelpers/EnumHelpers.h"

namespace anarchy::utils
{
	
	class Logger
	{
	public:
		DECLARE_STATIC_INLINE_STRING_ENUM(LogCategory, (Debug)(System)(Engine)(Graphics)(Physics)(Tool)(Framework));

		Logger() = delete;
		~Logger() = delete;

		static void LogInfo(LogCategory logCategory, framework::AC_String outputStr);
		static void LogInfo(LogCategory logCategory, ID3DBlob* outputBufferPtr);
		
		static void LogWarning(LogCategory logCategory, bool condition, framework::AC_String outputStr);
		static void LogWarning(LogCategory logCategory, bool condition, ID3DBlob* outputBufferPtr);
		
		static void LogError(LogCategory logCategory, bool condition, framework::AC_String outputStr);
		static void LogError(LogCategory logCategory, bool condition, ID3DBlob* outputBufferPtr);
	
	private:
		static void ProcessAndLogString(LogCategory logCategory, framework::AC_String outputString);
		static void ProcessAndLogString(LogCategory logCategory, ID3DBlob* outputBufferPtr);
		static framework::AC_String GetStringForCategory(LogCategory logCategory);
	};
}

#endif // _LOGGER_H_