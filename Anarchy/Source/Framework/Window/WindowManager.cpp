#include <string>

#include "WindowManager.h"
#include "../Includes/FrameworkGlobals.h"
#include "../../Utils/Logger/Logger.h"

namespace anarchy::framework
{
	uint32_t WindowManager::RequestNewWindow(WindowDesc windowDesc)
	{
		std::shared_ptr<Window> window = std::make_shared<Window>();
		
		if (SUCCEEDED(window->CreateNewWindow(windowDesc)))
		{
			m_windows.emplace_back(std::move(window));
			++m_numWindows;

			return m_numWindows;
		}
		else
		{
			AC_String errorMsg = "Cannot Create Requested Window ";
			AC_String windowName = windowDesc.lpClassName;
			utils::Logger::LogInfo((errorMsg + windowName).c_str());
			return std::numeric_limits<uint32_t>::max();
		}

	}
	
	uint32_t WindowManager::RequestNewDefaultWindow(HINSTANCE hInstance, WndProcFunctor wndProcFunctor)
	{
		// Could be because both are unnamed, creating another unnamed object. Imagine passing these unnamed as function parameters;
		// these would not exist beyond the argument parentheses '()' in the function call
		// So, let's go:
		auto _windowName = (AC_STR_LITERAL("AnarchyWindow_") + AC_To_String(m_numWindows));
		WindowDesc param;
		param.dwExStyle = NULL;
		param.lpClassName = const_cast<AC_CharPtr>(_windowName.c_str());
		param.lpWindowName = const_cast<AC_CharPtr>(_windowName.c_str());
		param.dwStyle = WS_OVERLAPPEDWINDOW;
		param.x = 0;
		param.y = 0;
		param.width = 1024;
		param.height = 768;
		param.hWndParent = nullptr;
		param.hMenu = nullptr;
		param.hInstance = hInstance;
		param.messageProcedureFunctor = wndProcFunctor;
		param.lpParam = nullptr;

		std::shared_ptr<Window> window = std::make_shared<Window>();

		return RequestNewWindow(param);
	}
}