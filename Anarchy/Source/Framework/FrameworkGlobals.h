#ifndef _FRAMEWORK_GLOBALS_H_
#define _FRAMEWORK_GLOBALS_H_

#include <string>

#include "Utils/Logger/Logger.h"

namespace anarchy
{

#ifdef PLATFORM_WINDOWS
 // Com Helpers
    void ComCheck(HRESULT hr, string message);
    void ComCheck(HRESULT hr, string message, AC_ComPtr<ID3DBlob>& errorMessagePtr);
#endif // PLATFORM_WINDOWS

// Assertion
    void AC_Assert(bool condition, string message);
    void AC_SoftAssert(bool condition, string message);

}

#endif // _FRAMEWORK_GLOBALS_H_
