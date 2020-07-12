#ifdef AC_D3D11

#include "D3D11Renderer.h"
#include "../../Core/EngineContext.h"

namespace anarchy
{
	void D3D11Renderer::Initialize()
	{
		InitializeAPI();
	}

	void D3D11Renderer::UpdateSingleThreaded()
	{
	}

	void D3D11Renderer::Destruct()
	{
	}
	
	void D3D11Renderer::InitializeAPI()
	{
		CreateAdapterAndFactory();
		CreateDevice();
		CreateSwapChain();
		CreateRenderTargetView();
	}

	void D3D11Renderer::CreateAdapterAndFactory()
	{
		ComCheck(CreateDXGIFactory(IID_PPV_ARGS(&(m_factory->GetRawFactory()))), "Failed to Create DXGIFactory.");
		m_adapter->SetAdapter(m_factory->GetD3D11SupportedHardwareAdapter());
	}
	
	void D3D11Renderer::CreateDevice()
	{
#ifdef AC_DEBUG
		m_device->AppendDeviceFlags(D3D11_CREATE_DEVICE_DEBUG);
#endif // AC_DEBUG

		std::array<D3D_FEATURE_LEVEL, 2> featureLevels{ D3D_FEATURE_LEVEL_11_1, D3D_FEATURE_LEVEL_11_0 };

		ComCheck(D3D11CreateDevice(m_adapter->GetAdapter().Get(), D3D_DRIVER_TYPE_UNKNOWN, NULL, m_device->GetDeviceFlags(), featureLevels.data(), static_cast<uint32_t>(featureLevels.size()),
			D3D11_SDK_VERSION, &m_device->GetRawDevice(), nullptr, nullptr), "Failed to create D3D11 Device");

		m_device->CreateImmediateContext();
		m_device->CreateDefferedContext();
		
	}

	void D3D11Renderer::CreateSwapChain()
	{
		DXGI_SWAP_CHAIN_DESC swapChainDesc = {};

		swapChainDesc.BufferDesc.Width = NULL; // Get automatically from hWND
		swapChainDesc.BufferDesc.Height = NULL; // Get automatically from hWND
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = g_numFrameBuffers;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		swapChainDesc.OutputWindow = AppContext::GetHandleToActiveWindow()->GetRawHandleToWindow();
		swapChainDesc.Windowed = true;

		m_factory->CreateSwapChain(m_device, swapChainDesc, m_swapChain);
	}
	
	void D3D11Renderer::CreateRenderTargetView()
	{
		for(uint_fast32_t itr = 0; itr < g_numFrameBuffers; ++itr)
		{
			ComCheck(m_swapChain->GetBuffer(itr, IID_PPV_ARGS(&(m_renderTargets.at(itr)))), "Failed to get Buffer for provided Index from swap chain.");
			m_device->CreateRenderTargetView(m_renderTargets.at(itr), nullptr, m_renderTargetViews.at(itr));
		}
	}
}

#endif // AC_D3D11