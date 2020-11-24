#ifdef AC_D3D12

#include <d3d12.h>

#include "D3D12Factory.h"
#include "Platform/ResultHelper.h"

namespace anarchy
{
    ComPtr<IDXGIAdapter4> D3D12Factory::GetD3D12SupportedHardwareAdapter() const
    {
        ComPtr<IDXGIAdapter4> hardwareAdapter;
        ComPtr<IDXGIAdapter1> hardwareAdapter1;

        auto enumAdapter = [&hardwareAdapter1](uint32 adapterIdx, ComPtr<IDXGIFactory7> factory)
        {
            return (factory->EnumAdapters1(adapterIdx, &hardwareAdapter1) != DXGI_ERROR_NOT_FOUND);
        };

        uint32 adapterIdx = 0;
        while (enumAdapter(adapterIdx++, m_factory))
        {
            DXGI_ADAPTER_DESC3 adapterDesc;

            CheckResult(hardwareAdapter1.As(&hardwareAdapter), "Failed to cast IDXGIAdapter1 to IDXGIAdapter4.");

            CheckResult(hardwareAdapter->GetDesc3(&adapterDesc), "Failed to Get DXGI Adapter Desc3.");

            if (adapterDesc.Flags & DXGI_ADAPTER_FLAG3_SOFTWARE) // Ignore Software Devices
                continue;

            if (SUCCEEDED(D3D12CreateDevice(hardwareAdapter.Get(), D3D_FEATURE_LEVEL_12_1, __uuidof(ID3D12Device), nullptr)))
                break; // Exit on first hardware device that supports D3D12
        }

        return hardwareAdapter;
    }

    ComPtr<IDXGISwapChain4> D3D12Factory::CreateSwapChain(ComPtr<ID3D12CommandQueue> commandQueue, const HWND hWnd, const DXGI_SWAP_CHAIN_DESC1* desc,
        const DXGI_SWAP_CHAIN_FULLSCREEN_DESC* fullscreenDesc, ComPtr<IDXGIOutput> restrictToOutput) const
    {
        ComPtr<IDXGISwapChain1> swapChain;
        CheckResult(m_factory->CreateSwapChainForHwnd(commandQueue.Get(), hWnd, desc, fullscreenDesc, restrictToOutput.Get(), &swapChain), "Failed to create Swap Chain.");

        ComPtr<IDXGISwapChain4> outputSwapChain;
        CheckResult(swapChain.As(&outputSwapChain), "Failed to cast IDXGISwapChain1 to IDXGISwapChain4.");

        return outputSwapChain;
    }
}

#endif // AC_D3D12