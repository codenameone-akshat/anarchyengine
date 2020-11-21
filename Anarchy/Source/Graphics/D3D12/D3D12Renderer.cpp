#if defined(AC_D3D12) && defined(PLATFORM_WINDOWS)

#include "D3D12Renderer.h"
#include "Engine/Core/EngineContext.h"
#include "Extern/Graphics/D3D12/D3DX12/d3dx12.h"
#include "Framework/AppContext.h"
#include "Framework/FrameworkHelpers.h"
#include "Framework/Math/Vector/Vec3.hpp"
#include "Framework/Math/Vector/Vec4.hpp"
#include "Platform/Types/NumericTypeLimits.h"
#include "Platform/ResultHelper.h"
#include "Utils/Logger/Logger.h"
#include "Utils/Time/ScopedTimer.h"
namespace anarchy
{
    //////////////////////////////////////////////////////////////////////////////////////
    // Public Members
    //////////////////////////////////////////////////////////////////////////////////////

    void D3D12Renderer::Initialize()
    {
        InitializeAPI();
        InitalizeResources();
        m_imGuiWrapper->InitializeImGuiLib();
        m_imGuiWrapper->InitializeImGuiWindowsD3D12(AppContext::GetHandleToMainWindow()->GetRawHandleToWindow(), m_device->GetRawDevice(), g_numFrameBuffers, DXGI_FORMAT_R8G8B8A8_UNORM, m_srvUavHeap, m_srvUavHeap->GetCPUDescriptorHandleForHeapStart(), m_srvUavHeap->GetGPUDescriptorHandleForHeapStart());
    }

    void D3D12Renderer::PreRender()
    {
        m_imGuiWrapper->NewFrame();
        RecordCommands();
    }

    void D3D12Renderer::Render()
    {
        ID3D12CommandList* ppCommandList[] = { m_commandList.Get() };
        m_graphicsCommandQueue->ExecuteCommandLists(1, ppCommandList);

        CheckResult(m_swapChain->Present(1, NULL), "SwapChain Failed to Present");
    }

    void D3D12Renderer::PostRender()
    {
		WaitForBackBufferAvailability();
    }

    void D3D12Renderer::Shutdown()
    {
        WaitForGPUToFinish();
        m_imGuiWrapper->Shutdown();
        CloseHandle(m_fenceEvent);
    }

    //////////////////////////////////////////////////////////////////////////////////////
    // Private Members
    //////////////////////////////////////////////////////////////////////////////////////

    void D3D12Renderer::InitializeAPI()
    {
#ifdef AC_DEBUG
        EnableDebugLayer();
#endif // AC_DEBUG

        CreateDevice();
        CreateGraphicsCommandQueue();
        CreateSwapChain();
        CreateRenderTargetView();
        CreateCBVSRVHeap();
        CreateCommandAllocators();
        PopulateShaders();

        m_viewport =
        {
            0.0f,
            0.0f,
            static_cast<float>(AppContext::GetMainWindowDesc().width),
            static_cast<float>(AppContext::GetMainWindowDesc().height)
        };

        m_scissorRect =
        {
            0,
            0,
            AppContext::GetMainWindowDesc().width,
            AppContext::GetMainWindowDesc().height
        };
    }

    void D3D12Renderer::InitalizeResources()
    {
        CreateRootSignature();
        CompileAllShaders();
        CreateVertexInputLayout(); // Modify this as per the shader??
        CreateGraphicsPipelineStateObject();

        CreateGraphicsCommandList();
        // Populate code if something is there to record. Leaving it for now since there is nothing to records. Maybe put this in a Command List Manager?
        CloseGraphicsCommandList();

        CreateVertexBuffer();
        CreateIndexBuffer();
        CreateSyncObjects();
		WaitForGPUToFinish(); // wait for command list to execute
    }

#ifdef AC_DEBUG
    // Should be the first step.
    void D3D12Renderer::EnableDebugLayer()
    {
        ComPtr<ID3D12Debug1> debugController;
        if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
        {
            debugController->EnableDebugLayer();
            debugController->SetEnableGPUBasedValidation(true);

            m_factory->AppendDXGIFactoryFlags(DXGI_CREATE_FACTORY_DEBUG);
        }
    }
#endif // AC_DEBUG

