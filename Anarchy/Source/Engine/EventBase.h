#ifndef _EVENT_BASE_H_
#define _EVENT_BASE_H_

#include <any>

namespace anarchy
{
    using GenericEvent = std::any;

    // Empty base class now
    struct EventBase
    {
    };

    // Helpers
#define DECLARE_EVENT_CLASS(EventName) struct EventName final : public EventBase 

#define DECLARE_EVENT_RTTI(EventName) \
    public: \
        static std::string GetName() { return m_name; } \
    private: \
        inline static std::string m_name = #EventName;

#define DECLARE_EVENT_CALLBACK(FunctionName) void FunctionName (GenericEvent& event)
#define DEFINE_EVENT_CALLBACK(FunctionName) void FunctionName (GenericEvent& event)
#define DEFINE_EVENT_MEMBER_CALLBACK(ClassMember, FunctionName) void ClassMember::##FunctionName (GenericEvent& event)

#define EVENT_CAST(EventType) std::any_cast<EventType>(event)
}

#endif // !_EVENT_BASE_H_
