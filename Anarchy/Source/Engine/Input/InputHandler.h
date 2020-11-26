#ifndef _INPUT_H_
#define _INPUT_H_

#include <array>

namespace anarchy
{
#define KEY_SET_COMPARE_VAL 0x80

    // Shamelessly Copied from MS VK_XX ;)
    enum Key : uint32
    {
        // Mouse Input
		MOUSE_LBUTTON       = 0x01,
		MOUSE_RBUTTON       = 0x02,
		MOUSE_MBUTTON       = 0x04,

        // Keyboard keys (not exhaustive ;-))
        KEY_BACKSPACE       = 0x08, // Same as Unicode & Win32
        KEY_TAB             = 0x09, // Same as Unicode & Win32
        KEY_RETURN          = 0x0D, // Same as Unicode & Win32
        KEY_SHIFT           = 0x10, // Same as Unicode & Win32
        KEY_CTRL            = 0x11, // Same as Unicode & Win32
        KEY_ALT             = 0x12, // Same as Unicode & Win32
        KEY_PAUSE           = 0x13, // Same as Win32
        KEY_ESCAPE          = 0x1B, // Same as Unicode & Win32
        KEY_SPACE           = 0x20, // Same as Unicode & Win32
        KEY_PRIOR           = 0x21, // Same as Win32
        KEY_NEXT            = 0x22, // Same as Win32
        KEY_END             = 0x23, // Same as Win32
        KEY_HOME            = 0x24, // Same as Win32
        KEY_UP              = 0x26, // Same as Win32
        KEY_DOWN            = 0x28, // Same as Win32
        KEY_LEFT            = 0x25, // Same as Win32
        KEY_RIGHT           = 0x27, // Same as Win32
        KEY_INSERT          = 0x2D, // Same as Unicode & Win32
        KEY_DELETE          = 0x2E, // Same as Unicode & Win32

        KEY_0               = 0x30, // Same as ASCII & Win 32
        KEY_1               = 0x31, // Same as ASCII & Win 32
        KEY_2               = 0x32, // Same as ASCII & Win 32
        KEY_3               = 0x33, // Same as ASCII & Win 32
        KEY_4               = 0x34, // Same as ASCII & Win 32
        KEY_5               = 0x35, // Same as ASCII & Win 32
        KEY_6               = 0x36, // Same as ASCII & Win 32
        KEY_7               = 0x37, // Same as ASCII & Win 32
        KEY_8               = 0x38, // Same as ASCII & Win 32
        KEY_9               = 0x39, // Same as ASCII & Win 32

        KEY_DOT             = 0xBE,
        KEY_MINUS           = 0xBD,

        KEY_A               = 0x41, // Same as ASCII
        KEY_B               = 0x42, // Same as ASCII
        KEY_C               = 0x43, // Same as ASCII
        KEY_D               = 0x44, // Same as ASCII
        KEY_E               = 0x45, // Same as ASCII
        KEY_F               = 0x46, // Same as ASCII
        KEY_G               = 0x47, // Same as ASCII
        KEY_H               = 0x48, // Same as ASCII
        KEY_I               = 0x49, // Same as ASCII
        KEY_J               = 0x4A, // Same as ASCII
        KEY_K               = 0x4B, // Same as ASCII
        KEY_L               = 0x4C, // Same as ASCII
        KEY_M               = 0x4D, // Same as ASCII
        KEY_N               = 0x4E, // Same as ASCII
        KEY_O               = 0x4F, // Same as ASCII
        KEY_P               = 0x50, // Same as ASCII
        KEY_Q               = 0x51, // Same as ASCII
        KEY_R               = 0x52, // Same as ASCII
        KEY_S               = 0x53, // Same as ASCII
        KEY_T               = 0x54, // Same as ASCII
        KEY_U               = 0x55, // Same as ASCII
        KEY_V               = 0x56, // Same as ASCII
        KEY_W               = 0x57, // Same as ASCII
        KEY_X               = 0x58, // Same as ASCII
        KEY_Y               = 0x59, // Same as ASCII
        KEY_Z               = 0x5A, // Same as ASCII

        KEY_NUMPAD0         = 0x60,
        KEY_NUMPAD1         = 0x61,
        KEY_NUMPAD2         = 0x62,
        KEY_NUMPAD3         = 0x63,
        KEY_NUMPAD4         = 0x64,
        KEY_NUMPAD5         = 0x65,
        KEY_NUMPAD6         = 0x66,
        KEY_NUMPAD7         = 0x67,
        KEY_NUMPAD8         = 0x68,
        KEY_NUMPAD9         = 0x69,
        KEY_NUMPADDIV       = 0x6F,
        KEY_NUMPADMUL       = 0x6A,
        KEY_NUMPADMINUS     = 0x6D,
        KEY_NUMPADPLUS      = 0x6B,
        KEY_NUMPADDEC       = 0x6E,

        KEY_F1              = 0x70, // Same as Win32
        KEY_F2              = 0x71, // Same as Win32
        KEY_F3              = 0x72, // Same as Win32
        KEY_F4              = 0x73, // Same as Win32
        KEY_F5              = 0x74, // Same as Win32
        KEY_F6              = 0x75, // Same as Win32
        KEY_F7              = 0x76, // Same as Win32
        KEY_F8              = 0x77, // Same as Win32
        KEY_F9              = 0x78, // Same as Win32
        KEY_F10             = 0x79, // Same as Win32
        KEY_F11             = 0x7A, // Same as Win32
        KEY_F12             = 0x7B, // Same as Win32

        KEY_COLON           = 0xBA,
        KEY_SEMICOLON       = 0xBA,
        KEY_BACKSLASH       = 0xDC,
        KEY_SINGLEQUOTE     = 0xDE,
        KEY_SLASH           = 0xBF,
        KEY_GRAVE           = 0xC0, // '^' and '~'
        KEY_COMMA           = 0xBC,
        KEY_OPENINGBRACKET  = 0xDB,
        KEY_CLOSINGBRACKET  = 0xDD,
        KEY_APOSTROPHE      = 0xDE, // ''' and  '"'
        KEY_EQUAL           = 0xBB,

        KEY_SCROLLLOCK      = 0x7D
    };

    class InputHandler
    {
        using MousePosition = Vector2i;
        struct MouseState
        {
            MousePosition mousePosition = {};
            MousePosition mousePositionDelta = {};
        };

        DECLARE_DEFAULT_CLASSMEMBERS(InputHandler);

        void PollInputFromOS();

        inline bool GetIsKeyDown(Key key) const
        {
            return ((m_keyStates.at(key) & KEY_SET_COMPARE_VAL) > 0);
        }

        inline MousePosition GetMousePosition() const
        {
            return m_mouseState.mousePosition;
        }

        inline MousePosition GetMousePositionDelta() const
        {
            return m_mouseState.mousePositionDelta;
        }

        static InputHandler& GetInstance()
        {
            static InputHandler inputInstance;
            return inputInstance;
        }
        
    private:
        void PollKeyboardInput();
        void PollMouseInput();

        std::array<unsigned char, 256> m_keyStates = {};
        MouseState m_mouseState = {};
    };
}
#endif
