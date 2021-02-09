#ifndef _GFX_EVENTS_H_
#define _GFX_EVENTS_H_

#include <Engine/EventBase.h>

namespace anarchy
{
    DECLARE_EVENT_CLASS(SwapChainResizeEvent)
    {
        DECLARE_EVENT_RTTI(SwapChainResizeEvent);
    };
}

#endif // !_GFX_EVENTS_H_
