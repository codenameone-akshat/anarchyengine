#include "Framework/Includes/FrameworkHeaders.h"
#include "Framework/Platform/Platform.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	InitAnarchyPlatform_Windows(hInstance, hPrevInstance, lpCmdLine, nShowCmd);
	StartAnarchyEngine();
}