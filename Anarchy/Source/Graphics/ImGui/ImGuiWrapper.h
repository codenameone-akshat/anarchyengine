#ifndef _IMGUI_WRAPPER_H_
#define _IMGUI_WRAPPER_H_

#include "Framework/ClassHelpers.h"

namespace anarchy
{
	class ImGuiWrapper final
	{
		DECLARE_DEFAULT_CLASSMEMBERS(ImGuiWrapper);
	public:
		void InitializeImGui();
	};
}

#endif // _IMGUI_WRAPPER_H_
