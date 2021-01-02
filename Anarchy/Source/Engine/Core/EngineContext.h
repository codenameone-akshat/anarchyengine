#ifndef _ENGINE_CONTEXT_H_
#define _ENGINE_CONTEXT_H_

#include <memory>

#include "Game/GameSettings/GameSettings.h"

namespace anarchy
{
    // Static context maintaining the state of the engine.
    class EngineContext
    {
    public:
        EngineContext() = delete;
        ~EngineContext() = default;

        static bool GetIsEngneRunning() noexcept { return ms_isEngineRunning; }
        static void SetIsEngneRunning(bool isEngineRunning) { ms_isEngineRunning = isEngineRunning; }

        static std::shared_ptr<game::GameSettings> GetGameSpecificSettings() { return m_gameSpecificSettings; }
        static void SetGameSpecificSettings(std::shared_ptr<game::GameSettings> settings) { m_gameSpecificSettings = settings; }

    private:
        inline static bool ms_isEngineRunning = false;
        inline static std::shared_ptr<game::GameSettings> m_gameSpecificSettings = nullptr;
    };
}

#endif // _ENGINE_CONTEXT_H_