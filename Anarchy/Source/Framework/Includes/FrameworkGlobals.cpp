#include <d3d12.h>
#include <cassert>

#include "FrameworkGlobals.h"
#include "FrameworkDefines.h"

namespace anarchy::framework
{
	using LogCategory = utils::Logger::LogCategory;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Com Helpers
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void ComCheck(HRESULT hr, AC_String message)
	{
		if (SUCCEEDED(hr))
			return;
		else
		{
			utils::Logger::LogError(LogCategory::Graphics, false, message);
		}
	}

	void ComCheck(HRESULT hr, AC_String message, framework::AC_ComPtr<ID3DBlob> errorMessagePtr)
	{
		if (SUCCEEDED(hr))
		{
			if (errorMessagePtr)
				utils::Logger::LogWarning(LogCategory::Graphics, false, errorMessagePtr.Get());

			return;
		}
		else
		{
			if (errorMessagePtr)
				utils::Logger::LogError(LogCategory::Graphics, false, errorMessagePtr.Get());
			else
				utils::Logger::LogError(LogCategory::Graphics, false, message);
		}
	}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Assertion
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void AC_Assert(bool condition, AC_String message)
	{
		if (!condition)
		{
			utils::Logger::LogInfo(LogCategory::System, message);
			assert(false);
		}
	}

	void AC_SoftAssert(bool condition, AC_String message)
	{
		if (!condition)
		{
			utils::Logger::LogInfo(LogCategory::System, message);
			Sleep(500); // Giving it a little suspense
			AcBreak;
		}
	}

//----------------------------------------------------------------------end of file-----------------------------------------------------------------------------
}