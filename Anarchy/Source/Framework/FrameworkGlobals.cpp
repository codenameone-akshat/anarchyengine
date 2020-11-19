#include <d3d12.h>

#include "FrameworkGlobals.h"
#include "FrameworkDefines.h"

namespace anarchy
{
	using LogCategory = Logger::LogCategory;

#ifdef PLATFORM_WINDOWS
// Com Helpers
	void ComCheck(HRESULT hr, string message)
	{
		if (SUCCEEDED(hr))
			return;
		else
		{
			Logger::LogError(LogCategory::Graphics, false, message);
		}
	}

	void ComCheck(HRESULT hr, string message, AC_ComPtr<ID3DBlob>& errorMessagePtr)
	{
		if (SUCCEEDED(hr))
		{
			if (errorMessagePtr)
				Logger::LogWarning(LogCategory::Graphics, false, errorMessagePtr.Get());

			return;
		}
		else
		{
			if (errorMessagePtr)
				Logger::LogError(LogCategory::Graphics, false, errorMessagePtr.Get());
			else
				Logger::LogError(LogCategory::Graphics, false, message);
		}
	}
#endif // PLATFORM_WINDOWS

// Assertion
	void AC_Assert(bool condition, string message)
	{
		if (!condition)
		{
			Logger::LogInfo(LogCategory::System, message);
			ACForceCrash;
		}
	}

	void AC_SoftAssert(bool condition, string message)
	{
		if (!condition)
		{
			Logger::LogInfo(LogCategory::System, message);
			Sleep(500); // Giving it a little suspense
			ACBreak;
		}
	}
}