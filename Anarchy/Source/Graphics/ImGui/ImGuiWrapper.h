#ifndef _IMGUI_WRAPPER_H_
#define _IMGUI_WRAPPER_H_

#include "Platform/PlatformConfig.h"

#ifdef PLATFORM_WINDOWS
#include <windows.h>
#endif // PLATFORM_WINDOWS

namespace anarchy
{
	class ImGuiWrapper final
	{
		DECLARE_DEFAULT_CLASSMEMBERS(ImGuiWrapper);
	public:

		void InitializeImGuiLib();

#if defined(PLATFORM_WINDOWS) && defined (AC_D3D12)
		void InitializeImGuiWindowsD3D12(HWND mainWindowHandle, ComPtr<ID3D12Device> device, int numFramesInFlight, DXGI_FORMAT rtvFormat, ComPtr<ID3D12DescriptorHeap> srvHeap, D3D12_CPU_DESCRIPTOR_HANDLE fontSRV_CPUDescHandle, D3D12_GPU_DESCRIPTOR_HANDLE fontSRV_GPUDescHandle);
		void NewFrame();
		void SetupDebugUI(); // TODO: Move this to the game project later
		void Render(ComPtr<ID3D12GraphicsCommandList>& graphicsCommandlist);
		void InvalidateResources();
		void RecreateResources();
		void Shutdown();
#endif // PLATFORM_WINDOWS && AC_D3D12
	};
}

#endif // _IMGUI_WRAPPER_H_
