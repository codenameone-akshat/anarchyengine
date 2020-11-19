#ifndef _FRAMEWORK_HEADERS_H_
#define _FRAMEWORK_HEADERS_H_

//Windows Includes
#ifdef PLATFORM_WINDOWS
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif // WIN32_LEAN_AND_MEAN

#ifndef NOMINMAX
#define NOMINMAX
#endif // NOMINMAX

#include <windows.h>
#endif // PLATFORM_INCLUDES

//STD Includes
#include <cstdint>

//----------------------------------------------------------------------end of file-----------------------------------------------------------------------------

#endif // _FRAMEWORK_HEADERS_H_