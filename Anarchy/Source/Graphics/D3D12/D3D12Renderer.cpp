#include "acpch.h"

#if defined(AC_D3D12) && defined(PLATFORM_WINDOWS)

#include "D3D12Renderer.h"

#include <Engine/Core/EngineContext.h>
#include <Engine/Object/Entity/Entity.h>
#include <Extern/Graphics/D3D12/D3DX12/d3dx12.h>
#include <Framework/AppContext.h>
#include <Framework/Math/MathHelper.h>
#include <Graphics/GfxControllables.h>
#include <Platform/ResultHelper.h>
#include <Utils/Logger/Logger.h>
#include <Utils/Time/ScopedTimer.h>
#include <Engine/EventDispatcher.hpp>
#include <Graphics/GfxEvents.h>

namespace anarchy
{
    //////////////////////////////////////////////////////////////////////////////////////
    // Public Members
    //////////////////////////////////////////////////////////////////////////////////////

    void D3D12Renderer::Initialize()
    {
        InitializeAPI();
		
		/// TEMP CODE HERE | ADD TO ASYNC COMMANDS MAYBE?
        {
            ACScopedTimer("Loading Model Task: ");
            string dataDir = AppContext::GetDataDirPath() + "sponza.wavobj";
            m_entities.emplace_back(m_modelImporter->ReadEntityFromFile(dataDir));
        }

        InitalizeResources();
        m_imGuiWrapper->InitializeImGuiLib();
        m_imGuiWrapper->InitializeImGuiWindowsD3D12(AppContext::GetHandleToMainWindow()->GetRawHandleToWindow(), m_device->GetRawDevice(), g_numFrameBuffers, DXGI_FORMAT_R8G8B8A8_UNORM, m_cbvSrvUavDescHeap, m_cbvSrvUavDescHeap->GetCPUDescriptorHandleForHeapStart(), m_cbvSrvUavDescHeap->GetGPUDescriptorHandleForHeapStart());

        // Register Events
        acEventDispatcher.RegisterEventCallback<SwapChainResizeEvent>(this, &D3D12Renderer::ResizeSwapChain);
    }

    void D3D12Renderer::PreRender()
    {
		// tempcode
		m_editorCamera.HandleInput();
        m_viewMatrix = m_editorCamera.GetViewMatrix();

		m_constantBufferData.color = GfxControllables::GetPrimitiveColor();
        m_constantBufferData.wvpMatrix = (m_viewMatrix * m_projMatrix);
		memcpy(m_constantBufferDataGPUAddresses[m_currentBackBufferIndex], &m_constantBufferData, sizeof(m_constantBufferData));

        m_imGuiWrapper->NewFrame();
    }

    void D3D12Renderer::Render()
    {
        RecordCommands();
        ID3D12CommandList* ppCommandList[] = { m_commandList.Get() };
        m_graphicsCommandQueue->ExecuteCommandLists(1, ppCommandList);

		WaitForBackBufferAvailability();
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
        
        for (uint32 itr = 0; itr < g_numFrameBuffers; ++itr)
            m_constantBufferUploadHeaps[itr]->Unmap(NULL, nullptr);

        CloseHandle(m_fenceEvent);
        CloseHandle(m_frameLatencyWaitableObject);
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
        SetupRenderTargetViewResources();
        CreateRenderTargetViews();
        CreateCBVSRVDescriptorHeap();
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
        swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT;

        m_swapChain = m_factory->CreateSwapChain(m_graphicsCommandQueue, AppContext::GetHandleToMainWindow()->GetRawHandleToWindow(), &swapChainDesc, nullptr, nullptr);

        m_currentBackBufferIndex = m_swapChain->GetCurrentBackBufferIndex();
        m_swapChain->SetMaximumFrameLatency(g_numFrameBuffers);
        m_frameLatencyWaitableObject = m_swapChain->GetFrameLatencyWaitableObject();
    }

    void D3D12Renderer::SetupRenderTargetViewResources()
    {
        D3D12_DESCRIPTOR_HEAP_DESC rtvDesc = {};
        rtvDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
        rtvDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
        rtvDesc.NumDescriptors = g_numFrameBuffers;

        m_device->CreateDescriptorHeap(rtvDesc, m_rtvDescHeap);
        m_rtvHeapIncrementSize = m_device->GetDescriptorHandleIncrementSize(rtvDesc.Type);
    }

