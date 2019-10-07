#ifndef _D3D12_ADAPTER_H_
#define _D3D12_ADAPTER_H_

#include <dxgi1_6.h>

#include "../../../../Framework/Includes/FrameworkAliases.h"

namespace anarchy::engine::graphics::hal
{
	class DXGIAdapter
	{
	public:
		DXGIAdapter() = default;
		~DXGIAdapter() = default;

		inline IDXGIAdapter4* GetRawAdapter() { return m_hardwareAdapter.Get(); }
		inline framework::AC_ComPtr<IDXGIAdapter4> GetAdapter() { return m_hardwareAdapter; }
		inline void SetAdapter(framework::AC_ComPtr<IDXGIAdapter4> adapter) { m_hardwareAdapter = adapter; }

	private:
		framework::AC_ComPtr<IDXGIAdapter4> m_hardwareAdapter;
	};
}

#endif // _D3D12_ADAPTER_H_