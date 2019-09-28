#include <memory>

#include "MainEngine.h"
#include "EngineContext.h"
#include "../System/System.h"

namespace anarchy::engine::core
{
	void EngineMain()
	{
		std::unique_ptr<system::System> system = std::make_unique<system::System>();
		
		AppContext::SetWndProcHAndle(MainEngineWindowProc);

		system->Initialize();

		do
		{
			//Engine Running state should be set in the enginecore

			system->SystemTick();
	
		} while (EngineContext::GetIsEngneRunning());
	}	

	LRESULT CALLBACK MainEngineWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
		case WM_DESTROY:
			::PostQuitMessage(0);
			return 0;
			break;
		}
		return ::DefWindowProc(hWnd, message, wParam, lParam);
	}
}