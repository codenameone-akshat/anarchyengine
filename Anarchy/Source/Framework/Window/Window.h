#ifndef _WINDOW_H_	
#define _WINDOW_H_

#include <functional>

#include "../../Framework/Includes/FrameworkHeaders.h"
#include "../../Framework/Includes/FrameworkAliases.h"
#include "../../Framework/Includes/FrameworkDefines.h"
#include "../../Framework/Includes/FrameworkGlobals.h"

namespace anarchy::framework
{
	// Functor Alias for Window Message Procedures | For More Readability 
	// Idea Credits : NishantSingh.
	typedef LRESULT(CALLBACK* WndProcFunctor)(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	struct WindowDesc // Structure for Window Descriptor to setup Window
	{
		uint32_t dwExStyle = NULL;
		AC_CharPtr lpClassName = const_cast<AC_CharPtr>(AC_Str_Default);
		AC_CharPtr lpWindowName = const_cast<AC_CharPtr>(AC_Str_Default);
		uint32_t dwStyle = NULL;
		int32_t x = 0;
		int32_t y = 0;
		int32_t width = 0;
		int32_t height = 0;
		HWND hWndParent = nullptr;
		HMENU hMenu = nullptr;
		HINSTANCE hInstance = nullptr;
		AC_VoidPtr lpParam = nullptr;
		WndProcFunctor messageProcedureFunctor = nullptr;
	};

	class Window
	{
	public:
		Window() = default;
		~Window();

		inline HWND GetRawHandleToWindow() { return m_hWnd; }
		inline void SetRawHandleToWindow(HWND hWnd) { m_hWnd = hWnd; }
		inline void ShowWindow(int32_t showCmd) { ::ShowWindow(m_hWnd, showCmd); }
		HRESULT CreateNewWindow(WindowDesc windowParams);

	private:
		void RegisterClassInternal();
		void CreateWindowInternal();

	private:
		WindowDesc m_wndDesc;
		HWND m_hWnd = nullptr;
		WNDCLASSEX m_wndClass = { };
		WndProcFunctor m_messageProcedureFunctor = nullptr;
	};
}

#endif // _WINDOW_H_