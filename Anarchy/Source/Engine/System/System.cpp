#include "System.h"
#include "../Core/EngineContext.h"

namespace anarchy
{
    void System::Initialize()
    {
        m_engineCore->StartEngine();
        EngineContext::SetIsEngneRunning(true);
    }

    void System::SystemTick()
    {
        // All the DT work here. Set it to engine context too.

        Update();

        // Post DT work here.
    }

    void System::Destruct()
    {
        m_engineCore->ShutDownEngine();
    }

    void System::Update()
    {
        m_engineCore->Update();
    }
}