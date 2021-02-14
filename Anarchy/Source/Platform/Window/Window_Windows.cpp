#include "acpch.h"

#include "Window_Windows.h"
#include "Platform/Assertion.h"
#include "Framework/AppContext.h"
#include "Utils/StringUtils/StringUtils.h"

namespace anarchy
{
	WindowDesc::WindowDesc()
		:WindowDesc_Common({ "AnarchyWindow", 0, 0, 1024, 768 }),
		dwExStyle(NULL),
		className("AnarchyWindow"),
		dwStyle(WS_OVERLAPPEDWINDOW),
		hWndParent(nullptr),
		hMenu(nullptr),
		lpParam(nullptr)
	{
		hInstance = AppContext::GetMainParams().hInstance;
	}

	//-----------------------------Window-----------------------------------

	void Window_Windows::InitWindowParams(const WindowDesc& windowDesc)
	{
		m_windowDesc = windowDesc;
	}

	void Window_Windows::CreateNewWindow()
	{
		RegisterClassInternal();
		CreateWindowInternal();
		Assert(m_rawWindowHandle, "Handle to window (hWnd) NULL After Attempting to create a window.");
	}

	void Window_Windows::ShowWindow()
	{
		::ShowWindow(m_rawWindowHandle, SW_SHOWDEFAULT);
		auto error = ::GetLastError();
	}

	void Window_Windows::DestroyWindow()
	{
		::DestroyWindow(m_rawWindowHandle);
		::UnregisterClass(m_windowClass.lpszClassName, m_windowClass.hInstance);
	}

	RECT Window_Windows::GetWindowRect()
	{
		RECT rect;
		::GetWindowRect(m_rawWindowHandle, &rect);
		return rect;
	}

	void Window_Windows::RegisterClassInternal()
	{
		Assert(m_messageHandlerFunctor != nullptr, "Message Handler Functor (WndProc) is nullptr. Please specify the functor.");
		::ZeroMemory(&m_windowClass, sizeof(WNDCLASSEX));

		m_windowClass.cbSize = sizeof(WNDCLASSEX);
		m_windowClass.hInstance = m_windowDesc.hInstance;
		m_windowClass.style = CS_HREDRAW | CS_VREDRAW;
		m_windowClass.lpszClassName = m_windowDesc.className.c_str();
		m_windowClass.hCursor = ::LoadCursor(nullptr, IDC_ARROW);
		m_windowClass.lpfnWndProc = m_messageHandlerFunctor;

		::RegisterClassEx(&m_windowClass);
	}

	void Window_Windows::CreateWindowInternal()
	{
		m_rawWindowHandle = ::CreateWindowEx(m_windowDesc.dwExStyle, m_windowDesc.className.c_str(), m_windowDesc.windowName.c_str(), m_windowDesc.dwStyle,
			m_windowDesc.x, m_windowDesc.y, m_windowDesc.width, m_windowDesc.height, m_windowDesc.hWndParent, m_windowDesc.hMenu,
			m_windowDesc.hInstance, m_windowDesc.lpParam);
		auto error = ::GetLastError();
	}
}
