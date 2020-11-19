#ifndef _PLATFORM_H_
#define _PLATFORM_H_

#include "Platform/PlatformConfig.h"
#include "Platform/Types/Types.h"

// Defined by game or app
anarchy::int32 anarchyMain(anarchy::int32 argc, const anarchy::string argv);

#define ForceCrash *((uint64_t*)0) = 0xDEAD;

#ifdef AC_DEBUG

#ifdef PLATFORM_WINDOWS
#define HWBreak __debugbreak(); // Stupid MSVC ignores asm and __asm instructions on x64.
#else
#define HWBreak asm("int 3");
#endif // PLATFORM_WINDOWS

#else
#define HWBreak 
#endif // AC_DEBUG

#ifdef AC_DEBUG
#define DEBUGONLY(x) x
#else
#define DEBUGONLY(x)
#endif // AC_DEBUG

#ifdef PLATFORM_WINDOWS
#include "Platform/Platform_Windows.h"
#elif PLATFORM_LINUX
#include "Platform/Platform_Linux.h"
#endif // PLATFORM_WINDOWS || PLATFORM_LINUX

#endif // !_PLATFORM_H_
