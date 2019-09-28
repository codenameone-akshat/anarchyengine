#include "../Framework/Includes/FrameworkHeaders.h"
#include "../Engine/Core/EngineContext.h"

namespace anarchy::engine::core { extern void EngineMain(); } // Defined in MainEngine.cpp

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	anarchy::engine::core::AppContext::SetMainParams({ hInstance, hPrevInstance, lpCmdLine, nShowCmd });
	anarchy::engine::core::EngineMain();
	
	return 0;
}