#include "acpch.h"
#include "SandboxInterface.h"

#include <Game/DebugUI.h>

namespace anarchy
{
    // Instance Creation
    GAME_SPECIFIC_INTERFACE_CREATEINSTANCE_IMPL_BEGIN
        GameSpecificInterface::SetInstance(std::make_shared<sandbox::SandboxInterface>());
    GAME_SPECIFIC_INTERFACE_CREATEINSTANCE_IMPL_END
    
    namespace sandbox
    {
        void SandboxInterface::Initialize()
        {
            SUPER_CALL(super::Initialize();)
        }

        void SandboxInterface::Update()
        {
            SUPER_CALL(super::Update();)
        }

        void SandboxInterface::PreRender()
        {
            SUPER_CALL(super::PreRender();)
        }

        void SandboxInterface::Render()
        {
            SUPER_CALL(super::Render();)
            m_debugUI->Draw();
        }

        void SandboxInterface::PostRender()
        {
            SUPER_CALL(super::PostRender();)
        }

        void SandboxInterface::Shutdown()
        {
            SUPER_CALL(super::Shutdown();)
        }
    }
}
