#ifndef _D3D12_RENDERER_H_
#define _D3D12_RENDERER_H_

#include <d3d12.h>
#include <memory>

#include "HAL/DXGIFactory.h"
#include "HAL/D3D12Hardware.h"

namespace anarchy::engine::graphics
{
	constexpr D3D_FEATURE_LEVEL g_minFeatureLevel = D3D_FEATURE_LEVEL_12_0;

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
		
		std::shared_ptr<hal::DXGIFactory> m_factory = std::make_shared<hal::DXGIFactory>();
		std::shared_ptr<hal::DXGIAdapter> m_adapter = std::make_shared<hal::DXGIAdapter>();
		std::shared_ptr<hal::D3D12Device> m_device = std::make_shared<hal::D3D12Device>();
		framework::AC_ComPtr<ID3D12CommandQueue> m_graphicsCommandQueue = nullptr;
		framework::AC_ComPtr<IDXGISwapChain4> m_swapChain = nullptr;
		
		uint32_t m_numBuffers = 2;
		uint32_t m_backBufferIndex = 0;
	};
}

#endif // _D3D12_RENDERER_H_