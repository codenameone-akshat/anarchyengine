#ifndef _PLATFORM_H_
#define _PLATFORM_H_

#ifdef PLATFORM_WINDOWS
#include "Framework/Platform/Platform_Windows.h"
#elif PLATFORM_LINUX
#include "Framework/Platform/Platform_Linux.h"
#endif // PLATFORM_WINDOWS | PLATFORM_LINUX

// Common Functions
inline void StartAnarchyEngine()
{
    anarchy::EngineMain();
}


#endif // _PLATFORM_H_
