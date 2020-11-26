#ifndef _WINDOW_WINDOWS_H_
#define _WINDOW_WINDOWS_H_

#include <windows.h>

#include "Platform/Window/WindowDesc_Common.h"

namespace anarchy
{
	// Functor Alias for Window Message Procedures | For More Readability 
	typedef LRESULT(CALLBACK* MessageHandlerFunctor)(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	struct WindowDesc : public WindowDesc_Common
	{
		WindowDesc();
		~WindowDesc() = default;

		string className = "";
		uint32 dwExStyle = NULL;
		uint32 dwStyle = NULL;
		HWND hWndParent = nullptr;
		HMENU hMenu = nullptr;
		HINSTANCE hInstance = nullptr;
		voidptr lpParam = nullptr;
	};

	class Window_Windows
	{
		DECLARE_DEFAULT_CLASSMEMBERS(Window_Windows);

	public:
		void InitWindowParams(const WindowDesc& windowDesc = {});
		void CreateNewWindow();
		void ShowWindow();
		void DestroyWindow();

		inline HWND GetRawHandleToWindow() const { return m_rawWindowHandle; }
		inline void SetRawHandleToWindow(HWND windowHandle) { m_rawWindowHandle = m_rawWindowHandle; }

		inline WindowDesc GetWindowDesc() const { return m_windowDesc; }
		inline void SetWindowDesc(const WindowDesc& windowDesc) { m_windowDesc = windowDesc; }

		inline void SetMessageProcedureFunctor(MessageHandlerFunctor messageHandler) { m_messageHandlerFunctor = messageHandler; }
	
	private:
		void RegisterClassInternal();
		void CreateWindowInternal();

		WindowDesc m_windowDesc;
		HWND m_rawWindowHandle = nullptr;
		WNDCLASSEX m_windowClass = { };
		MessageHandlerFunctor m_messageHandlerFunctor = nullptr;
	};

	static LRESULT CALLBACK MessageHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
}

#endif _WINDOW_WINDOWS_H_
