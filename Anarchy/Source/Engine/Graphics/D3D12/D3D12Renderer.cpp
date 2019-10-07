#include "D3D12Renderer.h"
#include "../../../Utils/Logger/Logger.h"
#include "../../../Framework/Includes/FrameworkAliases.h"
#include "../../../Framework/Includes/FrameworkGlobals.h"

namespace anarchy::engine::graphics
{
	void D3D12Renderer::Initialize()
	{
#ifdef AC_DEBUG
		EnableDebugLayer();
#endif AC_DEBUG

		CreateDevice();
	}

#ifdef AC_DEBUG
	// Should be the first step.
	void D3D12Renderer::EnableDebugLayer()
	{
		framework::AC_ComPtr<ID3D12Debug> debugController;
		auto size = sizeof(debugController);
		if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
		{
			debugController->EnableDebugLayer();

			m_factory->AppendDXGIFactoryFlags(DXGI_CREATE_FACTORY_DEBUG);
		}
	}
#endif AC_DEBUG

	void D3D12Renderer::CreateDevice()
	{
		framework::ComCheck(CreateDXGIFactory2(m_factory->GetDXGIFactoryFlags(), IID_PPV_ARGS(&(m_factory->GetRawFactory()))), "Failed to Create DXGIFactory.");
		m_adapter->SetAdapter(m_factory->GetD3D12SupportedHardwareAdapter());
		framework::ComCheck(D3D12CreateDevice(m_adapter->GetAdapter().Get(), g_MinFeatureLevel, IID_PPV_ARGS(&(m_device->GetRawDevice()))), "Failed to create D3D12Device.");
	}
}