#ifndef _ENGINE_CONTEXT_H_
#define _ENGINE_CONTEXT_H_

#include <memory>

#include "../../Framework/Window/Window.h"

namespace anarchy::engine::core
{
	// Static context maintaining the state of the engine.
	class EngineContext
	{
	public:
		EngineContext() = delete;
		~EngineContext() = default;

		static bool GetIsEngneRunning() noexcept { return ms_isEngineRunning; }
		static void SetIsEngneRunning(bool isEngineRunning) { ms_isEngineRunning = isEngineRunning; }
		
	private:
		inline static bool ms_isEngineRunning = false;
	};

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

		static framework::WndProcFunctor GetWndProcHandle() { return ms_wndProcFunctor; }
		static void SetWndProcHAndle(framework::WndProcFunctor wndProc) { ms_wndProcFunctor = wndProc; }
		
		static MainParams GetMainParams() noexcept { return ms_mainParams; }
		static void SetMainParams(MainParams mainParams) noexcept { ms_mainParams = mainParams; }

		static std::shared_ptr<framework::Window> GetHandleToActiveWindow() noexcept { return ms_mainWindow; }
		static void SetHandleToActiveWindow(std::shared_ptr<framework::Window> window) { ms_mainWindow = window; }
	
	private:

		inline static MainParams ms_mainParams = {};
		inline static framework::WndProcFunctor ms_wndProcFunctor = nullptr;
		inline static std::shared_ptr<framework::Window> ms_mainWindow = nullptr;
	};
}

#endif // _ENGINE_CONTEXT_H_