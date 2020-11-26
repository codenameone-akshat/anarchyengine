#ifndef _WINDOW_EVENT_HANDLER_WINDOWS_H_
#define _WINDOW_EVENT_HANDLER_WINDOWS_H_

namespace anarchy
{
	class WindowEventHandler_Windows
	{
		DECLARE_DEFAULT_CLASSMEMBERS(WindowEventHandler_Windows);

	public:
		void Initialize();
		void PollMessage();
		void HandleMessage(WindowEvent event);
	};
}
#endif // !_WINDOW_EVENT_HANDLER_WINDOWS_H_

