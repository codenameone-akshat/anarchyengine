#include <memory>

#include "Platform/Platform.h"
#include "Engine/Core/EngineCore.h"
#include "Engine/Core/EngineContext.h"

int32 anarchyMain(int32 argc, const string argv)
{
    std::unique_ptr<EngineCore> engineCore = std::make_unique<EngineCore>();
    engineCore->InitializeEngine();
    
    EngineContext::SetIsEngneRunning(true);

    do
	{
		// Engine Running state should be set in the enginecore
        engineCore->Update();

	} while (EngineContext::GetIsEngneRunning());

    engineCore->ShutdownEngine();

    return 0;
}