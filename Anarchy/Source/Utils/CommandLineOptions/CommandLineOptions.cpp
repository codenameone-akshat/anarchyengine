#include "CommandLineOptions.hpp"

#include "../../Engine/Core/EngineContext.h"

namespace anarchy::utils
{
	void anarchy::utils::CommandLineOptions::Init()
	{
		framework::AC_String commandLineString = engine::core::AppContext::GetMainParams().lpCmdLine;
	}
}
