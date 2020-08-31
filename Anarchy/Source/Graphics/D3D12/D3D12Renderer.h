#ifdef AC_D3D12

#ifndef _D3D12_RENDERER_H_
#define _D3D12_RENDERER_H_

#include <array>
#include <memory>
#include <d3d12.h>

#include "Graphics/GfxRenderer.h"
#include "Graphics/HLSL/HLSLShader.h"
#include "Graphics/D3D12/HAL/D3D12Factory.h"
#include "Graphics/D3D12/HAL/D3D12Hardware.h"

namespace anarchy
{
    constexpr D3D_FEATURE_LEVEL g_minFeatureLevel = D3D_FEATURE_LEVEL_12_1;
    constexpr uint32_t g_numFrameBuffers = 2; // TODO: Maybe Retrieve from D3D12Context or EngineContext or EngineSettings or RenderSettings or RenderingContext

    class D3D12Renderer : public GfxRenderer
    {
    public:
        D3D12Renderer() = default;
        ~D3D12Renderer() = default;

        virtual void Initialize() override;
        virtual void PreRender() override;
        virtual void Render() override;
        virtual void PostRender() override;
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
        void CreateIndexBuffer();
        void CreateSyncObjects();
        void WaitForPreviousFrame();
        // End Load Pipe

        // Render
        void RecordCommands();
        // End Render

        std::shared_ptr<D3D12Factory> m_factory = std::make_shared<D3D12Factory>();
        std::shared_ptr<D3D12Adapter> m_adapter = std::make_shared<D3D12Adapter>();
        std::shared_ptr<D3D12Device> m_device = std::make_shared<D3D12Device>();

        AC_ComPtr<ID3D12CommandQueue> m_graphicsCommandQueue = nullptr;
        AC_ComPtr<IDXGISwapChain4> m_swapChain = nullptr;
        AC_ComPtr<ID3D12DescriptorHeap> m_rtvHeap = nullptr;
        std::array<AC_ComPtr<ID3D12Resource>, g_numFrameBuffers> m_renderTargets = { };
        AC_ComPtr<ID3D12CommandAllocator> m_commandAllocator = nullptr;
        std::vector<D3D12_INPUT_ELEMENT_DESC> m_inputElementDescs = { };

        AC_ComPtr<ID3D12PipelineState> m_graphicsPSO = nullptr; // TODO: Wrap this in some PSO manager? Maybe?
        AC_ComPtr<ID3D12RootSignature> m_rootSignature = nullptr; // TODO: Find a better place for this?

        AC_ComPtr<ID3D12GraphicsCommandList> m_commandList = nullptr; // TODO: Take this to a manager?

        std::vector<HLSLShader> m_shaders = { }; // Rework required for GraphicsPipelineState
        std::vector<AC_String> m_shaderFullFileNames = { };

        // Here for now. TODO: Remove from here maybe?
        AC_ComPtr<ID3D12Resource> m_vertexBuffer = nullptr;
        D3D12_VERTEX_BUFFER_VIEW m_vertexBufferView = {};
        AC_ComPtr<ID3D12Resource> m_indexBuffer = nullptr;
        D3D12_INDEX_BUFFER_VIEW m_indexBufferView = {};
        uint32_t m_indicesPerInstance = 0;

        // Sync Objects
        AC_ComPtr<ID3D12Fence1> m_fence = nullptr;
        AC_Handle m_fenceEvent = nullptr;
        uint64_t m_fenceValue = 0;

        uint32_t m_currentBackBufferIndex = 0;
        uint32_t m_rtvHeapIncrementSize = 0;

        // Render Objects
        D3D12_VIEWPORT m_viewport = {};
        D3D12_RECT m_scissorRect = {};
    };
}

#endif // _D3D12_RENDERER_H_

#endif // AC_D3D12