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

		inline void SetDXGIFactoryFlags(uint32_t flags) { m_dxgiFactoryFlags = flags; }
		inline void ClearDXGIFactoryFlags(uint32_t flags) { m_dxgiFactoryFlags = NULL; }
		inline void AppendDXGIFactoryFlags(uint32_t flags) { m_dxgiFactoryFlags |= flags; }
		inline uint32_t GetDXGIFactoryFlags() { return m_dxgiFactoryFlags; }

		inline framework::AC_ComPtr<IDXGIFactory7>& GetRawFactory() { return m_factory; }

		framework::AC_ComPtr<IDXGIAdapter4> GetD3D12SupportedHardwareAdapter() const;

	private:
		uint32_t m_dxgiFactoryFlags = NULL;
		framework::AC_ComPtr<IDXGIFactory7> m_factory = nullptr;
	};
}

#endif // _DXGI_FACTORY_H_
