#ifdef AC_D3D11

#ifndef _D3D11_RENDERER_H_
#define _D3D11_RENDERER_H_

#include <memory>
#include <d3d11.h>

#include "GfxRenderer.h"
#include "HAL/D3D11Hardware.h"
#include "HAL/D3D11Factory.h"	

namespace anarchy
{
	constexpr uint32_t g_numFrameBuffers = 2; // TODO: Maybe Retrieve from D3D11Context or EngineContext or EngineSettings or RenderSettings or RenderingContext

	class D3D11Renderer : public GfxRenderer
	{
	public:
		D3D11Renderer() = default;
		~D3D11Renderer() = default;

		virtual void Initialize() override;
		virtual void Destruct() override;

	private:
		void InitializeAPI();
		void CreateAdapterAndFactory();
		void CreateDevice();
		void CreateSwapChain();
		void CreateRenderTargetView();

		std::shared_ptr<D3D11Factory> m_factory = std::make_shared<D3D11Factory>();
		std::shared_ptr<D3D11Adapter> m_adapter = std::make_shared<D3D11Adapter>();
		std::shared_ptr<D3D11Device> m_device = std::make_shared<D3D11Device>();
		AC_ComPtr<IDXGISwapChain> m_swapChain = nullptr;
		AC_ComPtr<ID3D11RenderTargetView> m_renderTargetView = nullptr;
		
		std::array<AC_ComPtr<ID3D11Resource>, g_numFrameBuffers> m_renderTargets{};
		std::array<AC_ComPtr<ID3D11RenderTargetView>, g_numFrameBuffers> m_renderTargetViews{};
	};
}

#endif // _D3D11_RENDERER_H_

#endif // AC_D3D11