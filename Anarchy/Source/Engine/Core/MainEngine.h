#ifndef _MAIN_ENGINE_H_
#define _MAIN_ENGINE_H_

#include "Framework/Includes/FrameworkHeaders.h"

// Everything Starts Here

namespace anarchy
{
	void EngineMain();
	void PollMessage();

	static LRESULT CALLBACK MainEngineWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
}

#endif // _MAIN_ENGINE_H_
