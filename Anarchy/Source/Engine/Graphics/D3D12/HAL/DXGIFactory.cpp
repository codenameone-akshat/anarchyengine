#include <d3d12.h>

#include "DXGIFactory.h"
#include "../../../../Framework/Includes/FrameworkGlobals.h"

namespace anarchy::engine::graphics::hal
{
	framework::AC_ComPtr<IDXGIAdapter4> DXGIFactory::GetD3D12SupportedHardwareAdapter() const
	{
		framework::AC_ComPtr<IDXGIAdapter4> hardwareAdapter;
		framework::AC_ComPtr<IDXGIAdapter1> hardwareAdapter1;

		auto enumAdapter = [&hardwareAdapter1](uint32_t adapterIdx, framework::AC_ComPtr<IDXGIFactory7> factory)
		{
			return (factory->EnumAdapters1(adapterIdx, &hardwareAdapter1) != DXGI_ERROR_NOT_FOUND);
		};
		
		uint32_t adapterIdx = 0;
		while(enumAdapter(adapterIdx++, m_factory))
		{
			DXGI_ADAPTER_DESC3 adapterDesc;

			framework::ComCheck(hardwareAdapter1.As(&hardwareAdapter), "Failed to cast IDXGIAdapter1 to IDXGIAdapter4.");

			framework::ComCheck(hardwareAdapter->GetDesc3(&adapterDesc), "Failed to Get DXGI Adapter Desc3.");

			if (adapterDesc.Flags & DXGI_ADAPTER_FLAG3_SOFTWARE) // Ignore Software Devices
				continue;

			if(SUCCEEDED(D3D12CreateDevice(hardwareAdapter.Get(), D3D_FEATURE_LEVEL_12_0, __uuidof(ID3D12Device), nullptr)))
				break; // Exit on first hardware device that supports D3D12
		}
		
		return hardwareAdapter;
	}
	
	framework::AC_ComPtr<IDXGISwapChain4> DXGIFactory::CreateSwapChain(framework::AC_ComPtr<ID3D12CommandQueue> commandQueue, HWND hWnd, const DXGI_SWAP_CHAIN_DESC1* desc, 
		const DXGI_SWAP_CHAIN_FULLSCREEN_DESC* fullscreenDesc, framework::AC_ComPtr<IDXGIOutput> restrictToOutput) const
	{
		framework::AC_ComPtr<IDXGISwapChain1> swapChain;
		framework::ComCheck(m_factory->CreateSwapChainForHwnd(commandQueue.Get(), hWnd, desc, fullscreenDesc, restrictToOutput.Get(), &swapChain), "Failed to create Swap Chain.");

		framework::AC_ComPtr<IDXGISwapChain4> outputSwapChain;
		framework::ComCheck(swapChain.As(&outputSwapChain), "Failed to cast IDXGISwapChain1 to IDXGISwapChain4.");

		return outputSwapChain;
	}
} 