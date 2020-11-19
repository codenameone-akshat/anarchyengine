#ifndef _WINDOW_XBC_H_
#define _WINDOW_XBC_H_

#include "Framework/ClassHelpers.h"
#include "Platform/Window/WindowDesc_Common.h"

namespace anarchy
{
	class WindowDesc : public WindowDesc_Common
	{
		WindowDesc();
		~WindowDesc() = default;
	};

	class Window_XCB
	{
		DECLARE_DEFAULT_CLASSMEMBERS(WindowCommon);

	public:
		void InitWindowParams(const WindowDesc& windowDesc) override;
		void CreateNewWindow() override;
		void ShowWindow() override;
		void DestroyWindow() override;
	};
}
#endif // !_WINDOW_XBC_H_
