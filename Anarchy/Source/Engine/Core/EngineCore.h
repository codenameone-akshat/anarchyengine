#ifndef _ENGINE_CORE_H_
#define _ENGINE_CORE_H_

#include <memory>

#include "Game/GameSpecificCommands.h"
#include "Engine/Input/InputHandler.h"
#include "Platform/Window/Window.h"
#include "Platform/Window/WindowEventHandler.h"

#if defined(AC_D3D12) && defined(PLATFORM_WINDOWS)
#include "Graphics/D3D12/D3D12Renderer.h"
using RenderAPI = anarchy::D3D12Renderer;

#elif AC_VULKAN
#include "Graphics/Vulkan/VulkanRenderer.h"
using RenderAPI = anarchy::VulkanRenderer;

#endif // AC_D3D12 | AC_D3D11 | AC_VULKAN

namespace anarchy
{
    class EngineCore
    {
    public:
        EngineCore() = default;
        ~EngineCore() = default;

        void InitializeEngine();
        void Update();
        void ShutdownEngine();

    private:

        std::shared_ptr<Window> m_mainWindow = std::make_shared<Window>();
        std::shared_ptr<WindowEventHandler> m_windowEventHandler = std::make_shared<WindowEventHandler>();
        std::unique_ptr<GfxRenderer> m_renderer = std::make_unique<RenderAPI>();
        std::unique_ptr<game::GameSpecificCommands> m_gameSpecificCommands = std::make_unique<game::GameSpecificCommands>();
		InputHandler& m_input = InputHandler::GetInstance();
    };
}

#endif // _ENGINE_CORE_H_