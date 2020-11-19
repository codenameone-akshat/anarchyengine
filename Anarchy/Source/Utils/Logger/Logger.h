#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <array>
#include <d3d12.h>

#include "Utils/MacroHelpers/EnumHelpers.h"

namespace anarchy
{
    class Logger
    {
    public:
        DECLARE_STATIC_INLINE_STRING_ENUM(LogCategory, (Debug)(System)(Engine)(Graphics)(Physics)(Tool)(Framework));

        Logger() = delete;
        ~Logger() = delete;

        static void LogInfo(LogCategory logCategory, string outputStr);
        static void LogInfo(LogCategory logCategory, ID3DBlob* outputBufferPtr);

        static void LogWarning(LogCategory logCategory, bool condition, string outputStr);
        static void LogWarning(LogCategory logCategory, bool condition, ID3DBlob* outputBufferPtr);

        static void LogError(LogCategory logCategory, bool condition, string outputStr);
        static void LogError(LogCategory logCategory, bool condition, ID3DBlob* outputBufferPtr);

    private:
        static void ProcessAndLogString(LogCategory logCategory, string outputString);
        static void ProcessAndLogString(LogCategory logCategory, ID3DBlob* outputBufferPtr);
        static string GetStringForCategory(LogCategory logCategory);
    };
}

#endif // _LOGGER_H_