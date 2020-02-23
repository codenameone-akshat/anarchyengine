#include <memory>

#include "MainEngine.h"
#include "EngineContext.h"
#include "../System/System.h"
#include "../../Utils/Logger/Logger.h"

namespace anarchy::engine::core
{
	void EngineMain()
	{
		std::unique_ptr<system::System> system = std::make_unique<system::System>();

		AppContext::SetWndProcHAndle(MainEngineWindowProc);

		system->Initialize();

		do
		{
			// Engine Running state should be set in the enginecore
			PollMessage();
			system->SystemTick();
	
		} while (EngineContext::GetIsEngneRunning());

		// End Running.
		system->Destruct();
	}
	
	void PollMessage()
	{
		MSG msg = {};
		while (::PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) // 0,0 here represents to take any input possible
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT)
			EngineContext::SetIsEngneRunning(false);
	}

	LRESULT CALLBACK MainEngineWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
		case WM_CLOSE:
			::PostQuitMessage(0);
			return 0;
		}
		return ::DefWindowProc(hWnd, message, wParam, lParam);
	}
}