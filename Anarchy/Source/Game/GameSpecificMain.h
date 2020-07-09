#ifndef _GAME_SPECIFIC_MAIN_
#define _GAME_SPECIFIC_MAIN_

#include <memory>

#include "GameSettings/GameSettings.h"

namespace anarchy::game
{
    class GameSpecificMain
    {
    public:
        GameSpecificMain() = default;
        ~GameSpecificMain() = default;

        void InitializeSettings();
        void MainRun();

        inline std::shared_ptr<GameSettings> GetSettings() { return m_settings; }

    private:
        void AddAllShaders();

        std::shared_ptr<GameSettings> m_settings = std::make_shared<GameSettings>();
    };
}

#endif // _GAME_SPECIFIC_MAIN_
