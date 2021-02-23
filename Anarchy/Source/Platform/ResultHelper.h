#ifndef _RESULT_CHECKER_H_
#define _RESULT_CHECKER_H_

#ifdef PLATFORM_WINDOWS

#include <d3d12.h>
#include <string>
#include <wrl.h>

#include "Utils/Logger/Logger.h"

namespace anarchy
{
    using LogCategory = Logger::LogCategory;

    inline void CheckResult(HRESULT hr, string message)
    {
        if (SUCCEEDED(hr))
            return;
        else
        {
            Logger::LogError(LogCategory::Graphics, false, message);
        }
    }

    inline void CheckResult(HRESULT hr, string message, ComPtr<ID3DBlob>& errorMessagePtr)
    {
        if (SUCCEEDED(hr))
        {
            if (errorMessagePtr)
                Logger::LogWarning(LogCategory::Graphics, false, errorMessagePtr.Get());

            return;
        }
        else
        {
            if (errorMessagePtr)
                Logger::LogError(LogCategory::Graphics, false, errorMessagePtr.Get());
            else
                Logger::LogError(LogCategory::Graphics, false, message);
        }
    }
}

#endif // PLATFORM_WINDOWS

// Later add for whatever linux / vulkan uses.

#endif // !_RESULT_CHECKER_H_
