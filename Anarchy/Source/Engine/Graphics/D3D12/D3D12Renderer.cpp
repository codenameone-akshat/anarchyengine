#include "D3D12Renderer.h"
#include "../../../Utils/Logger/Logger.h"
#include "../../../Framework/Includes/FrameworkAliases.h"
#include "../../../Framework/Includes/FrameworkGlobals.h"
#include "../../Core/EngineContext.h"

namespace anarchy::engine::graphics
{
	void D3D12Renderer::Initialize()
	{
#ifdef AC_DEBUG
		EnableDebugLayer();
#endif // AC_DEBUG

		CreateDevice();
		CreateGraphicsCommandQueue();
		CreateSwapChain();
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
#endif // AC_DEBUG

	void D3D12Renderer::CreateDevice()
	{
		framework::ComCheck(CreateDXGIFactory2(m_factory->GetDXGIFactoryFlags(), IID_PPV_ARGS(&(m_factory->GetRawFactory()))), "Failed to Create DXGIFactory.");
		m_adapter->SetAdapter(m_factory->GetD3D12SupportedHardwareAdapter());
		framework::ComCheck(D3D12CreateDevice(m_adapter->GetAdapter().Get(), g_minFeatureLevel, IID_PPV_ARGS(&(m_device->GetRawDevice()))), "Failed to create D3D12Device.");
	}
	
	void D3D12Renderer::CreateGraphicsCommandQueue()
	{
		D3D12_COMMAND_QUEUE_DESC graphicsCommandQueueDesc = {};
		graphicsCommandQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
		graphicsCommandQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		graphicsCommandQueueDesc.NodeMask = 0;
		graphicsCommandQueueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;

		m_device->CreateCommandQueue(graphicsCommandQueueDesc, m_graphicsCommandQueue);
	}
	
	void D3D12Renderer::CreateSwapChain()
	{
		DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
		swapChainDesc.Width = NULL; // Get automatically from hWND
		swapChainDesc.Height = NULL; // Get automatically from hWND
		swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.Stereo = FALSE;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = m_numBuffers;
		swapChainDesc.Scaling = DXGI_SCALING_STRETCH;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;

		m_swapChain = m_factory->CreateSwapChain(m_graphicsCommandQueue, core::AppContext::GetHandleToActiveWindow()->GetRawHandleToWindow(), &swapChainDesc, nullptr, nullptr);

		m_numBuffers = m_swapChain->GetCurrentBackBufferIndex();
	}
}