#ifndef _CLASS_HELPERS_H

#include <type_traits>

namespace anarchy
{

// Class Basic Members Helpers
#define DECLARE_DEFAULT_CLASSMEMBERS(className) \
public: \
className() = default; \
~className() = default; \
className(const className&) = default; \
className(className&&) = default; \
className& operator=(const className&) = default;

#define DECLARE_DEFAULT_CLASSMEMBERS_NO_DEFAULTCONSTRUCTIBLE(className) \
public: \
className() = delete; \
~className() = default; \
className(const className&) = default; \
className(className&&) = default; \
className& operator=(const className&) = default;

#define DECLARE_DEFAULT_CLASSMEMBERS_DELETED_CTOR(className) DECLARE_DEFAULT_CLASSMEMBERS_NO_DEFAULTCONSTRUCTIBLE(className) 

#define DECLARE_DEFAULT_CLASSMEMBERS_VIRTUAL_DTOR(className) \
public: \
className() = default; \
virtual ~className() = default; \
className(const className&) = default; \
className(className&&) = default; \
className& operator=(const className&) = default;

#define DECLARE_DEFAULT_CLASSMEMBERS_NODEF_CTOR(className) \
public: \
className(); \
~className() = default; \
className(const className&) = default; \
className(className&&) = default; \
className& operator=(const className&) = default;

#define DECLARE_DEFAULT_CLASSMEMBERS_NODEF_DTOR(className) \
public: \
className() = default; \
~className(); \
className(const className&) = default; \
className(className&&) = default; \
className& operator=(const className&) = default;

#define DECLARE_DEFAULT_CLASSMEMBERS_NODEF_CTORDTOR(className) \
public: \
className(); \
~className(); \
className(const className&) = default; \
className(className&&) = default; \
className& operator=(const className&) = default;

#define DECLARE_DEFAULT_CLASSMEMBERS_NOCOPY(className) \
public: \
className() = default; \
~className() = default; \
className(const className&) = delete;\
className(className&&) = default;\
className& operator=(const className&) = delete;

#define DECLARE_DEFAULT_CLASSMEMBERS_NOMOVE(className) \
public: \
className() = default; \
~className() = default; \
className(const className&) = default; \
className(className&&) = delete; \
className& operator=(const className&) = default;

#define DECLARE_DEFAULT_CLASSMEMBERS_NO_COPY_NOMOVE(className) \
public: \
className() = default; \
~className() = default; \
className(const className&) = delete; \
className(className&&) = delete; \
className& operator=(const className&) = delete;

#define DECLARE_DELETED_CLASSMEMBERS(className) \
public: \
className() = delete; \
~className() = delete; \
className(const className&) = delete; \
className(className&&) = delete; \
className& operator=(const className&) = delete;
// !Class Basic Members Helpers


// Class Member Getter Setter Helpers
#define DECLARE_DEFAULT_ACCESSORS(type, varName, propertyName) \
inline type Get##propertyName() const { return m_##varName; } \
inline void Set##propertyName(const type& arg) { m_##varName = arg; }

#define DECLARE_DEFAULT_ACCESSORS_NODEF_GET(type, varName, propertyName) \
inline type Get##propertyName() const;\
inline void Set##propertyName(const type& arg) { m_##varName = arg; }

#define DECLARE_DEFAULT_ACCESSORS_NODEF_SET(type, varName, propertyName) \
inline type Get##propertyName() const { return m_##varName; } \
inline void Set##propertyName(const type& arg);

#define DECLARE_DEFAULT_ACCESSORS_NODEF_GETSET(type, varName, propertyName) \
inline type Get##propertyName() const; \
inline void Set##propertyName(const type& arg);

#define DECLARE_DEFAULT_ACCESSORS_NO_GET(type, varName, propertyName) \
inline void Set##propertyName(const type& arg) { m_##varName = arg; }

#define DECLARE_DEFAULT_ACCESSORS_NO_SET(type, varName, propertyName) \
inline type Get##propertyName() const { return m_##varName; } \

#define DECLARE_DEFAULT_ACCESSORS_STATIC(type, varName, propertyName) \
static type Get##propertyName() { return ms_##varName; } \
static void Set##propertyName(const type& arg) { ms_##varName = arg; }

#define DECLARE_DEFAULT_ACCESSORS_REFGET(type, varName, propertyName) \
inline type& Get##propertyName() { return m_##varName; } \
inline void Set##propertyName(const type& arg) { m_##varName = arg; }
// !Class Member Getter Setter Helpers


// Class Member Declaration Helpers
#define DECLARE_PROPERTY(type, varName, propertyName, defaultVal) \
public: \
DECLARE_DEFAULT_ACCESSORS(type, varName, propertyName) \
private: \
type m_##varName = defaultVal; 

#define DECLARE_PROPERTY_NODEF_GET(type, varName, propertyName, defaultVal) \
public: \
DECLARE_DEFAULT_ACCESSORS_NODEF_GET(type, varName, propertyName) \
private: \
type m_##varName = defaultVal; 

#define DECLARE_PROPERTY_NODEF_SET(type, varName, propertyName, defaultVal) \
public: \
DECLARE_DEFAULT_ACCESSORS_NODEF_SET(type, varName, propertyName) \
private: \
type m_##varName = defaultVal; 

#define DECLARE_PROPERTY_NODEF_GETSET(type, varName, propertyName, defaultVal) \
public: \
DECLARE_DEFAULT_ACCESSORS_NODEF_GETSET(type, varName, propertyName) \
private: \
type m_##varName = defaultVal; 

#define DECLARE_PROPERTY_NO_GET(type, varName, propertyName, defaultVal) \
public: \
DECLARE_DEFAULT_ACCESSORS_NO_GET(type, varName, propertyName) \
private: \
type m_##varName = defaultVal; 

#define DECLARE_PROPERTY_NO_SET(type, varName, propertyName, defaultVal) \
public: \
DECLARE_DEFAULT_ACCESSORS_NO_SET(type, varName, propertyName) \
private: \
type m_##varName = defaultVal; 

#define DECLARE_PROPERTY_STATIC(type, varName, propertyName, defaultVal) \
public: \
DECLARE_DEFAULT_ACCESSORS_STATIC(type, varName, propertyName) \
private: \
inline static type ms_##varName = defaultVal; 

#define DECLARE_PROPERTY_REFGET(type, varName, propertyName, defaultVal) \
public: \
DECLARE_DEFAULT_ACCESSORS_REFGET(type, varName, propertyName) \
private: \
type m_##varName = defaultVal; 
// !Class Member Declaration Helpers


// Class Member Default Initialized Declaration Helpers
#define DECLARE_DEFAULT_PROPERTY(type, varName, propertyName) \
DECLARE_PROPERTY(type, varName, propertyName, {}) 

#define DECLARE_DEFAULT_PROPERTY_NODEF_GET(type, varName, propertyName) \
DECLARE_PROPERTY_NODEF_GET(type, varName, propertyName, {}) 

#define DECLARE_DEFAULT_PROPERTY_NODEF_SET(type, varName, propertyName) \
DECLARE_PROPERTY_NODEF_SET(type, varName, propertyName, {}) 

#define DECLARE_DEFAULT_PROPERTY_NODEF_GETSET(type, varName, propertyName) \
DECLARE_PROPERTY_NODEF_GETSET(type, varName, propertyName, {}) 

#define DECLARE_DEFAULT_PROPERTY_NO_GET(type, varName, propertyName) \
DECLARE_PROPERTY_NO_GET(type, varName, propertyName, {}) 

#define DECLARE_DEFAULT_PROPERTY_NO_SET(type, varName, propertyName) \
DECLARE_PROPERTY_NO_SET(type, varName, propertyName, {}) 

#define DECLARE_DEFAULT_PROPERTY_STATIC(type, varName, propertyName) \
DECLARE_PROPERTY_STATIC(type, varName, propertyName, {}) 

#define DECLARE_DEFAULT_PROPERTY_REFGET(type, varName, propertyName) \
DECLARE_PROPERTY_REFGET(type, varName, propertyName, {}) 
// !Class Member Default Initialized Declaration Helpers

// Class Security Helpers
#define VIRTUAL_DTOR_GUARD(Base) \
static_assert(std::has_virtual_destructor<Base>::value, "Possible Memory Leak. Base Class doesn't have a virual desctructor.");

//#define NO_DEFAULT_CONSTRUCT_GUARD(T) \ 
//static_assert(!std::is_default_constructible_v<T>, "T is default constructible.");

// !Class Security Helpers

}
#endif // !_CLASS_HELPERS_H
 