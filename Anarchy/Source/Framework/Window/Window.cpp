#include "Window.h"
#include "Framework/Includes/FrameworkGlobals.h"

namespace anarchy
{
    Window::~Window()
    {
        ::DestroyWindow(m_hWnd);
        ::UnregisterClass(m_wndClass.lpszClassName, m_wndClass.hInstance);
    }

    HRESULT Window::CreateNewWindow(WindowDesc windowParams)
    {
        m_wndDesc = windowParams;
        RegisterClassInternal();
        CreateWindowInternal();
        AC_Assert(m_hWnd, "Handle to window (hWnd) NULL After Attempting to create a window.");

        return S_OK;
    }

    void Window::RegisterClassInternal()
    {
        ::ZeroMemory(&m_wndClass, sizeof(WNDCLASSEX));

        m_wndClass.cbSize = sizeof(WNDCLASSEX);
        m_wndClass.hInstance = m_wndDesc.hInstance;
        m_wndClass.style = CS_HREDRAW | CS_VREDRAW;
        m_wndClass.lpszClassName = m_wndDesc.lpClassName;
        m_wndClass.hCursor = ::LoadCursor(nullptr, IDC_ARROW);
        m_wndClass.lpfnWndProc = m_wndDesc.messageProcedureFunctor;
        m_messageProcedureFunctor = m_wndDesc.messageProcedureFunctor;

        ::RegisterClassEx(&m_wndClass);
    }

    void Window::CreateWindowInternal()
    {
        m_hWnd = CreateWindowEx(m_wndDesc.dwExStyle, m_wndDesc.lpClassName, m_wndDesc.lpWindowName, m_wndDesc.dwStyle,
            m_wndDesc.x, m_wndDesc.y, m_wndDesc.width, m_wndDesc.height, m_wndDesc.hWndParent, m_wndDesc.hMenu,
            m_wndDesc.hInstance, m_wndDesc.lpParam);
        auto error = ::GetLastError();
    }
}