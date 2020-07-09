#ifndef _ENGINE_CORE_H_
#define _ENGINE_CORE_H_

#include <memory>

#include "../../Framework/Window/WindowManager.h"
#include "../../Game/GameSpecificMain.h"

#ifdef AC_D3D12
#include "../Graphics/D3D12/D3D12Renderer.h"
using AC_RendererClass = anarchy::D3D12Renderer;

#elif AC_D3D11
#include "../Graphics/D3D11/D3D11Renderer.h"
using AC_RendererClass = anarchy::D3D11Renderer;

#elif AC_VULKAN
#include "../Graphics/Vulkan/VulkanRenderer.h"
using AC_RendererClass = anarchy::VulkanRenderer;

#endif // AC_D3D12 | AC_D3D11 | AC_VULKAN

namespace anarchy
{
    class EngineCore
    {
    public:
        EngineCore() = default;
        ~EngineCore() = default;

        void StartEngine();
        void Update();
        void ShutDownEngine();

    private:

        uint32_t m_mainWindowIndex = 0;
        std::unique_ptr<WindowManager> m_windowManger = std::make_unique<WindowManager>();
        std::unique_ptr<GfxRenderer> m_renderer = std::make_unique<AC_RendererClass>();
        std::unique_ptr<game::GameSpecificMain> m_gameSpecificMain = std::make_unique<game::GameSpecificMain>();
    };
}

#endif // _ENGINE_CORE_H_