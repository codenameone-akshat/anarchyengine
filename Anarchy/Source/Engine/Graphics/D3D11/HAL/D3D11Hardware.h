#ifdef AC_D3D11

#ifndef _D3D11_HARDWARE_H_
#define _D3D11_HARDWARE_H_

#include <d3d11.h>
#include <dxgi.h>

#include "../../../../Framework/Includes/FrameworkAliases.h"
#include "../../../../Framework/Includes/FrameworkGlobals.h"

namespace anarchy
{
	class D3D11Adapter
	{
	public:
		D3D11Adapter() = default;
		~D3D11Adapter() = default;

		inline IDXGIAdapter* GetRawAdapter() const { return m_hardwareAdapter.Get(); }
		inline AC_ComPtr<IDXGIAdapter> GetAdapter() { return m_hardwareAdapter; }
		inline void SetAdapter(AC_ComPtr<IDXGIAdapter> adapter) { m_hardwareAdapter = adapter; }

	private:
		AC_ComPtr<IDXGIAdapter> m_hardwareAdapter;
	};


	class D3D11Device
	{
	public:
		D3D11Device() = default;
		~D3D11Device() = default;

		inline AC_ComPtr<ID3D11Device>& GetRawDevice() { return m_device; }
		inline void SetRawDevice(AC_ComPtr<ID3D11Device> device) { m_device = device; }
		
		inline AC_ComPtr<ID3D11DeviceContext>& GetImmediateContext()
		{
			if (!m_immediateContext)
				m_device->GetImmediateContext(&m_immediateContext);
			
			return m_immediateContext;
		}
		
		inline void CreateImmediateContext() 
		{
			if (!m_immediateContext)
				m_device->GetImmediateContext(&m_immediateContext);
		}

		inline AC_ComPtr<ID3D11DeviceContext>& GetDeferredContext() { return m_deferredContext; }
		inline void CreateDefferedContext() { m_device->CreateDeferredContext(NULL, &m_deferredContext); }
		inline void CreateRenderTargetView(AC_ComPtr<ID3D11Resource>& backBuffer, const D3D11_RENDER_TARGET_VIEW_DESC* rtvDesc, AC_ComPtr<ID3D11RenderTargetView>& renderTargetView)
		{
			ComCheck(m_device->CreateRenderTargetView(backBuffer.Get(), rtvDesc, renderTargetView.GetAddressOf()), "Failed To Create Render Target View");
		}

		inline void SetDeviceFlags(const uint32_t flags) { m_deviceFlags = flags; }
		inline void ClearDeviceFlags(const uint32_t flags) { m_deviceFlags = NULL; }
		inline void AppendDeviceFlags(const uint32_t flags) { m_deviceFlags |= flags; }
		inline uint32_t GetDeviceFlags() const { return m_deviceFlags; }

	private:
		AC_ComPtr<ID3D11Device> m_device = nullptr;
		AC_ComPtr<ID3D11DeviceContext> m_immediateContext = nullptr;
		AC_ComPtr<ID3D11DeviceContext> m_deferredContext = nullptr;

		uint32_t m_deviceFlags = NULL;
	};
}

#endif // _D3D11_HARDWARE_H_

#endif // AC_D3D11