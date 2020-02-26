#ifdef AC_D3D12

#ifndef _D3D12_RENDERER_H_
#define _D3D12_RENDERER_H_

#include <array>
#include <memory>
#include <d3d12.h>

#include "../GfxRenderer.h"
#include "HAL/D3D12Factory.h"
#include "HAL/D3D12Hardware.h"
#include "../HLSL/HLSLShader.h"

namespace anarchy::engine::graphics
{
	constexpr D3D_FEATURE_LEVEL g_minFeatureLevel = D3D_FEATURE_LEVEL_12_0;
	constexpr uint32_t g_numFrameBuffers = 2; // TODO: Maybe Retrieve from D3D12Context or EngineContext or EngineSettings or RenderSettings or RenderingContext

	class D3D12Renderer : public GfxRenderer
	{
	public:
		D3D12Renderer() = default;
		~D3D12Renderer() = default;

		virtual void Initialize() override;
		virtual void UpdateSingleThreaded() override;
		virtual void Destruct() override;
	
	private:

		// Initializing D3D12
		void InitializeAPI();

#ifdef AC_DEBUG
		void EnableDebugLayer();
#endif // AC_DEBUG
		void CreateDevice();
		void CreateGraphicsCommandQueue();
		void CreateSwapChain();
		void CreateRenderTargetView();
		void PopulateShaders();
		// End Initializing

		// Load Pipe
		void InitalizeResources();

		void CreateRootSignature();
		void CompileAllShaders();
		void CreateVertexInputLayout();
		void CreateGraphicsPipelineStateObject();
		void CreateGraphicsCommandList();
		void CloseGraphicsCommandList();

		void CreateVertexBuffer();
		// End Load Pipe

		std::shared_ptr<hal::D3D12Factory> m_factory = std::make_shared<hal::D3D12Factory>();
		std::shared_ptr<hal::D3D12Adapter> m_adapter = std::make_shared<hal::D3D12Adapter>();
		std::shared_ptr<hal::D3D12Device> m_device = std::make_shared<hal::D3D12Device>();
		
		framework::AC_ComPtr<ID3D12CommandQueue> m_graphicsCommandQueue = nullptr;
		framework::AC_ComPtr<IDXGISwapChain4> m_swapChain = nullptr;
		framework::AC_ComPtr<ID3D12DescriptorHeap> m_rtvHeap = nullptr;
		std::array<framework::AC_ComPtr<ID3D12Resource>, g_numFrameBuffers> m_renderTargets = { };
		framework::AC_ComPtr<ID3D12CommandAllocator> m_commandAllocator = nullptr;
		std::vector<D3D12_INPUT_ELEMENT_DESC> m_inputElementDescs = { };

		framework::AC_ComPtr<ID3D12PipelineState> m_graphicsPSO = nullptr; // TODO: Wrap this in some PSO manager? Maybe?
		framework::AC_ComPtr<ID3D12RootSignature> m_rootSignature = nullptr; // TODO: Find a better place for this?

		framework::AC_ComPtr<ID3D12GraphicsCommandList> m_commandList = nullptr; // TODO: Take this to a manager?

		std::vector<HLSLShader> m_shaders = { }; // Rework required for GraphicsPipelineState
		std::vector<framework::AC_String> m_shaderFullFileNames = { };

		// Here for now. TODO: Remove from here maybe?
		framework::AC_ComPtr<ID3D12Resource> m_vertexBuffer = nullptr;
		D3D12_VERTEX_BUFFER_VIEW m_vertexBufferView = {};

		uint32_t m_currentBackBufferIndex = 0;
	};
}

#endif // _D3D12_RENDERER_H_

#endif // AC_D3D12