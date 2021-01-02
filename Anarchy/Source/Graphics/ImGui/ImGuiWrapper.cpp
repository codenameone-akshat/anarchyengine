#include "acpch.h"

#ifdef AC_D3D12
#include <d3d12.h>
#endif // AC_D3D12

#include "ImGuiWrapper.h"
#include "Graphics/ImGui/imgui.h"
#include "Engine/Core/EngineContext.h"
#include "Graphics/ImGui/Windows/imgui_impl_win32.h"
#include "Graphics/ImGui/D3D12/imgui_impl_dx12.h"

namespace anarchy
{
	void ImGuiWrapper::InitializeImGuiLib()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui::StyleColorsDark();
	}

	void ImGuiWrapper::InitializeImGuiWindowsD3D12(HWND mainWindowHandle, ComPtr<ID3D12Device> device, int numFramesInFlight, DXGI_FORMAT rtvFormat, ComPtr<ID3D12DescriptorHeap> srvHeap, D3D12_CPU_DESCRIPTOR_HANDLE fontSRV_CPUDescHandle, D3D12_GPU_DESCRIPTOR_HANDLE fontSRV_GPUDescHandle)
	{
		ImGui_ImplWin32_Init(mainWindowHandle);
#ifdef AC_D3D12
		ImGui_ImplDX12_Init(device.Get(), numFramesInFlight, rtvFormat, srvHeap.Get(), fontSRV_CPUDescHandle, fontSRV_GPUDescHandle);
#endif // AC_D3D12
	}

	void ImGuiWrapper::NewFrame()
	{
#ifdef AC_D3D12
		ImGui_ImplDX12_NewFrame();
#endif // AC_D3D12
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiWrapper::Render(ComPtr<ID3D12GraphicsCommandList>& graphicsCommandlist)
	{
		ImGui::Render();
#ifdef AC_D3D12
		ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), graphicsCommandlist.Get());
#endif // AC_D3D12
	}

	void ImGuiWrapper::InvalidateResources()
	{
#ifdef AC_D3D12
		ImGui_ImplDX12_InvalidateDeviceObjects();
#endif // AC_D3D12
	}

	void ImGuiWrapper::RecreateResources()
	{
#ifdef AC_D3D12
#endif // AC_D3D12
	}

	void ImGuiWrapper::Shutdown()
	{
#ifdef AC_D3D12
		ImGui_ImplDX12_Shutdown();
#endif // AC_D3D12
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();
	}
}
