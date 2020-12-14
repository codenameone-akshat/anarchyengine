#if defined(AC_D3D12) && defined(PLATFORM_WINDOWS)

#ifndef _D3D12_RENDERER_H_
#define _D3D12_RENDERER_H_

#include <array>
#include <memory>

#include "Graphics/GfxRenderer.h"
#include "Graphics/HLSL/HLSLShader.h"
#include "Graphics/D3D12/HAL/D3D12Factory.h"
#include "Graphics/D3D12/HAL/D3D12Hardware.h"
#include "Graphics/ImGui/ImGuiWrapper.h"

namespace anarchy
{
    constexpr D3D_FEATURE_LEVEL g_minFeatureLevel = D3D_FEATURE_LEVEL_12_1;
    constexpr uint32 g_numFrameBuffers = 3; // TODO: Maybe Retrieve from D3D12Context or EngineContext or EngineSettings or RenderSettings or RenderingContext
	constexpr uint32 g_numImGuiSrvDescriptors = 1;
	constexpr uint32 g_numCbvDescriptors = g_numFrameBuffers;

    struct SceneConstantBuffer
    {
		Vector4f color;
		Vector4f position;
	};

    class D3D12Renderer : public GfxRenderer
    {
        VIRTUAL_DTOR_GUARD(GfxRenderer);
    public:
        D3D12Renderer() = default;
        ~D3D12Renderer() = default;

        virtual void Initialize() override;
        virtual void PreRender() override;
        virtual void Render() override;
        virtual void PostRender() override;
        virtual void Shutdown() override;

    private:

        // Initializing D3D12
        void InitializeAPI();

#ifdef AC_DEBUG
        void EnableDebugLayer();
#endif // AC_DEBUG
        void CreateDevice();
        void CreateGraphicsCommandQueue();
        void CreateSwapChain();
        void SetupRenderTargetViewResources();
        void CreateRenderTargetViews();
        void CreateCBVSRVDescriptorHeap();
        void CreateCommandAllocators();
        void PopulateShaders();
        // End Initializing

        // Resize 
		void ResizeSwapChain();
        void CleanupRenderTargetViews();

        // Load Pipe
        void InitalizeResources();

        void CreateRootSignature();
        void CompileAllShaders();
        void CreateVertexInputLayout();
        void CreateGraphicsPipelineStateObject();
        void CreateGraphicsCommandList();
        void CloseGraphicsCommandList();

        void CreateVertexBuffer();
        void CreateIndexBuffer();
        void CreateCBVUploadHeap();

        void CreateSyncObjects();
		void WaitForGPUToFinish();
		void WaitForBackBufferAvailability();
        // End Load Pipe

        // Render
        void RecordCommands();
        // End Render

        // HW Objects
        std::shared_ptr<D3D12Factory> m_factory = std::make_shared<D3D12Factory>();
        std::shared_ptr<D3D12Adapter> m_adapter = std::make_shared<D3D12Adapter>();
		std::shared_ptr<D3D12Device> m_device = std::make_shared<D3D12Device>();
		
        // imGui Wrapper
        std::shared_ptr<ImGuiWrapper> m_imGuiWrapper = std::make_shared<ImGuiWrapper>();

        // COM Objects
        ComPtr<ID3D12CommandQueue> m_graphicsCommandQueue = nullptr;
        ComPtr<IDXGISwapChain4> m_swapChain = nullptr;
		ComPtr<ID3D12DescriptorHeap> m_rtvDescHeap = nullptr;
		ComPtr<ID3D12DescriptorHeap> m_cbvSrvUavDescHeap = nullptr;
		ComPtr<ID3D12PipelineState> m_graphicsPSO = nullptr; // TODO: Wrap this in some PSO manager? Maybe?
		ComPtr<ID3D12RootSignature> m_rootSignature = nullptr; // TODO: Find a better place for this?
		ComPtr<ID3D12GraphicsCommandList> m_commandList = nullptr; // TODO: Take this to a manager?

        // Per Frame COM Objects
        std::array<ComPtr<ID3D12Resource>, g_numFrameBuffers> m_renderTargets = { };
        std::array<ComPtr<ID3D12CommandAllocator>, g_numFrameBuffers> m_commandAllocators = { };
       
        // Mesh Data
        std::vector<D3D12_INPUT_ELEMENT_DESC> m_inputElementDescs = { };
		std::vector<HLSLShader> m_shaders = { }; // Rework required for GraphicsPipelineState
		std::vector<string> m_shaderFullFileNames = { };
        
        // Here for now. TODO: Remove from here maybe?
        ComPtr<ID3D12Resource> m_vertexBuffer = nullptr;
        D3D12_VERTEX_BUFFER_VIEW m_vertexBufferView = {};
        ComPtr<ID3D12Resource> m_indexBuffer = nullptr;
        D3D12_INDEX_BUFFER_VIEW m_indexBufferView = {};
        uint32 m_indicesPerInstance = 0;

        std::array<ComPtr<ID3D12Resource>, g_numFrameBuffers> m_constantBufferUploadHeaps = {};
        SceneConstantBuffer m_constantBufferData = {}; // TEMP CODE HERE
        std::array<byte*, g_numFrameBuffers> m_constantBufferDataGPUAddresses = { };

        // Sync Objects
		ComPtr<ID3D12Fence1> m_fence = nullptr;
		handle m_frameLatencyWaitableObject = nullptr;
        handle m_fenceEvent = nullptr;
		uint32 m_currentBackBufferIndex = 0; // frameIndex
        std::array<uint64, g_numFrameBuffers> m_fenceValues = { };

		uint32 m_rtvHeapIncrementSize = 0;
		uint32 m_cbvSrvUavHeapIncrementSize = 0;

        // Render Objects
        D3D12_VIEWPORT m_viewport = {};
        D3D12_RECT m_scissorRect = {};
    };
}

#endif // _D3D12_RENDERER_H_

#endif // defined(AC_D3D12) && defined(PLATFORM_WINDOWS)