#ifndef _ENGINE_CONTEXT_H_
#define _ENGINE_CONTEXT_H_

#include <memory>

#include "Game/GameSettings/GameSettings.h"
#include "Framework/Math/Vector/Vec4.hpp"
#include "Framework/ClassHelpers.h"

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

		static math::Vec4<float> GetClearColor() noexcept { return ms_clearColor; }
		static void SetClearColor(math::Vec4<float> clearColor) { ms_clearColor = clearColor; }

    private:
        inline static bool ms_isEngineRunning = false;
        inline static std::shared_ptr<game::GameSettings> m_gameSpecificSettings = nullptr;
        inline static math::Vec4<float> ms_clearColor = { 0.0f, 0.5f, 0.7f, 1.0f };
    };
}

#endif // _ENGINE_CONTEXT_H_