    void D3D12Renderer::CreateDevice()
    {
        CheckResult(CreateDXGIFactory2(m_factory->GetDXGIFactoryFlags(), IID_PPV_ARGS(&(m_factory->GetRawFactory()))), "Failed to Create DXGIFactory.");
        m_adapter->SetAdapter(m_factory->GetD3D12SupportedHardwareAdapter());
        CheckResult(D3D12CreateDevice(m_adapter->GetAdapter().Get(), g_minFeatureLevel, IID_PPV_ARGS(&(m_device->GetRawDevice()))), "Failed to create D3D12Device.");
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
        swapChainDesc.BufferCount = g_numFrameBuffers;
        swapChainDesc.Scaling = DXGI_SCALING_STRETCH;
        swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
        swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;

        m_swapChain = m_factory->CreateSwapChain(m_graphicsCommandQueue, AppContext::GetHandleToMainWindow()->GetRawHandleToWindow(), &swapChainDesc, nullptr, nullptr);

        m_currentBackBufferIndex = m_swapChain->GetCurrentBackBufferIndex();
    }

    void D3D12Renderer::CreateRenderTargetView()
    {
        D3D12_DESCRIPTOR_HEAP_DESC rtvDesc = {};
        rtvDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
        rtvDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
        rtvDesc.NumDescriptors = g_numFrameBuffers;

        m_device->CreateDescriptorHeap(rtvDesc, m_rtvHeap);
        m_rtvHeapIncrementSize = m_device->GetDescriptorHandleIncrementSize(rtvDesc.Type);

        CD3DX12_CPU_DESCRIPTOR_HANDLE rtvDescriptorHandle(m_rtvHeap->GetCPUDescriptorHandleForHeapStart()); // Handle to the begin ptr.
        for (uint_fast32_t itr = 0; itr < g_numFrameBuffers; ++itr)
        {
            CheckResult(m_swapChain->GetBuffer(itr, IID_PPV_ARGS(&(m_renderTargets.at(itr)))), "Failed to get Buffer for provided Index from swap chain.");
            m_device->CreateRenderTargetView(m_renderTargets.at(itr), nullptr, rtvDescriptorHandle); // Null RTV_DESC for default desc.
            rtvDescriptorHandle.Offset(1, m_rtvHeapIncrementSize); // Move handle to the next ptr.
        }
    }

    void D3D12Renderer::CreateCBVSRVHeap()
    {
		D3D12_DESCRIPTOR_HEAP_DESC srvUavHeapDesc = {};
        srvUavHeapDesc.NumDescriptors = 1;
        srvUavHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
        srvUavHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
        m_device->CreateDescriptorHeap(srvUavHeapDesc, m_srvUavHeap);
        m_cbvSrvHeapIncrementSize = m_device->GetDescriptorHandleIncrementSize(srvUavHeapDesc.Type);
    }

