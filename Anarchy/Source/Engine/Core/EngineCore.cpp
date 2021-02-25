#include "acpch.h"

#include "Engine/Core/EngineCore.h"
#include "Engine/Core/EngineContext.h"
#include "Framework/AppContext.h"
#include <Framework/GameSpecificInterface.h>

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
        
        GameSpecificInterface::SetupGameSpecificInstance();
        acGameSpecificInterface->Initialize();

        // Initialize the Renderer
        m_gfxManager->Initialize();        
    }

    void EngineCore::GenerateData()
    {
        ACScopedTimer("Generating Data: ");
        std::unique_ptr<ModelImporter> modelImporter = std::make_unique<ModelImporter>();
        string dataDir = AppContext::GetDataDirPath() + string("/RawData/") + "sponza.fbx"; // TODO: Get models from a file.
        modelImporter->ReadEntityFromFileAndSerialize(dataDir);
    }

    void EngineCore::Update()
    {
        m_windowEventHandler->PollMessage();
        m_input.PollInputFromOS();
        acGameSpecificInterface->Update();

        acGameSpecificInterface->PreRender();
        m_gfxManager->PreRender();
        
        acGameSpecificInterface->Render();
        m_gfxManager->Render();
        
        acGameSpecificInterface->PostRender();
        m_gfxManager->PostRender();
    }

    void EngineCore::ShutdownEngine()
    {
        // Cleanup. Maybe call from Dtor for RAII?
        m_gfxManager->Shutdown();
        acGameSpecificInterface->Shutdown();
        m_mainWindow->DestroyWindow();
    }
}
