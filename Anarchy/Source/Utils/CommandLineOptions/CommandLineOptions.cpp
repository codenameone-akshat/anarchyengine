#include "CommandLineOptions.hpp"

#include "../../Engine/Core/EngineContext.h"

namespace anarchy
{
	void anarchy::CommandLineOptions::Init()
	{
		AC_String commandLineString = AppContext::GetMainParams().lpCmdLine;
	}
}
