#include "Engine/Core/EngineCore.h"
#include "Engine/Core/EngineContext.h"
#include "Framework/AppContext.h"

namespace anarchy
{
    void EngineCore::InitializeEngine()
    {
        // Initialize
        m_windowEventHandler->Initialize();
		AppContext::SetWindowEventHandler(m_windowEventHandler);

        m_mainWindow->InitWindowParams(); // default init
        m_mainWindow->SetMessageProcedureFunctor(AppContext::GetMessageHandlerFunctor());
        m_mainWindow->CreateNewWindow();
        m_mainWindow->ShowWindow();

        AppContext::SetHandleToMainWindow(m_mainWindow);
        AppContext::SetMainWindowDesc(m_mainWindow->GetWindowDesc());

        // Initialize the game specific settings
        m_gameSpecificCommands->InitializeSettings();
        EngineContext::SetGameSpecificSettings(m_gameSpecificCommands->GetSettings());
        
        // Initialize the Renderer
        m_renderer->Initialize();
    }

    void EngineCore::Update()
    {
        m_windowEventHandler->PollMessage();
		m_input.PollInputFromOS();

        m_renderer->PreRender();
        m_renderer->Render();
        m_renderer->PostRender();
    }

    void EngineCore::ShutDownEngine()
    {
        // Cleanup. Maybe call from Dtor for RAII?
        m_renderer->Shutdown();
        m_mainWindow->DestroyWindow();
    }
}
