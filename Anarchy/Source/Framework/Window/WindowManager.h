#ifndef _WINDOW_MANAGER_H_
#define _WINDOW_MANAGER_H_

#include <vector>
#include <memory>
#include <stdint.h>

#include "Window.h"
#include "../../Framework/Includes/FrameworkDefines.h"

namespace anarchy::framework
{
	class WindowManager
	{
	public:
		WindowManager() = default;
		~WindowManager() = default;

		//Returns Window Index in Vector.
		AC_NODISCARD uint32_t RequestNewWindow(WindowDesc windowDesc);
		AC_NODISCARD uint32_t RequestNewDefaultWindow(HINSTANCE hInstance, WndProcFunctor wndProcFunctor);
		
		AC_NODISCARD inline std::shared_ptr<Window> GetHandleToWindow(uint32_t index) { return m_windows[index]; } // @NS : Vector overflow check needed here?
		AC_NODISCARD inline WindowDesc& GetWindowDesc(uint32_t index) { return m_windowDescs[index]; } // @NS : Vector overflow check needed here?
		
		inline void ShowWindow(uint32_t index, int32_t showCmd) { m_windows[index]->ShowWindow(showCmd); } // @NS : Vector overflow check needed here?

	private:
		std::vector<std::shared_ptr<Window>> m_windows; // List of all windows for the engine
		std::vector<WindowDesc> m_windowDescs; // List of all window descriptions for the engine
		uint32_t m_numWindows = 0;
	};
}

#endif // _WINDOW_MANAGER_H_
