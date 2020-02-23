#include <d3d12.h>
#include "FrameworkGlobals.h"

namespace anarchy::framework
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Com Helpers
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	using LogCategory = utils::Logger::LogCategory;

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

//----------------------------------------------------------------------end of file-----------------------------------------------------------------------------
}