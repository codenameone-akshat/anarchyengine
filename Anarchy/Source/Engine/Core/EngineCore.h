#ifndef _ENGINE_CORE_H_
#define _ENGINE_CORE_H_

#include <memory>

#include "../../Framework/Window/WindowManager.h"

#ifdef AC_D3D12
#include "../Graphics/D3D12/D3D12Renderer.h"
#define	AC_RendererClass graphics::D3D12Renderer

#elif AC_D3D11
#include "../Graphics/D3D11/D3D11Renderer.h"
#define AC_RendererClass graphics::D3D11Renderer

#elif AC_VULKAN
#include "../Graphics/Vulkan/VulkanRenderer.h"
#define AC_RendererClass graphics::VulkanRenderer

#endif // AC_D3D12 | AC_D3D11 | AC_VULKAN

namespace anarchy::engine::core
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
		std::unique_ptr<framework::WindowManager> m_windowManger = std::make_unique<framework::WindowManager>();
		std::unique_ptr<graphics::GfxRenderer> m_renderer = std::make_unique<AC_RendererClass>();
	};
}

#endif // _ENGINE_CORE_H_