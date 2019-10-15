#ifndef _DXGI_FACTORY_H_
#define _DXGI_FACTORY_H_

#include <dxgi1_6.h>

#include "../../../../Framework/Includes/FrameworkHeaders.h"
#include "../../../../Framework/Includes/FrameworkAliases.h"

namespace anarchy::engine::graphics::hal
{
	class DXGIFactory
	{
	public:
		DXGIFactory() = default;
		~DXGIFactory() = default;

		inline void SetDXGIFactoryFlags(const uint32_t flags) { m_dxgiFactoryFlags = flags; }
		inline void ClearDXGIFactoryFlags(const uint32_t flags) { m_dxgiFactoryFlags = NULL; }
		inline void AppendDXGIFactoryFlags(const uint32_t flags) { m_dxgiFactoryFlags |= flags; }
		inline uint32_t GetDXGIFactoryFlags() const { return m_dxgiFactoryFlags; }

		inline framework::AC_ComPtr<IDXGIFactory7>& GetRawFactory() { return m_factory; }

		framework::AC_ComPtr<IDXGIAdapter4> GetD3D12SupportedHardwareAdapter() const;
		
		framework::AC_ComPtr<IDXGISwapChain4> CreateSwapChain(framework::AC_ComPtr<ID3D12CommandQueue> commandQueue, const HWND hWnd, const DXGI_SWAP_CHAIN_DESC1* desc,
			const DXGI_SWAP_CHAIN_FULLSCREEN_DESC* fullscreenDesc, framework::AC_ComPtr<IDXGIOutput> restrictToOutput) const;

	private:
		uint32_t m_dxgiFactoryFlags = NULL;
		framework::AC_ComPtr<IDXGIFactory7> m_factory = nullptr;
	};
}

#endif // _DXGI_FACTORY_H_
