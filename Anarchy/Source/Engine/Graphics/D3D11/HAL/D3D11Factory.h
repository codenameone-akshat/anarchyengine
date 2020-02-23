#ifdef AC_D3D11

#ifndef _D3D11_FACTORY_H_
#define _D3D11_FACTORY_H_

#include <dxgi.h>

#include "../../../../Framework/Includes/FrameworkHeaders.h"
#include "../../../../Framework/Includes/FrameworkAliases.h"
#include "D3D11Hardware.h"

namespace anarchy::engine::graphics::hal
{
	class D3D11Factory
	{
	public:
		D3D11Factory() = default;
		~D3D11Factory() = default;
		
		inline framework::AC_ComPtr<IDXGIFactory>& GetRawFactory() { return m_factory; }
		inline void CreateSwapChain(std::shared_ptr<hal::D3D11Device> device, DXGI_SWAP_CHAIN_DESC& swapChainDesc, framework::AC_ComPtr<IDXGISwapChain>& swapChain)
		{
			framework::ComCheck(m_factory->CreateSwapChain(device->GetRawDevice().Get(), &swapChainDesc, &swapChain), "Failed to create D3D11 Device");
		}

		framework::AC_ComPtr<IDXGIAdapter> GetD3D11SupportedHardwareAdapter() const;

	private:
		uint32_t m_dxgiFactoryFlags = NULL;
		framework::AC_ComPtr<IDXGIFactory> m_factory = nullptr;
	};
}

#endif // _D3D11_FACTORY_H_

#endif // AC_D3D11