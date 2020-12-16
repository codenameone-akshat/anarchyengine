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
		SetupDebugUI();
	}

	void ImGuiWrapper::SetupDebugUI()
	{
		static float f = 0.0f;
		static int counter = 0;
		static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
		static ImVec4 prim_color = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		static ImVec4 prim_pos = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);

		// Debug Menu
		ImGui::Begin("Debug Menu");
		ImGui::ColorEdit3("Clear Color", (float*)&clear_color); // Edit 3 floats representing a color
		EngineContext::SetClearColor(Vector4f(clear_color.x, clear_color.y, clear_color.z, clear_color.w));
		ImGui::NewLine();
		ImGui::ColorEdit3("Primitive Color", (float*)&prim_color); // Edit 3 floats representing a color
		EngineContext::SetPrimColor(Vector4f(prim_color.x, prim_color.y, prim_color.z, prim_color.w));
		ImGui::End();

		// Frame Stats
		ImGui::Begin("Stats", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
		ImGui::Text("%.3f ms", 1000.0f / ImGui::GetIO().Framerate);
		ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);
		ImGui::End();
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
