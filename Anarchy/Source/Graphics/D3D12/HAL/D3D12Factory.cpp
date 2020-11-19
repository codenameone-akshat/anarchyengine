#ifdef AC_D3D12

#include <d3d12.h>

#include "D3D12Factory.h"
#include "Framework/FrameworkGlobals.h"

namespace anarchy
{
    AC_ComPtr<IDXGIAdapter4> D3D12Factory::GetD3D12SupportedHardwareAdapter() const
    {
        AC_ComPtr<IDXGIAdapter4> hardwareAdapter;
        AC_ComPtr<IDXGIAdapter1> hardwareAdapter1;

        auto enumAdapter = [&hardwareAdapter1](uint32_t adapterIdx, AC_ComPtr<IDXGIFactory7> factory)
        {
            return (factory->EnumAdapters1(adapterIdx, &hardwareAdapter1) != DXGI_ERROR_NOT_FOUND);
        };

        uint32_t adapterIdx = 0;
        while (enumAdapter(adapterIdx++, m_factory))
        {
            DXGI_ADAPTER_DESC3 adapterDesc;

            ComCheck(hardwareAdapter1.As(&hardwareAdapter), "Failed to cast IDXGIAdapter1 to IDXGIAdapter4.");

            ComCheck(hardwareAdapter->GetDesc3(&adapterDesc), "Failed to Get DXGI Adapter Desc3.");

            if (adapterDesc.Flags & DXGI_ADAPTER_FLAG3_SOFTWARE) // Ignore Software Devices
                continue;

            if (SUCCEEDED(D3D12CreateDevice(hardwareAdapter.Get(), D3D_FEATURE_LEVEL_12_1, __uuidof(ID3D12Device), nullptr)))
                break; // Exit on first hardware device that supports D3D12
        }

        return hardwareAdapter;
    }

    AC_ComPtr<IDXGISwapChain4> D3D12Factory::CreateSwapChain(AC_ComPtr<ID3D12CommandQueue> commandQueue, const HWND hWnd, const DXGI_SWAP_CHAIN_DESC1* desc,
        const DXGI_SWAP_CHAIN_FULLSCREEN_DESC* fullscreenDesc, AC_ComPtr<IDXGIOutput> restrictToOutput) const
    {
        AC_ComPtr<IDXGISwapChain1> swapChain;
        ComCheck(m_factory->CreateSwapChainForHwnd(commandQueue.Get(), hWnd, desc, fullscreenDesc, restrictToOutput.Get(), &swapChain), "Failed to create Swap Chain.");

        AC_ComPtr<IDXGISwapChain4> outputSwapChain;
        ComCheck(swapChain.As(&outputSwapChain), "Failed to cast IDXGISwapChain1 to IDXGISwapChain4.");

        return outputSwapChain;
    }
}

#endif // AC_D3D12