    void D3D12Renderer::CreateRenderTargetViews()
    {
		CD3DX12_CPU_DESCRIPTOR_HANDLE rtvDescriptorHandle(m_rtvDescHeap->GetCPUDescriptorHandleForHeapStart()); // Handle to the begin ptr.
		for (uint32 itr = 0; itr < g_numFrameBuffers; ++itr)
		{
			CheckResult(m_swapChain->GetBuffer(itr, IID_PPV_ARGS(&(m_renderTargets.at(itr)))), "Failed to get Buffer for provided Index from swap chain.");
			m_device->CreateRenderTargetView(m_renderTargets.at(itr), nullptr, rtvDescriptorHandle); // Null RTV_DESC for default desc.
			rtvDescriptorHandle.Offset(1, m_rtvHeapIncrementSize); // Move handle to the next ptr.
            m_renderTargets.at(itr)->SetName(string_cast<wstring>((string("Render Target " + to_string(itr)))).c_str());
		}
    }

    void D3D12Renderer::CreateCBVSRVDescriptorHeap()
    {
        const uint32 numDescriptors = g_numImGuiSrvDescriptors + g_numCbvDescriptors;
		D3D12_DESCRIPTOR_HEAP_DESC cbvSrvUavHeapDesc = {};
        cbvSrvUavHeapDesc.NumDescriptors = numDescriptors;
        cbvSrvUavHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
        cbvSrvUavHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;

        m_device->CreateDescriptorHeap(cbvSrvUavHeapDesc, m_cbvSrvUavDescHeap);
        m_cbvSrvUavHeapIncrementSize = m_device->GetDescriptorHandleIncrementSize(cbvSrvUavHeapDesc.Type);
    }

