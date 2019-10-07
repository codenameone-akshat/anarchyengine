#ifndef _FRAMEWORK_ALIASES_H_
#define _FRAMEWORK_ALIASES_H_

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif // WIN32_LEAN_AND_MEAN

#ifndef NOMINMAX
#define NOMINMAX
#endif // NOMINMAX

#include <string>
#include <wrl.h>

#ifdef UNICODE

using AC_ConstCharPtr = LPCWSTR;
using AC_CharPtr = wchar_t*;
using AC_Char = wchar_t;
using AC_String = std::wstring;
using AC_OStringStream = std::wostringstream;
using AC_IStringStream = std::wistringstream;
using AC_StringStream = std::wstringstream;

#else

using AC_ConstCharPtr = LPCSTR;
using AC_CharPtr = char*;
using AC_Char = char;
using AC_String = std::string;
using AC_OStringStream = std::ostringstream;
using AC_IStringStream = std::istringstream;
using AC_StringStream = std::stringstream;

#endif // UNICODE

using AC_VoidPtr = void*;

// Com Specifics
template<typename T>
using AC_ComPtr = Microsoft::WRL::ComPtr<T>;

#endif // _FRAMEWORK_ALIASES_H_
