#ifndef _APP_CONTEXT_H_
#define _APP_CONTEXT_H_

#include "Framework/Window/Window.h"

namespace anarchy
{
    // Static context maintaining the state and info of the main app.
    struct MainParams
    {
        HINSTANCE hInstance = nullptr;
        HINSTANCE hPrevInstance = nullptr;
        LPSTR lpCmdLine = nullptr;
        int32_t nShowCmd = 0;
    };

    class AppContext
    {
    public:
        AppContext() = delete;
        ~AppContext() = delete;

        static WndProcFunctor GetWndProcHandle() { return ms_wndProcFunctor; }
        static void SetWndProcHAndle(WndProcFunctor wndProc) { ms_wndProcFunctor = wndProc; }

        static MainParams GetMainParams() noexcept { return ms_mainParams; }
        static void SetMainParams(MainParams mainParams) noexcept { ms_mainParams = mainParams; }

        static std::shared_ptr<Window> GetHandleToActiveWindow() noexcept { return ms_mainWindow; }
        static void SetHandleToActiveWindow(std::shared_ptr<Window> window) { ms_mainWindow = window; }

        static WindowDesc GetMainWindowDesc() { return ms_mainWindowDesc; }
        static void SetMainWindowDesc(WindowDesc windowDesc) { ms_mainWindowDesc = windowDesc; }

        static AC_String GetSourceDirPath() { return ms_sourceDirPath; }
        static void SetSourceDirPath(AC_String path) { ms_sourceDirPath = path; }

    private:
        inline static MainParams ms_mainParams = {};
        inline static WndProcFunctor ms_wndProcFunctor = nullptr;
        inline static std::shared_ptr<Window> ms_mainWindow = nullptr;
        inline static WindowDesc ms_mainWindowDesc = {};
        inline static AC_String ms_sourceDirPath = {};
    };
}

#endif // !_APP_CONTEXT_H_
