#ifndef _ENGINE_CORE_H_
#define _ENGINE_CORE_H_

#include <memory>

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
	};
}

#endif // _ENGINE_CORE_H_