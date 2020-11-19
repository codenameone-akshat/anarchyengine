#ifdef AC_D3D12
#include <d3d12.h>
#endif // AC_D3D12

#include "ImGuiWrapper.h"
#include "Graphics/ImGui/imgui.h"
#include "Engine/Core/EngineContext.h"
#include "Framework/Math/Vector/Vec4.hpp"
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
		ImGui_ImplDX12_Init(device.Get(), numFramesInFlight, rtvFormat, srvHeap.Get(), fontSRV_CPUDescHandle, fontSRV_GPUDescHandle);
	}

	void ImGuiWrapper::NewFrame()
	{
		ImGui_ImplDX12_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
		SetupDebugUI();
	}

	void ImGuiWrapper::SetupDebugUI()
	{
		static float f = 0.0f;
		static int counter = 0;
		static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

		ImGui::Begin("Debug Menu");                          // Create a window called "Hello, world!" and append into it.

		ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color
		EngineContext::SetClearColor(math::Vec4<float>(clear_color.x, clear_color.y, clear_color.z, clear_color.w));
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

	void ImGuiWrapper::Render(ComPtr<ID3D12GraphicsCommandList>& graphicsCommandlist)
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
