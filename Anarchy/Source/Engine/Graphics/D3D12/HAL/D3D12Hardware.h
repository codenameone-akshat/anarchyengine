#ifndef _D3D12_HARDWARE_H_
#define _D3D12_HARDWARE_H_

#include <d3d12.h>
#include <dxgi1_6.h>

#include "../../../../Framework/Includes/FrameworkAliases.h"
#include "../../../../Framework/Includes/FrameworkGlobals.h"

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


	class D3D12Device
	{
	public:
		D3D12Device() = default;
		~D3D12Device() = default;

		inline framework::AC_ComPtr<ID3D12Device6>& GetRawDevice() { return m_device; }
		inline void SetRawDevice(framework::AC_ComPtr<ID3D12Device6> device) { m_device = device; }
		inline void CreateCommandQueue(D3D12_COMMAND_QUEUE_DESC desc, framework::AC_ComPtr<ID3D12CommandQueue>& commandQueue)
		{
			framework::ComCheck(m_device->CreateCommandQueue(&desc, IID_PPV_ARGS(&commandQueue)), "Failed to Create Requested Command Queue.");
		}

	private:
		framework::AC_ComPtr<ID3D12Device6> m_device;
	};
}

#endif // _D3D12_HARDWARE_H_