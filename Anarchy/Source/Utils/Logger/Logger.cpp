#include <sstream>

#include "Logger.h"
#include "Framework/FrameworkHelpers.h"

namespace anarchy
{
    void Logger::LogInfo(LogCategory logCategory, string outputStr)
    {
        ProcessAndLogString(logCategory, outputStr);
    }

    void Logger::LogInfo(LogCategory logCategory, ID3DBlob* outputBufferPtr)
    {
        ProcessAndLogString(logCategory, outputBufferPtr);
    }

    void Logger::LogWarning(LogCategory logCategory, bool condition, string outputStr)
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

    void Logger::LogError(LogCategory logCategory, bool condition, string outputStr)
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

    void Logger::ProcessAndLogString(LogCategory logCategory, string outputString)
    {
        string logCategoryString = GetStringForCategory(logCategory);
        ostringstream os_;
        os_ << logCategoryString << outputString << std::endl;
        OutputDebugString(os_.str().c_str());
    }

    void Logger::ProcessAndLogString(LogCategory logCategory, ID3DBlob* outputBufferPtr)
    {
        string outputString = static_cast<const char*>(outputBufferPtr->GetBufferPointer());
        string logCategoryString = GetStringForCategory(logCategory);
        ostringstream os_;
        os_ << logCategoryString << outputString << std::endl;
        OutputDebugString(os_.str().c_str());
    }

    string Logger::GetStringForCategory(LogCategory logCategory)
    {
        string outputCategory = "[" + LogCategory_Strings[static_cast<std::underlying_type_t<LogCategory>>(logCategory)] + "]: ";
        return outputCategory;
    }
}