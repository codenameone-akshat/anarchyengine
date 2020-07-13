#include "CommandLineOptions.hpp"

#include "Framework/App/AppContext.h"

namespace anarchy
{
	void anarchy::CommandLineOptions::Init()
	{
		AC_String commandLineString = AppContext::GetMainParams().lpCmdLine;
	}
}
