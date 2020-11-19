#ifndef _WINDOW_H_
#define _WINDOW_H_

#ifdef PLATFORM_WINDOWS
#include "Platform/Window/Window_Windows.h"
namespace anarchy { using Window = Window_Windows; }
#elif PLATFORM_LINUX
#include "Platform/Window/Window_XCB.h"
namespace anarchy { using Window = Window_XCB; }
#endif // PLATFORM_WINDOWS || PLATFORM_LINUX

#endif // !_WINDOW_H_
