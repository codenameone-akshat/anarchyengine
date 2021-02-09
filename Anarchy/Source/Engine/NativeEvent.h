#ifndef _NATIVE_EVENT_H_
#define _NATIVE_EVENT_H_

#include <vector>
#include <boost/signals2.hpp>
#include <boost/ptr_container/ptr_unordered_map.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

#include <Engine/EventBase.h>

namespace anarchy
{
    using eventSignal = boost::signals2::signal<void(GenericEvent& ev)>;
    using signalSlot = eventSignal::slot_type;
    using slotConnection = boost::signals2::connection;

    class NativeEvent final
    {
    public:
        NativeEvent() = default;
        ~NativeEvent() = default;
        NativeEvent(const NativeEvent&) = default;

        eventSignal signal;
        boost::ptr_vector<signalSlot> slotRefs;
        std::vector<slotConnection> connectionRefs;
    };
}

#endif // !_NATIVE_EVENT_H_
