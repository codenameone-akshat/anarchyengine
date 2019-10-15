#ifndef _D3D12_RENDERER_H_
#define _D3D12_RENDERER_H_

#include <array>
#include <memory>
#include <d3d12.h>

#include "HAL/DXGIFactory.h"
#include "HAL/D3D12Hardware.h"

namespace anarchy::engine::graphics
{
	constexpr D3D_FEATURE_LEVEL g_minFeatureLevel = D3D_FEATURE_LEVEL_12_0;
	constexpr uint32_t g_numFrameBuffers = 2; // TODO: Maybe Retrieve from D3D12Context or EngineContext or EngineSettings or RenderSettings or RenderingContext

	class D3D12Renderer
	{
	public:
		D3D12Renderer() = default;
		~D3D12Renderer() = default;

		void Initialize();
	
	private:
#ifdef AC_DEBUG
		void EnableDebugLayer();
#endif // AC_DEBUG
		
		void CreateDevice();
		void CreateGraphicsCommandQueue();
		void CreateSwapChain();
		void CreateRenderTargetView();
		
		std::shared_ptr<hal::DXGIFactory> m_factory = std::make_shared<hal::DXGIFactory>();
		std::shared_ptr<hal::DXGIAdapter> m_adapter = std::make_shared<hal::DXGIAdapter>();
		std::shared_ptr<hal::D3D12Device> m_device = std::make_shared<hal::D3D12Device>();
		
		framework::AC_ComPtr<ID3D12CommandQueue> m_graphicsCommandQueue = nullptr;
		framework::AC_ComPtr<IDXGISwapChain4> m_swapChain = nullptr;
		framework::AC_ComPtr<ID3D12DescriptorHeap> m_rtvHeap = nullptr;
		std::array<framework::AC_ComPtr<ID3D12Resource>, g_numFrameBuffers> m_renderTargets{};
		framework::AC_ComPtr<ID3D12CommandAllocator> m_commandAllocator = nullptr;

		uint32_t m_currentBackBufferIndex = 0;
	};
}

#endif // _D3D12_RENDERER_H_