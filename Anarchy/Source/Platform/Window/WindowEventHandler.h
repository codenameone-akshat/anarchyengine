#ifndef _WINDOW_EVENT_HANDLER_H_
#define _WINDOW_EVENT_HANDLER_H_

enum class WindowEvent
{
    Close,
    Quit,
    Resize
};

#ifdef PLATFORM_WINDOWS
#include "Platform/Window/WindowEventHandler_Windows.h"
namespace anarchy { using WindowEventHandler = WindowEventHandler_Windows; }
#elif PLATFORM_LINUX
#include "Platform/Window/WindowEventHandler_XCB.h"
namespace anarchy { using WindowEventHandler = WindowEventHandler_XCB; }
#endif // PLATFORM_WINDOWS || PLATFORM_LINUX

#endif // !_WINDOW_EVENT_HANDLER_H_
