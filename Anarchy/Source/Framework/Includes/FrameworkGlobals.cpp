#include "FrameworkGlobals.h"

namespace anarchy::framework
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Com Helpers
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void ComCheck(HRESULT hr, AC_String message)
	{
		if (SUCCEEDED(hr))
			return;
		else
			utils::Logger::LogError(utils::LogCategory::Graphics, false, message);
	}
//----------------------------------------------------------------------end of file-----------------------------------------------------------------------------
}