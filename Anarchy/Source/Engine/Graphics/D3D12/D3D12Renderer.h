#ifndef _D3D12_RENDERER_H_
#define _D3D12_RENDERER_H_

#include <d3d12.h>
#include <memory>

#include "HAL/DXGIFactory.h"
#include "HAL/DXGIAdapter.h"
#include "HAL/D3D12Device.h"

namespace anarchy::engine::graphics
{
	constexpr D3D_FEATURE_LEVEL g_MinFeatureLevel = D3D_FEATURE_LEVEL_12_0;

	class D3D12Renderer
	{
	public:
		D3D12Renderer() = default;
		~D3D12Renderer() = default;

		void Initialize();
	
	private:
#ifdef AC_DEBUG
		void EnableDebugLayer();
		void CreateDevice();
#endif // AC_DEBUG

		std::shared_ptr<hal::DXGIFactory> m_factory = std::make_shared<hal::DXGIFactory>();
		std::shared_ptr<hal::DXGIAdapter> m_adapter = std::make_shared<hal::DXGIAdapter>();
		std::shared_ptr<hal::D3D12Device> m_device = std::make_shared<hal::D3D12Device>();
	};
}

#endif // _D3D12_RENDERER_H_