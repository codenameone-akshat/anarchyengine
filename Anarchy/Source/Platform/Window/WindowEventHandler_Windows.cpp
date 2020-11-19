#include "WindowEventHandler.h"
#include "Framework/AppContext.h"
#include "Engine/Core/EngineContext.h"

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
		switch (message)
		{
		case WM_CLOSE:
			WindowEventHandlerPtr->HandleMessage(WindowEvent::Close);
			::PostQuitMessage(0);
			return 0;
		}
		return ::DefWindowProc(hWnd, message, wParam, lParam);
	}
#undef WindowEventHandlerPtr
}