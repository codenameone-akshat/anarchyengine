#ifndef _FRAMEWORK_DEFINES_H_
#define _FRAMEWORK_DEFINES_H_

namespace anarchy::framework
{
#ifdef UNICODE

#define AC_STR_LITERAL(x) L##x

#else

#define AC_STR_LITERAL(x) x

#endif // UNICODE

#define AC_NODISCARD [[nodiscard]]
#define AC_FORCEINLINE __forceinline

#define AC_EXPAND_AND_TOKEN_PASTE(X,Y) X##Y
#define AC_TOKEN_PASTE(X,Y) AC_EXPAND_AND_TOKEN_PASTE(X,Y)
#define AC_UNIQUE_VARIABLE(varName) AC_TOKEN_PASTE(varname##_unique_var_, __COUNTER__)

#define ACScopedTimer(tag) anarchy::utils::ScopedTimer AC_UNIQUE_VARIABLE(timer)(tag);

#define ACForceCrash *((uint64_t*)0) = 0xDEAD;

#ifdef AC_DEBUG
#define ACBreak __debugbreak();
#else
#define ACBreak 
#endif // AC_DEBUG

}

#endif // _FRAMEWORK_DEFINES_H_
