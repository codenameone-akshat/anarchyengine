#include <d3d12.h>

#include "FrameworkGlobals.h"
#include "FrameworkDefines.h"

namespace anarchy
{
	using LogCategory = Logger::LogCategory;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Com Helpers
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void ComCheck(HRESULT hr, AC_String message)
	{
		if (SUCCEEDED(hr))
			return;
		else
		{
			Logger::LogError(LogCategory::Graphics, false, message);
		}
	}

	void ComCheck(HRESULT hr, AC_String message, AC_ComPtr<ID3DBlob>& errorMessagePtr)
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Assertion
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void AC_Assert(bool condition, AC_String message)
	{
		if (!condition)
		{
			Logger::LogInfo(LogCategory::System, message);
			ACForceCrash;
		}
	}

	void AC_SoftAssert(bool condition, AC_String message)
	{
		if (!condition)
		{
			Logger::LogInfo(LogCategory::System, message);
			Sleep(500); // Giving it a little suspense
			ACBreak;
		}
	}

//----------------------------------------------------------------------end of file-----------------------------------------------------------------------------
}