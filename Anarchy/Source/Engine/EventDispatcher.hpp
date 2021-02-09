#ifndef _EVENT_DISPATCHER_HPP_
#define _EVENT_DISPATCHER_HPP_

#include <functional>

#include <Engine/NativeEvent.h>

namespace anarchy
{
    class EventDispatcher
    {
    public:
        static EventDispatcher& GetInstance()
        {
            static EventDispatcher instance;
            return instance;
        }

        template <typename EventType, typename HandlerType>
        void RegisterEventCallback(HandlerType* handler, void (HandlerType::*&&Callback)(GenericEvent& ev))
        {
            signalSlot slot = std::bind(Callback, handler, std::placeholders::_1);

            auto eventRef = [&]()
            {
                auto iterator = m_eventHandlers.find(EventType::GetName());
                if (iterator == m_eventHandlers.end()) // cant find event type 
                {
                    auto [insertionItr, result] = m_eventHandlers.insert(EventType::GetName(), std::make_unique<NativeEvent>());
                    return insertionItr->second;
                }
                else
                {
                    return iterator->second;
                }
            }();

            eventRef->connectionRefs.push_back(eventRef->signal.connect(slot));
        }

        template <typename EventType>
        void TriggerEvent(EventType event)
        {
            // redirection for better API syntax? XD. sorry
            TriggerEventInternal<EventType>(event);
        }

    private:
        template <typename EventType>
        void TriggerEventInternal(GenericEvent event) 
        {
            m_eventHandlers[EventType::GetName()].signal(event);
        }

        boost::ptr_unordered_map<std::string, NativeEvent> m_eventHandlers;
    };
}

#define acEventDispatcher EventDispatcher::GetInstance()

#endif // !_EVENT_DISPATCHER_HPP_
