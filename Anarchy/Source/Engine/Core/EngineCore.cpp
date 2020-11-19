#include "EngineCore.h"
#include "EngineContext.h"
#include "Framework/App/AppContext.h"

namespace anarchy
{
    void EngineCore::StartEngine()
    {
        // Initialize
        m_mainWindowIndex = m_windowManger->RequestNewDefaultWindow(AppContext::GetMainParams().hInstance, AppContext::GetWndProcHandle());
        m_windowManger->ShowWindow(m_mainWindowIndex, AppContext::GetMainParams().nShowCmd);

        AppContext::SetHandleToActiveWindow(m_windowManger->GetHandleToWindow(m_mainWindowIndex));
        AppContext::SetMainWindowDesc(m_windowManger->GetWindowDesc(m_mainWindowIndex));

        // Initialize the game specific settings
        m_gameSpecificMain->InitializeSettings();
        EngineContext::SetGameSpecificSettings(m_gameSpecificMain->GetSettings());

        // Initialize the Renderer
        m_renderer->Initialize();
    }

    void EngineCore::Update()
    {
        m_renderer->PreRender();
        m_renderer->Render();
        m_renderer->PostRender();
    }

    void EngineCore::ShutDownEngine()
    {
        // Cleanup. Maybe call from Dtor for RAII?
    }
}
