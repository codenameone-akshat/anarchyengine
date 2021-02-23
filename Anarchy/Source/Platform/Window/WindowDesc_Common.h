#ifndef _WINDOW_BASE_H_
#define _WINDOW_BASE_H_

#include "Platform/Types/Types.h"

namespace anarchy
{
    struct WindowDesc_Common // Structure for Window Descriptor to setup Window
    {
        string windowName = "";
        int32 x = 0;
        int32 y = 0;
        int32 width = 0;
        int32 height = 0;
    };
}

#endif  // !_WINDOW_BASE_H_
