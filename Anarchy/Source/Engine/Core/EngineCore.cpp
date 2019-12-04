#include "EngineCore.h"
#include "EngineContext.h"

namespace anarchy::engine::core
{	
	void EngineCore::StartEngine()
	{
		// Initialize
		m_mainWindowIndex = m_windowManger->RequestNewDefaultWindow(AppContext::GetMainParams().hInstance, AppContext::GetWndProcHandle());
		m_windowManger->ShowWindow(m_mainWindowIndex, AppContext::GetMainParams().nShowCmd);
		
		AppContext::SetHandleToActiveWindow(m_windowManger->GetHandleToWindow(m_mainWindowIndex));
		AppContext::SetMainWindowDesc(m_windowManger->GetWindowDesc(m_mainWindowIndex));

		// Initialize the Renderer
		m_renderer->Initialize();
	}
	
	void EngineCore::Update()
	{
		// Stub
	}

	void EngineCore::ShutDownEngine()
	{
		// Cleanup. Maybe call from Dtor for RAII?
	}
}
