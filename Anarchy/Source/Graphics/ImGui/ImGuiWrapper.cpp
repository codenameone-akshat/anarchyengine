#ifdef AC_D3D12
#include <d3d12.h>
#endif // AC_D3D12

#include "ImGuiWrapper.h"
#include "Graphics/ImGui/imgui.h"
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

	void ImGuiWrapper::InitializeImGuiWindowsD3D12(HWND mainWindowHandle, ID3D12Device* device, int numFramesInFlight, DXGI_FORMAT rtvFormat, ID3D12DescriptorHeap* CBVSRVHeap, D3D12_CPU_DESCRIPTOR_HANDLE fontSRV_CPUDescHandle, D3D12_GPU_DESCRIPTOR_HANDLE fontSRV_GPUDescHandle)
	{
		ImGui_ImplWin32_Init(mainWindowHandle);
		ImGui_ImplDX12_Init(device, numFramesInFlight, rtvFormat, CBVSRVHeap, fontSRV_CPUDescHandle, fontSRV_GPUDescHandle);
	}

	void ImGuiWrapper::NewFrame()
	{
		ImGui_ImplDX12_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
	}
	
	void ImGuiWrapper::SetupDebugUI()
	{
	}
	
	void ImGuiWrapper::Render(ComPtr<ID3D12GraphicsCommandList> graphicsCommandlist)
	{
		ImGui::Render();
		ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), graphicsCommandlist.Get());
	}
	
	void ImGuiWrapper::Shutdown()
	{
		ImGui_ImplDX12_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();
	}
}
