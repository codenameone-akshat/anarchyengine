#include "EngineContext.h"

namespace anarchy::engine::core
{
	//------------------------------------Engine Context----------------------------------
	// Static Members Init
	bool EngineContext::ms_isEngineRunning = false;
	
	
	//------------------------------------App Context----------------------------------
	// Static Members Init
	MainParams AppContext::ms_mainParams;
	framework::WndProcFunctor AppContext::ms_wndProcFunctor = nullptr;
	std::shared_ptr<framework::Window> AppContext::ms_mainWindow = nullptr;
}