    void D3D12Renderer::CreateCommandAllocators()
    {
        for (uint32 itr = 0; itr < g_numFrameBuffers; ++itr)
        {
            m_device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, m_commandAllocators[itr]);
            m_commandAllocators[itr]->SetName(string_cast<wstring>((string("Command Allocator for Frame: " + to_string(itr)))).c_str());
        }
    }

    void D3D12Renderer::PopulateShaders()
    {
        m_shaders = EngineContext::GetGameSpecificSettings()->GetAllShaders();
    }

    DEFINE_EVENT_MEMBER_CALLBACK(D3D12Renderer, ResizeSwapChain)
	{
        CleanupRenderTargetViews();
        m_imGuiWrapper->InvalidateResources();

        auto windowDesc = AppContext::GetMainWindowDesc();
        DXGI_SWAP_CHAIN_DESC1 swapChainDesc;

        CheckResult(m_swapChain->GetDesc1(&swapChainDesc), "Failed to retrieve swapchain desc.");
        m_swapChain->ResizeBuffers(g_numFrameBuffers, windowDesc.width, windowDesc.height, swapChainDesc.Format, swapChainDesc.Flags | DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH);

        CreateRenderTargetViews();
        m_imGuiWrapper->RecreateResources();

        m_currentBackBufferIndex = m_swapChain->GetCurrentBackBufferIndex();
        m_fenceValues.fill(0);

        m_viewport.Width = static_cast<float>(windowDesc.width);
        m_viewport.Height = static_cast<float>(windowDesc.height);

        m_scissorRect.right = windowDesc.width;
        m_scissorRect.bottom = windowDesc.height;

		// Recreate projection matrix with new aspect ratio :)
        float32 aspectRatio = static_cast<float32>(windowDesc.width) / static_cast<float32>(windowDesc.height);
		m_projMatrix.CreatePerspectiveMatrix(DegToRadf(GfxControllables::GetFOV()), aspectRatio, 0.01f, 10000000.0f);
	}

	void D3D12Renderer::CleanupRenderTargetViews()
	{
        WaitForBackBufferAvailability();

        for (uint32 itr = 0; itr < g_numFrameBuffers; ++itr)
        {
            if (m_renderTargets[itr].Get())
                m_renderTargets[itr].Reset();
        }
	}

	void D3D12Renderer::InitalizeResources()
	{
        m_graphicPSOManager->Initialize(m_device);
		CreateGraphicsCommandList();
		// Populate code if something is there to record. Leaving it for now since there is nothing to records. Maybe put this in a Command List Manager?
		CloseGraphicsCommandList();

		CreateVertexBuffer();
		CreateIndexBuffer();
        CreateCBVUploadHeap();

		CreateSyncObjects();
		WaitForGPUToFinish(); // wait for command list to execute

        // Build matrices
        m_viewMatrix = m_editorCamera.GetViewMatrix();
		
        DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
        m_swapChain->GetDesc1(&swapChainDesc);
        float32 aspectRatio = static_cast<float32>(swapChainDesc.Width) / static_cast<float32>(swapChainDesc.Height);

        m_projMatrix.CreatePerspectiveMatrix(DegToRadf(GfxControllables::GetFOV()), aspectRatio, 1.0f, 10000000.0f);
	}

    void D3D12Renderer::CreateGraphicsCommandList()
    {
        // Create from the current frame's command allocator. On Reset, the other command allocators are used.
        m_device->CreateCommandList(D3D12_COMMAND_LIST_TYPE_DIRECT, m_commandAllocators[m_currentBackBufferIndex].Get(), m_graphicPSOManager->GetDefaultPipelineState().Get(), m_commandList);
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
            Vector3f position;
        };

        std::vector<Vertex> vertexBufferData;
        
        // TODO: Cleanup 
        for (auto entity : m_entities)
        {
            for (uint32 itr = 0; itr < entity->GetMeshes().size(); ++itr)
            {
                MeshGPUData meshData = entity->GetMeshes().at(itr).GetMeshGPUData();
                auto vertices = meshData.GetVertices();
                std::for_each(vertices.begin(), vertices.end(), [&vertexBufferData](Vector3f vertex) { vertexBufferData.emplace_back(vertex); });
            }
        }

        //vertexBufferData.shrink_to_fit();

        uint64 vertexBufferSize = sizeof(Vertex) * vertexBufferData.size();;

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
        byte* vertexDataGPUBuffer = nullptr;
        auto data = vertexBufferData.data();

        CheckResult(m_vertexBuffer->Map(0, &readRange, reinterpret_cast<void**>(&vertexDataGPUBuffer)), "Failed to map vertex buffer resource");
        memcpy_s(vertexDataGPUBuffer, vertexBufferSize, vertexBufferData.data(), vertexBufferSize);
        m_vertexBuffer->Unmap(NULL, nullptr);

        m_vertexBufferView.BufferLocation = m_vertexBuffer->GetGPUVirtualAddress();
        m_vertexBufferView.StrideInBytes = sizeof(Vertex);
        m_vertexBufferView.SizeInBytes = (uint32)vertexBufferSize;
    }

    void D3D12Renderer::CreateIndexBuffer()
    {
        std::vector<uint32> indexBufferData;

        // TODO: Cleanup 
        for (auto entity : m_entities)
        {
            for (uint32 itr = 0; itr < entity->GetMeshes().size(); ++itr)
            {
                MeshGPUData meshData = entity->GetMeshes().at(itr).GetMeshGPUData();
                auto indices = meshData.GetIndices();
                std::for_each(indices.begin(), indices.end(), [&indexBufferData](uint32 index) { indexBufferData.emplace_back(index); });
            }
        }

        indexBufferData.shrink_to_fit();

        uint64 indexBufferSize = sizeof(uint32) * indexBufferData.size();
        m_indicesPerInstance = (uint32)indexBufferSize / sizeof(uint32);

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
        byte* indexDataGPUBuffer = nullptr;

        CheckResult(m_indexBuffer->Map(0, &readRange, reinterpret_cast<void**>(&indexDataGPUBuffer)), "Failed to map index buffer resource");
        memcpy_s(indexDataGPUBuffer, indexBufferSize, indexBufferData.data(), indexBufferSize);
        m_indexBuffer->Unmap(NULL, nullptr);

        m_indexBufferView.BufferLocation = m_indexBuffer->GetGPUVirtualAddress();
        m_indexBufferView.Format = DXGI_FORMAT_R32_UINT;
        m_indexBufferView.SizeInBytes = (uint32)indexBufferSize;
    }

    void D3D12Renderer::CreateCBVUploadHeap()
    {
		D3D12_HEAP_PROPERTIES heapProperties = {};
		heapProperties.Type = D3D12_HEAP_TYPE_UPLOAD;
		heapProperties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		heapProperties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
		heapProperties.CreationNodeMask = NULL; // Single GPU.
		heapProperties.VisibleNodeMask = NULL; // Single GPU.

        uint64 cbvSize = 1024 * 64; // need to be a multiple of 64kb

		D3D12_RESOURCE_DESC resourceDesc = {};
		resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
		resourceDesc.Alignment = 0;
		resourceDesc.Width = cbvSize;
		resourceDesc.Height = 1;
		resourceDesc.DepthOrArraySize = 1;
		resourceDesc.MipLevels = 1;
		resourceDesc.Format = DXGI_FORMAT_UNKNOWN;
		resourceDesc.SampleDesc.Count = 1;
		resourceDesc.SampleDesc.Quality = 0;
		resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
		resourceDesc.Flags = D3D12_RESOURCE_FLAG_NONE;


        for (uint32 itr = 0; itr < g_numFrameBuffers; ++itr)
        {
			m_device->CreateCommittedResource(heapProperties, D3D12_HEAP_FLAG_NONE, resourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, m_constantBufferUploadHeaps[itr], fmt::format("Constant Buffer Upload Heap {}", itr));
			
            D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};
			cbvDesc.BufferLocation = m_constantBufferUploadHeaps[itr]->GetGPUVirtualAddress();
            cbvDesc.SizeInBytes = AlignTo(sizeof(SceneConstantBuffer), 256); // 256 byte aligned

            CD3DX12_CPU_DESCRIPTOR_HANDLE cbvDescHandle(m_cbvSrvUavDescHeap->GetCPUDescriptorHandleForHeapStart());
            cbvDescHandle.Offset(g_numImGuiSrvDescriptors + itr, m_cbvSrvUavHeapIncrementSize);

            m_device->CreateConstantBufferView(cbvDesc, cbvDescHandle);

            ZeroMemory(&m_constantBufferData, sizeof(m_constantBufferData));
			D3D12_RANGE readRange = { 0, 0 }; // No Need to read, hence begin = end.

			CheckResult(m_constantBufferUploadHeaps[itr]->Map(0, &readRange, reinterpret_cast<void**>(&m_constantBufferDataGPUAddresses[itr])), "Failed to map constant buffer resource");
			memcpy_s(m_constantBufferDataGPUAddresses[itr], sizeof(m_constantBufferData), &m_constantBufferData, sizeof(m_constantBufferData));
        }
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
		
        ::WaitForSingleObject(m_frameLatencyWaitableObject, 0); // idk... nvidia do's and don'ts say to wait for this object :/

        // Wait until the fence signal issued above set the fence to the value. (if value is set, the queue has finished executing the command list. Else, wait).
        if (m_fence->GetCompletedValue() < m_fenceValues[m_currentBackBufferIndex])
        {
            CheckResult(m_fence->SetEventOnCompletion(m_fenceValues[m_currentBackBufferIndex], m_fenceEvent), "Failed to Fire Event");
            ::WaitForSingleObject(m_fenceEvent, INFINITE);
        }

        m_fenceValues[m_currentBackBufferIndex] = fenceVal + 1;
    }

    void D3D12Renderer::RecordCommands()
    {
        CheckResult(m_commandAllocators[m_currentBackBufferIndex]->Reset(), "Failed to reset the command allocator");
        CheckResult(m_commandList->Reset(m_commandAllocators[m_currentBackBufferIndex].Get(), m_graphicPSOManager->GetPipelineState(GfxControllables::GetPipelineState()).Get()), "Failed to reset the command list");

        m_commandList->SetGraphicsRootSignature(m_graphicPSOManager->GetDefaultRootSignature().Get());
        m_commandList->RSSetViewports(1, &m_viewport);
        m_commandList->RSSetScissorRects(1, &m_scissorRect);

		ID3D12DescriptorHeap* ptrToHeaps[] = { m_cbvSrvUavDescHeap.Get()};
		m_commandList->SetDescriptorHeaps(CountOf(ptrToHeaps, ID3D12DescriptorHeap*), ptrToHeaps);
        CD3DX12_GPU_DESCRIPTOR_HANDLE cbvSrvUavHeapDescHandle(m_cbvSrvUavDescHeap->GetGPUDescriptorHandleForHeapStart());
        cbvSrvUavHeapDescHandle.Offset(g_numImGuiSrvDescriptors + m_currentBackBufferIndex, m_cbvSrvUavHeapIncrementSize);
        m_commandList->SetGraphicsRootDescriptorTable(0, cbvSrvUavHeapDescHandle);

        // Back Buffer as a Render Target
        D3D12_RESOURCE_BARRIER renderTargetBarrier = {};
        renderTargetBarrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
        renderTargetBarrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
        renderTargetBarrier.Transition.pResource = (m_renderTargets.at(m_currentBackBufferIndex)).Get();
        renderTargetBarrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT; // used as present in the last execution
        renderTargetBarrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
        renderTargetBarrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

        m_commandList->ResourceBarrier(1, &renderTargetBarrier);

        D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle(m_rtvDescHeap->GetCPUDescriptorHandleForHeapStart());
        rtvHandle.ptr += (m_currentBackBufferIndex * m_rtvHeapIncrementSize);

        auto fetchedColor = GfxControllables::GetClearColor();
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