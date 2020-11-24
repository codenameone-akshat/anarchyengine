#ifdef AC_D3D12

#ifndef _DXGI_FACTORY_H_
#define _DXGI_FACTORY_H_

#include <dxgi1_6.h>

#include "Platform/Types/Types.h"

namespace anarchy
{
    class D3D12Factory
    {
    public:
        D3D12Factory() = default;
        ~D3D12Factory() = default;

        inline void SetDXGIFactoryFlags(const uint32 flags) { m_dxgiFactoryFlags = flags; }
        inline void ClearDXGIFactoryFlags(const uint32 flags) { m_dxgiFactoryFlags = NULL; }
        inline void AppendDXGIFactoryFlags(const uint32 flags) { m_dxgiFactoryFlags |= flags; }
        inline uint32 GetDXGIFactoryFlags() const { return m_dxgiFactoryFlags; }

        inline ComPtr<IDXGIFactory7>& GetRawFactory() { return m_factory; }

        ComPtr<IDXGIAdapter4> GetD3D12SupportedHardwareAdapter() const;

        ComPtr<IDXGISwapChain4> CreateSwapChain(ComPtr<ID3D12CommandQueue> commandQueue, const HWND hWnd, const DXGI_SWAP_CHAIN_DESC1* desc,
            const DXGI_SWAP_CHAIN_FULLSCREEN_DESC* fullscreenDesc, ComPtr<IDXGIOutput> restrictToOutput) const;

    private:
        uint32_t m_dxgiFactoryFlags = NULL;
        ComPtr<IDXGIFactory7> m_factory = nullptr;
    };
}

#endif // _DXGI_FACTORY_H_

#endif // AC_D3D12