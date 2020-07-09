#ifndef _CLASS_HELPERS_H

namespace anarchy
{

#define DECLARE_DEFAULT_CLASSMEMBERS(className)\
public:\
className() = default;\
~className() = default;\
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

#define DECLARE_GETTERSETTER(type, varName, propertyName) \
inline type Get##propertyName() { return m_##varName; } \
inline void Set##propertyName(type& arg) { m_##varName = arg; } 

#define DECLARE_PROPERTY(type, varName, propertyName, defaultVal) \
public: \
DECLARE_GETTERSETTER(type, varName, propertyName) \
private: \
type m_##varName = defaultVal; 

#define DECLARE_DEFAULT_PROPERTY(type, varName, propertyName) \
DECLARE_PROPERTY(type, varName, propertyName, {}) 

}
#endif // !_CLASS_HELPERS_H
