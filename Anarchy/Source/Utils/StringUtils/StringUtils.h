#ifndef _STRING_UTILS_H_
#define _STRING_UTILS_H_

#ifdef PLATFORM_WINDOWS
#include <windows.h>
#endif // PLATFORM_WINDOWS

namespace anarchy
{
	template <typename T, typename = std::enable_if_t<!std::is_same_v<T, bool>>>
	auto constexpr to_string(T x) { return std::to_string(x); }

#ifdef PLATFORM_WINDOWS
	template <typename T, typename = std::enable_if_t<std::is_same_v<T, std::wstring>>>
    T string_cast(const std::string input)
    {
        // Get the size to allocate.
        uint32_t wstringSize = MultiByteToWideChar(CP_ACP, NULL, &input[0], static_cast<int32_t>(input.length()), NULL, 0);

        if (wstringSize)
        {
            std::wstring outputString;
            outputString.resize(wstringSize);

            MultiByteToWideChar(CP_ACP, NULL, input.c_str(), static_cast<int32_t>(input.length()), &outputString[0], wstringSize);

            return outputString;
        }

        return std::wstring(); // Return an empty wstring.
    }

    template <typename T, typename = std::enable_if_t<std::is_same_v<T, std::string>>>
    T string_cast(const std::wstring input)
    {
        // Get the size to allocate.
        uint32_t stringSize = WideCharToMultiByte(CP_ACP, NULL, &input[0], static_cast<int32_t>(input.length()), NULL, 0, NULL, NULL);

        if (stringSize)
        {
            std::string outputString;
            outputString.resize(stringSize);

            WideCharToMultiByte(CP_ACP, NULL, input.c_str(), static_cast<int32_t>(input.length()), &outputString[0], stringSize, NULL, NULL);

            return outputString;
        }

        return std::string(); // Return an empty string.
    }
}
#endif // PLATFORM_WINDOWS

#endif // _STRING_UTILS_H_