    void D3D12Renderer::CreateCommandAllocators()
    {
        for(int32 itr = 0; itr < g_numFrameBuffers; ++itr)
            m_device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, m_commandAllocators[itr]);
    }

    void D3D12Renderer::PopulateShaders()
    {
        m_shaders = EngineContext::GetGameSpecificSettings()->GetAllShaders();
    }

    void D3D12Renderer::CreateRootSignature()
    {
        // Empty root signature

        CD3DX12_ROOT_SIGNATURE_DESC rootSigDesc;
        rootSigDesc.Init(0, nullptr, 0, nullptr, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

        ComPtr<ID3DBlob> rootSignatureBlob;
        ComPtr<ID3DBlob> error;

        CheckResult(D3D12SerializeRootSignature(&rootSigDesc, D3D_ROOT_SIGNATURE_VERSION_1_0, &rootSignatureBlob, &error), "Failed to serialize root signature.");
        m_device->CreateRootSignature(0, rootSignatureBlob, m_rootSignature);
    }

    void D3D12Renderer::CompileAllShaders()
    {
        ACScopedTimer("Shader Compilation");
        Logger::LogInfo(Logger::LogCategory::Graphics, "Compiling Shaders Started...");

        for (auto& shader : m_shaders)
        {
            shader.CompileShader();
        }

        Logger::LogInfo(Logger::LogCategory::Graphics, "Shader Compilation Done!");
    }

    void D3D12Renderer::CreateVertexInputLayout()
    {
        m_inputElementDescs.reserve(2);

        D3D12_INPUT_ELEMENT_DESC inputElemDesc =
        {
            "POSITION",
            0,
            DXGI_FORMAT_R32G32B32_FLOAT, // Vec3
            0,
            0,
            D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
            0
        };

        m_inputElementDescs.emplace_back(inputElemDesc);

        inputElemDesc =
        {
            "COLOR",
            0,
            DXGI_FORMAT_R32G32B32A32_FLOAT, // Vec4
            0,
            12, // Size of Vec3. Find a better way to do this
            D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
            0
        };

        m_inputElementDescs.emplace_back(inputElemDesc);
    }

    void D3D12Renderer::CreateGraphicsPipelineStateObject()
    {
        D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
        psoDesc.pRootSignature = m_rootSignature.Get();
        psoDesc.VS = m_shaders[0].GetShaderByteCode();
        psoDesc.PS = m_shaders[1].GetShaderByteCode();
        psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
        psoDesc.SampleMask = uint32_max; // Default 0xffff
        psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);

        psoDesc.DepthStencilState.DepthEnable = false; // Disable for now
        psoDesc.DepthStencilState.StencilEnable = false; // Disable for now

        psoDesc.InputLayout = { m_inputElementDescs.data(), static_cast<uint32_t>(m_inputElementDescs.size()) };
        psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
        psoDesc.NumRenderTargets = 1;
        psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
        psoDesc.SampleDesc.Count = 1;

        m_device->CreateGraphicsPipelineStateObject(psoDesc, m_graphicsPSO);
    }

    void D3D12Renderer::CreateGraphicsCommandList()
    {
        // Create from the current frame's command allocator. On Reset, the other command allocators are used.
        m_device->CreateCommandList(D3D12_COMMAND_LIST_TYPE_DIRECT, m_commandAllocators[m_currentBackBufferIndex].Get(), m_graphicsPSO.Get(), m_commandList);
    }

    void D3D12Renderer::CloseGraphicsCommandList()
    {
        m_commandList->Close();
    }

    void D3D12Renderer::CreateVertexBuffer()
    {
        // Creating Vertex Layout here for now
        struct Vertex
        {
            math::Vec3<float> position;
            math::Vec4<float> color;
        };

        Vertex vertexBufferData[] =
        {
            { {-0.5f,-0.5f,-0.5f}, {1.0f, 0.0f, 0.0f, 1.0f} },
            { {-0.5f,-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f, 1.0f} },
            { {-0.5f, 0.5f,-0.5f}, {0.0f, 0.0f, 1.0f, 1.0f} },
            { {-0.5f, 0.5f, 0.5f}, {0.0f, 1.0f, 0.0f, 1.0f} },

            { {0.5f,-0.5f,-0.5f}, {0.0f, 1.0f, 0.0f, 1.0f} },
            { {0.5f,-0.5f, 0.5f}, {0.0f, 1.0f, 0.0f, 1.0f} },
            { {0.5f, 0.5f,-0.5f}, {0.0f, 1.0f, 0.0f, 1.0f} },
            { {0.5f, 0.5f, 0.5f}, {0.0f, 1.0f, 0.0f, 1.0f} }
        };

        uint32_t vertexBufferSize = sizeof(vertexBufferData);

        D3D12_HEAP_PROPERTIES heapProperties = {};
        heapProperties.Type = D3D12_HEAP_TYPE_UPLOAD;
        heapProperties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
        heapProperties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
        heapProperties.CreationNodeMask = NULL; // Single GPU.
        heapProperties.VisibleNodeMask = NULL; // Single GPU.

        D3D12_RESOURCE_DESC resourceDesc = {};
        resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
        resourceDesc.Alignment = 0;
        resourceDesc.Width = vertexBufferSize;
        resourceDesc.Height = 1;
        resourceDesc.DepthOrArraySize = 1;
        resourceDesc.MipLevels = 1;
        resourceDesc.Format = DXGI_FORMAT_UNKNOWN;
        resourceDesc.SampleDesc.Count = 1;
        resourceDesc.SampleDesc.Quality = 0;
        resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
        resourceDesc.Flags = D3D12_RESOURCE_FLAG_NONE;

        m_device->CreateCommittedResource(heapProperties, D3D12_HEAP_FLAG_NONE, resourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, m_vertexBuffer, "Vertex Buffer");

        D3D12_RANGE readRange = { 0, 0 }; // No Need to read, hence begin = end.
        uint8_t* vertexDataGPUBuffer = nullptr;

        CheckResult(m_vertexBuffer->Map(0, &readRange, reinterpret_cast<void**>(&vertexDataGPUBuffer)), "Failed to map resource");
        memcpy_s(vertexDataGPUBuffer, vertexBufferSize, vertexBufferData, vertexBufferSize);
        m_vertexBuffer->Unmap(NULL, nullptr);

        m_vertexBufferView.BufferLocation = m_vertexBuffer->GetGPUVirtualAddress();
        m_vertexBufferView.StrideInBytes = sizeof(Vertex);
        m_vertexBufferView.SizeInBytes = vertexBufferSize;
    }

    void D3D12Renderer::CreateIndexBuffer()
    {
        uint32_t indexBufferData[] =
        {
            0,2,1, // -x
            1,2,3,

            4,5,6, // +x
            5,7,6,

            0,1,5, // -y
            0,5,4,

            2,6,7, // +y
            2,7,3,

            0,4,6, // -z
            0,6,2,

            1,3,7, // +z
            1,7,5,
        };

        uint32_t indexBufferSize = sizeof(indexBufferData);
        m_indicesPerInstance = indexBufferSize / sizeof(uint32_t);

        D3D12_HEAP_PROPERTIES heapProperties = {};
        heapProperties.Type = D3D12_HEAP_TYPE_UPLOAD;
        heapProperties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
        heapProperties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
        heapProperties.CreationNodeMask = NULL; // Single GPU.
        heapProperties.VisibleNodeMask = NULL; // Single GPU.

        D3D12_RESOURCE_DESC resourceDesc = {};
        resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
        resourceDesc.Alignment = 0;
        resourceDesc.Width = indexBufferSize;
        resourceDesc.Height = 1;
        resourceDesc.DepthOrArraySize = 1;
        resourceDesc.MipLevels = 1;
        resourceDesc.Format = DXGI_FORMAT_UNKNOWN;
        resourceDesc.SampleDesc.Count = 1;
        resourceDesc.SampleDesc.Quality = 0;
        resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
        resourceDesc.Flags = D3D12_RESOURCE_FLAG_NONE;

        m_device->CreateCommittedResource(heapProperties, D3D12_HEAP_FLAG_NONE, resourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, m_indexBuffer, "Index Buffer");

        D3D12_RANGE readRange = { 0, 0 }; // No Need to read, hence begin = end.
        uint8_t* indexDataGPUBuffer = nullptr;

        CheckResult(m_indexBuffer->Map(0, &readRange, reinterpret_cast<void**>(&indexDataGPUBuffer)), "Failed to map resource");
        memcpy_s(indexDataGPUBuffer, indexBufferSize, indexBufferData, indexBufferSize);
        m_indexBuffer->Unmap(NULL, nullptr);

        m_indexBufferView.BufferLocation = m_indexBuffer->GetGPUVirtualAddress();
        m_indexBufferView.Format = DXGI_FORMAT_R32_UINT;
        m_indexBufferView.SizeInBytes = indexBufferSize;
    }

    void D3D12Renderer::CreateSyncObjects()
    {
        // Create the current processing frame's fence
        m_device->CreateFence(0, D3D12_FENCE_FLAG_NONE, m_fence);
        m_fenceValues[m_currentBackBufferIndex]++;

        m_fenceEvent = CreateEvent(nullptr, false, false, "FenceEvent");
        Assert(m_fenceEvent, "Failed to Create Fence Event");
    }

    void D3D12Renderer::WaitForGPUToFinish()
    {
        const uint64 fenceVal = m_fenceValues[m_currentBackBufferIndex];

		// Schedule a Signal command in the queue.
		CheckResult(m_graphicsCommandQueue->Signal(m_fence.Get(), fenceVal), "Failed to Update Fence Value");

		// Wait until the fence has been processed.
        CheckResult(m_fence->SetEventOnCompletion(fenceVal, m_fenceEvent), "Failed to Fire Event");
        ::WaitForSingleObjectEx(m_fenceEvent, INFINITE, false);

		// Increment the fence value for the current frame.
		m_fenceValues[m_currentBackBufferIndex]++;
    }

    void D3D12Renderer::WaitForBackBufferAvailability()
    {
        // Schedule a Signal command in the queue.
        const uint64 fenceVal = m_fenceValues[m_currentBackBufferIndex];
        CheckResult(m_graphicsCommandQueue->Signal(m_fence.Get(), m_fenceValues[m_currentBackBufferIndex]), "Failed to Update Fence Value");

        // calling after present, the back buffer has changed.
        m_currentBackBufferIndex = m_swapChain->GetCurrentBackBufferIndex();

        // Wait until the fence signal issued above set the fence to the value. (if value is set, the queue has finished execution the command list. Else, wait).
        if (m_fence->GetCompletedValue() < m_fenceValues[m_currentBackBufferIndex])
        {
            CheckResult(m_fence->SetEventOnCompletion(m_fenceValues[m_currentBackBufferIndex], m_fenceEvent), "Failed to Fire Event");
            ::WaitForSingleObjectEx(m_fenceEvent, INFINITE, false);
        }

        m_fenceValues[m_currentBackBufferIndex] = fenceVal + 1;
    }

    void D3D12Renderer::RecordCommands()
    {
        CheckResult(m_commandAllocators[m_currentBackBufferIndex]->Reset(), "Failed to reset the command allocator");
        CheckResult(m_commandList->Reset(m_commandAllocators[m_currentBackBufferIndex].Get(), m_graphicsPSO.Get()), "Failed to reset the command list");

        m_commandList->SetGraphicsRootSignature(m_rootSignature.Get());
        m_commandList->RSSetViewports(1, &m_viewport);
        m_commandList->RSSetScissorRects(1, &m_scissorRect);

        // Back Buffer as a Render Target
        D3D12_RESOURCE_BARRIER renderTargetBarrier = {};
        renderTargetBarrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
        renderTargetBarrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
        renderTargetBarrier.Transition.pResource = (m_renderTargets.at(m_currentBackBufferIndex)).Get();
        renderTargetBarrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT; // used as present in the last execution
        renderTargetBarrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
        renderTargetBarrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

		ID3D12DescriptorHeap* ptrToHeaps[] = { m_srvUavHeap.Get() };
		m_commandList->SetDescriptorHeaps(1, ptrToHeaps);

        m_commandList->ResourceBarrier(1, &renderTargetBarrier);

        D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle(m_rtvHeap->GetCPUDescriptorHandleForHeapStart());
        rtvHandle.ptr += (m_currentBackBufferIndex * m_rtvHeapIncrementSize);

        auto fetchedColor = EngineContext::GetClearColor();
        m_commandList->OMSetRenderTargets(1, &rtvHandle, false, nullptr);
        m_commandList->ClearRenderTargetView(rtvHandle, (float*)&fetchedColor, 0, nullptr);
        
        
        m_commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        m_commandList->IASetVertexBuffers(0, 1, &m_vertexBufferView);
        m_commandList->IASetIndexBuffer(&m_indexBufferView);
        m_commandList->DrawIndexedInstanced(m_indicesPerInstance, 1, 0, 0, 0);
		
        m_imGuiWrapper->Render(m_commandList);

        // Back Buffer used to Present
        D3D12_RESOURCE_BARRIER presentBarrier = {};
        presentBarrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
        presentBarrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
        presentBarrier.Transition.pResource = (m_renderTargets.at(m_currentBackBufferIndex)).Get();
        presentBarrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET; // used as present in the last execution
        presentBarrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
        presentBarrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

        m_commandList->ResourceBarrier(1, &presentBarrier);

        CheckResult(m_commandList->Close(), "Failed to close the command list");
    }
}

#endif // defined(AC_D3D12) && defined(PLATFORM_WINDOWS)