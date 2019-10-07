#ifndef _ENGINE_CORE_H_
#define _ENGINE_CORE_H_

#include <memory>

#include "../Graphics/D3D12/D3D12Renderer.h"
#include "../../Framework/Window/WindowManager.h"

namespace anarchy::engine::core
{
	class EngineCore
	{
	public:
		EngineCore() = default;
		~EngineCore() = default;

		void StartEngine();
		void ShutDownEngine();
		void Update();

	private:

		uint32_t m_mainWindowIndex = 0;
		std::unique_ptr<framework::WindowManager> m_windowManger = std::make_unique<framework::WindowManager>();
		std::unique_ptr<graphics::D3D12Renderer> m_renderer = std::make_unique<graphics::D3D12Renderer>();
	};
}

#endif // _ENGINE_CORE_H_