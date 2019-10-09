#ifndef _FRAMEWORK_GLOBALS_H_
#define _FRAMEWORK_GLOBALS_H_

#include <string>

#include "../../Utils/Logger/Logger.h"

namespace anarchy::framework
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// String Unicode Globals
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef UNICODE

	auto constexpr AC_Str_Default = L"";

	template <typename T>
	auto constexpr AC_To_String(T x) { return std::to_wstring(x); }

#else

	auto constexpr AC_Str_Default = "";

	template <typename T, typename = std::enable_if_t<!std::is_same_v<T, bool>>>
	auto constexpr AC_To_String(T x) { return std::to_string(x); }

#endif // UNICODE

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Com Helpers
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void ComCheck(HRESULT hr, AC_String message);
	
//----------------------------------------------------------------------end of file-----------------------------------------------------------------------------
}

#endif // _FRAMEWORK_GLOBALS_H_
