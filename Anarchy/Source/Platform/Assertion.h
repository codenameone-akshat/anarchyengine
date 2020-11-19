#ifndef _ASSERTION_H_
#define _ASSERTION_H_

#include <fmt/core.h>

#include "Utils/Logger/Logger.h"
#include "Utils/StringUtils/StringUtils.h"

namespace anarchy
{
	using LogCategory = Logger::LogCategory;

//#ifdef PLATFORM_WINDOWS
//	// Define these here inline
//	void ComCheck(HRESULT hr, string message);
//	void ComCheck(HRESULT hr, string message, ComPtr<ID3DBlob>& errorMessagePtr);
//#endif // PLATFORM_WINDOWS

	// Terminates the program
	inline void TriggerAssertion(bool condition, string message, string sourceFileName, int32 line)
	{
		// TODO: replace with std::format when stdlib supports it
		string assertMessage = fmt::format("{}. File: {}. Line: {}.", message, sourceFileName, line);
		Logger::LogError(LogCategory::System, condition, assertMessage);
	}
	
	// Doesn't terminate the program.
	inline void TriggerSoftAssertion(bool condition, string message, string sourceFileName, int32 line)
	{
		// TODO: replace with std::format when stdlib supports it
		string assertMessage = fmt::format("{}. File: {}. Line: {}.", message, sourceFileName, line);
		Logger::LogWarning(LogCategory::System, condition, assertMessage);
	}

#ifdef AC_DEBUG
#define Assert(x, message) TriggerAssertion(x, message, __FILE__, __LINE__)
#define SoftAssert(x, message) TriggerSoftAssertion(x, message, __FILE__, __LINE__)
#define NoImplAssert TriggerAssertion(false, string("No implementation error"), __FILE__, __LINE__)
#else
#define Assert(x, message)
#define SoftAssert(x, message)
#define NoImplAssert TriggerAssertion(false, "No implementation error", __FILE__, __LINE__)
#endif // AC_DEBUG
}

#endif // !_ASSERTION_H_
 