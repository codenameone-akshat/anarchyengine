#ifndef _TYPES_H_
#define _TYPES_H_

#include <string>

#ifdef PLATFORM_WINDOWS
#include <wrl.h>
#endif // PLATFORM_WINDOWS

namespace anarchy
{
	// byte
	using byte				= std::byte;

	// unsigned int
	using uint8				= std::uint8_t;
	using uint16			= std::uint16_t;
	using uint32			= std::uint32_t;
	using uint64			= std::uint64_t;

	// signed int			  
	using int8				= std::int8_t;
	using int16				= std::int16_t;
	using int32				= std::int32_t;
	using int64				= std::int64_t;

	// floating point
	using float32			= float;
	using float64			= double;

	// string | char types
	using wchar				= wchar_t;
	using string			= std::string;
	using wstring			= std::wstring;
	using cstring			= char*;

	// string stream
	using ostringstream		= std::ostringstream;
	using istringstream		= std::istringstream;
	using stringstream		= std::stringstream;

	using wostringstream	= std::wostringstream;
	using wistringstream	= std::wistringstream;
	using wstringstream		= std::wstringstream;

	// typeless
	using voidptr			= void*;
	using handle			= void*;

#ifdef PLATFORM_WINDOWS
	template<typename T>
	using ComPtr			= Microsoft::WRL::ComPtr<T>;
#endif // PLATFORM_WINDOWS

}
#endif // !_TYPES_H_