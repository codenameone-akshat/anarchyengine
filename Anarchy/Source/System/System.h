#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#include <cstdint>
#include <memory>

#include "Engine/Core/EngineCore.h"
#include "System/Input/InputHandler.h"

namespace anarchy
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
        std::unique_ptr<EngineCore> m_engineCore = std::make_unique<EngineCore>();
        InputHandler& m_input = InputHandler::GetInstance();
    };
}

#endif // _SYSTEM_H_