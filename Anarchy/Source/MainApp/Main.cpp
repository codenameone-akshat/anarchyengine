#include "../Framework/Includes/FrameworkHeaders.h"
#include "../Engine/Core/EngineContext.h"

#define PROJECT_PARENT_DIR_NAME AC_STR_LITERAL("anarchyengine")

namespace anarchy::engine::core { extern void EngineMain(); } // Defined in MainEngine.cpp

void anarchymain()
{
	anarchy::framework::AC_String sourceDirPath = []()
	{
		const auto hModule = GetModuleHandle(NULL); // Get handle to current module
		const DWORD pathLength = 180;

		anarchy::framework::AC_CharPtr outStr = static_cast<anarchy::framework::AC_CharPtr>(calloc(pathLength, sizeof(char)));

		if (GetModuleFileNameA(hModule, outStr, pathLength))
		{
			anarchy::framework::AC_String outputString(outStr);
			free(outStr);

			const anarchy::framework::AC_String parentDirName(PROJECT_PARENT_DIR_NAME);
			const anarchy::framework::AC_String sourceDir(AC_STR_LITERAL("\\Anarchy\\Source\\"));

			const size_t pos = outputString.find(parentDirName);
			outputString = outputString.substr(0, pos + parentDirName.length());
			
			outputString = outputString + sourceDir;
			outputString.shrink_to_fit();
			return outputString;
		}
		return anarchy::framework::AC_String(AC_STR_LITERAL(""));
	}();

	anarchy::engine::core::AppContext::SetSourceDirPath(sourceDirPath);

	anarchy::engine::core::EngineMain();
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	anarchy::engine::core::AppContext::SetMainParams({ hInstance, hPrevInstance, lpCmdLine, nShowCmd });
	
	anarchymain();

	return 0;
}