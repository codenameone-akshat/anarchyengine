#include "acpch.h"

#include "WindowEventHandler.h"
#include "Framework/AppContext.h"
#include "Engine/Core/EngineContext.h"
#include "Graphics/ImGui/Windows/imgui_impl_win32.h"

// External Linkage to ImGui WindowEventHandler
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace anarchy
{
	void WindowEventHandler_Windows::Initialize()
	{
		AppContext::SetMessageHandlerFunctor(MessageHandler);
	}

	void WindowEventHandler_Windows::PollMessage()
	{
		MSG msg = {};
		while (::PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) // 0,0 here represents to take any input possible
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT)
			HandleMessage(WindowEvent::Quit);
	}

	void WindowEventHandler_Windows::HandleMessage(WindowEvent event)
	{
		switch (event)
		{
		case WindowEvent::Quit:
			EngineContext::SetIsEngneRunning(false);
			break;
		case WindowEvent::Close:
			break;
		default:
			break;
		}
	}

#define WindowEventHandlerPtr AppContext::GetWindowEventHandler()
	

	// Namespace Scope. Not in Class. (Do something with this?)
	LRESULT CALLBACK MessageHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		if (::ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
			return true;

		switch (message)
		{
		case WM_CLOSE:
			WindowEventHandlerPtr->HandleMessage(WindowEvent::Close);
			::PostQuitMessage(0);
			return 0;
			break;
		case WM_SIZE:
			if (!AppContext::GetHandleToMainWindow())
				break;

			auto windowDesc = AppContext::GetMainWindowDesc();
			uint32 width = (UINT)LOWORD(lParam);
			uint32 height = (UINT)HIWORD(lParam);
			windowDesc.width = width;
			windowDesc.height = height;
			AppContext::SetMainWindowDesc(windowDesc);
			AppContext::SetIsResizeTriggered(true);
			break;
		}
		return ::DefWindowProc(hWnd, message, wParam, lParam);
	}
#undef WindowEventHandlerPtr
}