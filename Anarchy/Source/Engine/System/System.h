#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#include <stdint.h>
#include <memory>

#include "../Core/EngineCore.h"

namespace anarchy::engine::system
{
	// Will Handle the engine, IO and timers.
	class System final
	{
	public:
		System() = default;
		~System() = default;

		void Initialize();
		void SystemTick();
		void Destruct();

	private:
		void Update();

		uint_fast16_t m_dt = 0;
		std::unique_ptr<core::EngineCore> m_engineCore = std::make_unique<core::EngineCore>();
	};
}

#endif // _SYSTEM_H_