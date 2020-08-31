#include "InputHandler.h"
#include "Framework/App/AppContext.h"
#include "Framework/Includes/FrameworkHeaders.h"

namespace anarchy
{
    void InputHandler::PollInputFromOS()
    {
        HWND hwnd = AppContext::GetHandleToActiveWindow()->GetRawHandleToWindow();

        // Only update when anarchy window is in the view
        if (hwnd != NULL && ::GetForegroundWindow() != hwnd)
            return;
        
        PollKeyboardInput();
        PollMouseInput();
    }

    void InputHandler::PollKeyboardInput()
    {
        ::GetKeyboardState(m_keyStates.data());
    }

    void InputHandler::PollMouseInput()
    {
        POINT currentMousePos = {};
        ::GetCursorPos(&currentMousePos);
        
        m_mouseState.mousePositionDelta.x = currentMousePos.x - m_mouseState.mousePosition.x;
        m_mouseState.mousePositionDelta.y = currentMousePos.y - m_mouseState.mousePosition.y;

        m_mouseState.mousePosition.x = currentMousePos.x;
        m_mouseState.mousePosition.y = currentMousePos.y;
    }
}