#ifndef _D3D12_DEVICE_H_
#define _D3D12_DEVICE_H_

#include <d3d12.h>

#include "../../../../Framework/Includes/FrameworkAliases.h"

namespace anarchy::engine::graphics::hal
{
	class D3D12Device
	{
	public:
		D3D12Device() = default;
		~D3D12Device() = default;

		inline framework::AC_ComPtr<ID3D12Device6>& GetRawDevice() { return m_device; }
		inline void SetRawDevice(framework::AC_ComPtr<ID3D12Device6> device) { m_device = device; }

	private:
		framework::AC_ComPtr<ID3D12Device6> m_device;
	};
}

#endif // _D3D12_DEVICE_H_
