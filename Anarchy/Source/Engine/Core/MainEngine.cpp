#include "acpch.h"

#include <memory>

#include <Platform/Platform.h>
#include <Engine/Core/EngineCore.h>
#include <Engine/Core/EngineContext.h>
#include <Utils/CommandLineOptions/CommandLineManager.h>
#include <Utils/CommandLineOptions/CommandLineOptions.h>

int32 anarchyMain(int32 argc, const string argv)
{
    CommandLineManager commandLineManager;
    commandLineManager.RegisterAllOptions();
    commandLineManager.ParseAndApplyOptions(argv);

    std::unique_ptr<EngineCore> engineCore = std::make_unique<EngineCore>();

    if (!CommandLineOptions::shouldGenerateData) // trying for a true branch
    {
        engineCore->InitializeEngine();

        EngineContext::SetIsEngneRunning(true);

        do
        {
            // Engine Running state should be set in the enginecore
            engineCore->Update();

        } while (EngineContext::GetIsEngneRunning());

        engineCore->ShutdownEngine();
    }
    else
    {
        engineCore->GenerateData();
    }

    return 0;
}