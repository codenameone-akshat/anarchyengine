#ifndef _CLASS_HELPERS_H

namespace anarchy
{
// Class Basic Members Helpers
#define DECLARE_DEFAULT_CLASSMEMBERS(className)\
public:\
className() = default;\
~className() = default;\
className(const className&) = default;\
className(className&&) = default;\
className& operator=(const className&) = default;

#define DECLARE_DEFAULT_CLASSMEMBERS_NODEF_CTOR(className)\
public:\
className();\
~className() = default;\
className(const className&) = default;\
className(className&&) = default;\
className& operator=(const className&) = default;

#define DECLARE_DEFAULT_CLASSMEMBERS_NODEF_DTOR(className)\
public:\
className() = default;\
~className();\
className(const className&) = default;\
className(className&&) = default;\
className& operator=(const className&) = default;

#define DECLARE_DEFAULT_CLASSMEMBERS_NODEF_CTORDTOR(className)\
public:\
className();\
~className();\
className(const className&) = default;\
className(className&&) = default;\
className& operator=(const className&) = default;

#define DECLARE_DELETED_CLASSMEMBERS(className)\
public:\
className() = delete;\
~className() = delete;\
className(const className&) = delete;\
className(className&&) = delete;\
className& operator=(const className&) = delete;
// !Class Basic Members Helpers


// Class Member Getter Setter Helpers
#define DECLARE_DEFAULT_ACCESSORS(type, varName, propertyName) \
inline type Get##propertyName() { return m_##varName; } \
inline void Set##propertyName(type& arg) { m_##varName = arg; }

#define DECLARE_DEFAULT_ACCESSORS_NODEF_GET(type, varName, propertyName) \
inline type Get##propertyName();\
inline void Set##propertyName(type& arg) { m_##varName = arg; }

#define DECLARE_DEFAULT_ACCESSORS_NODEF_SET(type, varName, propertyName) \
inline type Get##propertyName() { return m_##varName; } \
inline void Set##propertyName(type& arg);

#define DECLARE_DEFAULT_ACCESSORS_NODEF_GETSET(type, varName, propertyName) \
inline type Get##propertyName(); \
inline void Set##propertyName(type& arg);
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
// !Class Member Default Initialized Declaration Helpers

}
#endif // !_CLASS_HELPERS_H
