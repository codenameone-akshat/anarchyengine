#include "Framework/App/AppContext.h"
#include "Framework/Includes/FrameworkHeaders.h"

#define PROJECT_PARENT_DIR_NAME AC_STR_LITERAL("anarchyengine")

namespace anarchy { extern void EngineMain(); } // Defined in MainEngine.cpp

void anarchymain()
{
    anarchy::AC_String sourceDirPath = []()
    {
        const auto hModule = GetModuleHandle(NULL); // Get handle to current module
        const DWORD pathLength = 180;

        anarchy::AC_CharPtr outStr = static_cast<anarchy::AC_CharPtr>(calloc(pathLength, sizeof(char)));

        if (GetModuleFileNameA(hModule, outStr, pathLength))
        {
            anarchy::AC_String outputString(outStr);
            free(outStr);

            const anarchy::AC_String parentDirName(PROJECT_PARENT_DIR_NAME);
            const anarchy::AC_String sourceDir(AC_STR_LITERAL("\\Anarchy\\Source\\"));

            const size_t pos = outputString.find(parentDirName);
            outputString = outputString.substr(0, pos + parentDirName.length());

            outputString = outputString + sourceDir;
            outputString.shrink_to_fit();
            return outputString;
        }
        return anarchy::AC_String(AC_STR_LITERAL(""));
    }();

    anarchy::AppContext::SetSourceDirPath(sourceDirPath);

    anarchy::EngineMain();
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    anarchy::AppContext::SetMainParams({ hInstance, hPrevInstance, lpCmdLine, nShowCmd });

    anarchymain();

    return 0;
}