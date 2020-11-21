#ifndef _APP_CONTEXT_H_
#define _APP_CONTEXT_H_

#include <memory>

#include "Platform/PlatformConfig.h"
#include "Platform/Window/WindowEventHandler.h"
#include "Platform/Window/Window.h"
#include "Framework/ClassHelpers.h"

namespace anarchy
{
    // Static context maintaining the state and info of the main app.
#ifdef PLATFORM_WINDOWS
    struct MainParams
    {
        HINSTANCE hInstance = nullptr;
        HINSTANCE hPrevInstance = nullptr;
        int32 argc = 0;
        string argv = "";
        int32 showCmd = 0;
    };
#endif //PLATFORM_WINDOWS

    class AppContext
    {
    public:
        AppContext() = delete;
        ~AppContext() = delete;

#ifdef PLATFORM_WINDOWS
		static MessageHandlerFunctor GetMessageHandlerFunctor() { return ms_messageHandlerFunctor; }
        static void SetMessageHandlerFunctor(MessageHandlerFunctor messageHandler) { ms_messageHandlerFunctor = messageHandler; }

		static MainParams GetMainParams() noexcept { return ms_mainParams; }
        static void SetMainParams(MainParams mainParams) noexcept { ms_mainParams = mainParams; }
#endif //PLATFORM_WINDOWS

		static std::shared_ptr<WindowEventHandler> GetWindowEventHandler() { return ms_windowEventHandler; }
		static void SetWindowEventHandler(std::shared_ptr<WindowEventHandler> windowEventHandler) { ms_windowEventHandler = windowEventHandler; }

        static std::shared_ptr<Window> GetHandleToMainWindow() noexcept { return ms_mainWindow; }
        static void SetHandleToMainWindow(std::shared_ptr<Window> window) { ms_mainWindow = window; }

        static WindowDesc GetMainWindowDesc() { return ms_mainWindow->GetWindowDesc(); }
        static void SetMainWindowDesc(WindowDesc windowDesc) { ms_mainWindow->SetWindowDesc(windowDesc); }

        static string GetSourceDirPath() { return ms_sourceDirPath; }
        static void SetSourceDirPath(string path) { ms_sourceDirPath = path; }

        DECLARE_PROPERTY_STATIC(bool, isResizeTriggered, IsResizeTriggered, false);

    private:
        WINDOWS_ONLY(inline static MainParams ms_mainParams = {};)
        WINDOWS_ONLY(inline static MessageHandlerFunctor ms_messageHandlerFunctor = nullptr;)

        inline static  std::shared_ptr<WindowEventHandler> ms_windowEventHandler = nullptr;
        inline static std::shared_ptr<Window> ms_mainWindow = nullptr;
        inline static WindowDesc ms_mainWindowDesc = {};
        inline static string ms_sourceDirPath = {};
    };
}

#endif // !_APP_CONTEXT_H_
