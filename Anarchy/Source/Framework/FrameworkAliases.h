#ifndef _FRAMEWORK_ALIASES_H_
#define _FRAMEWORK_ALIASES_H_

#ifdef PLATFORM_WINDOWS

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif // WIN32_LEAN_AND_MEAN

#ifndef NOMINMAX
#define NOMINMAX
#endif // NOMINMAX

#endif // PLATFORM_WINDOWS

#include <string>

#ifdef PLATFORM_WINDOWS
#include <wrl.h>
#endif // PLATFORM_WINDOWS

namespace anarchy
{

#ifdef PLATFORM_WINDOWS
    // Com Specifics
    template<typename T>
    using AC_ComPtr = Microsoft::WRL::ComPtr<T>;
#endif // PLATFORM_WINDOWS
}
#endif // _FRAMEWORK_ALIASES_H_
