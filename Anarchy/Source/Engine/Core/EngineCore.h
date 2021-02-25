#ifndef _ENGINE_CORE_H_
#define _ENGINE_CORE_H_

#include <memory>

#include <Game/GameSpecificCommands.h>
#include <Engine/Input/InputHandler.h>
#include <Platform/Window/Window.h>
#include <Platform/Window/WindowEventHandler.h>
#include <Graphics/GfxManager.h>

namespace anarchy
{
    class EngineCore
    {
    public:
        EngineCore() = default;
        ~EngineCore() = default;

        void InitializeEngine();
        void GenerateData();
        void Update();
        void ShutdownEngine();
        
    private:

        std::shared_ptr<Window> m_mainWindow = std::make_shared<Window>();
        std::shared_ptr<WindowEventHandler> m_windowEventHandler = std::make_shared<WindowEventHandler>();
        std::unique_ptr<GfxManger> m_gfxManager = std::make_unique<GfxManger>();
        std::unique_ptr<game::GameSpecificCommands> m_gameSpecificCommands = std::make_unique<game::GameSpecificCommands>();

        InputHandler& m_input = InputHandler::GetInstance();
    };
}

#endif // _ENGINE_CORE_H_