#ifndef _FRAMEWORK_DEFINES_H_
#define _FRAMEWORK_DEFINES_H_


#ifdef UNICODE

#define AC_STR_LITERAL(x) L##x

#else

#define AC_STR_LITERAL(x) x

#endif // UNICODE

#define AC_NODISCARD [[nodiscard]]
#define AC_FORCEINLINE __forceinline

#endif // _FRAMEWORK_DEFINES_H_
