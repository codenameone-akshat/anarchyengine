#ifdef AC_D3D12

#include <limits>

#include "D3D12Renderer.h"
#include "../../Core/EngineContext.h"
#include "../../../Utils/Logger/Logger.h"
#include "../../../Utils/Time/ScopedTimer.h"
#include "../../../Extern/Graphics/D3D12/D3DX12/d3dx12.h"
#include "../../../Framework/Includes/FrameworkAliases.h"
#include "../../../Framework/Includes/FrameworkGlobals.h"

#include"../../../Framework/Math/Vector/Vec3.hpp"
#include"../../../Framework/Math/Vector/Vec4.hpp"

namespace anarchy::engine::graphics
{
	void D3D12Renderer::Initialize()
	{
		InitializeAPI();
		InitalizeResources();
	}

	void D3D12Renderer::UpdateSingleThreaded()
	{
	}

	void D3D12Renderer::Destruct()
	{
	}
	
	void D3D12Renderer::InitializeAPI()
	{
#ifdef AC_DEBUG
		EnableDebugLayer();
#endif // AC_DEBUG

		CreateDevice();
		CreateGraphicsCommandQueue();
		CreateSwapChain();
		CreateRenderTargetView();
		m_device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, m_commandAllocator);
		PopulateShaders();
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
	}

#ifdef AC_DEBUG
	// Should be the first step.
	void D3D12Renderer::EnableDebugLayer()
	{
		framework::AC_ComPtr<ID3D12Debug1> debugController;
		auto size = sizeof(debugController);
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
		swapChainDesc.BufferCount = g_numFrameBuffers;
		swapChainDesc.Scaling = DXGI_SCALING_STRETCH;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;

		m_swapChain = m_factory->CreateSwapChain(m_graphicsCommandQueue, core::AppContext::GetHandleToActiveWindow()->GetRawHandleToWindow(), &swapChainDesc, nullptr, nullptr);

		m_currentBackBufferIndex = m_swapChain->GetCurrentBackBufferIndex();
	}
	
	void D3D12Renderer::CreateRenderTargetView()
	{
		D3D12_DESCRIPTOR_HEAP_DESC rtvDesc = {};
		rtvDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
		rtvDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		rtvDesc.NumDescriptors = g_numFrameBuffers;

		m_device->CreateDescriptorHeap(rtvDesc, m_rtvHeap);
		uint32_t rtvHeapIncrementSize = m_device->GetDescriptorHandleIncrementSize(rtvDesc.Type);

		CD3DX12_CPU_DESCRIPTOR_HANDLE rtvDescriptorHandle(m_rtvHeap->GetCPUDescriptorHandleForHeapStart()); // Handle to the begin ptr.
		for (uint_fast32_t itr = 0; itr < g_numFrameBuffers; ++itr)
		{
			framework::ComCheck(m_swapChain->GetBuffer(itr, IID_PPV_ARGS(&(m_renderTargets.at(itr)))), "Failed to get Buffer for provided Index from swap chain.");
			m_device->CreateRenderTargetView(m_renderTargets.at(itr), nullptr, rtvDescriptorHandle); // Null RTV_DESC for default desc.
			rtvDescriptorHandle.Offset(1, rtvHeapIncrementSize); // Move handle to the next ptr.
		}
	}

	void D3D12Renderer::PopulateShaders()
	{
		m_shaders = core::EngineContext::GetGameSpecificSettings()->GetAllShaders();
	}
	
	void D3D12Renderer::CreateRootSignature()
	{
		// Empty root signature

		CD3DX12_ROOT_SIGNATURE_DESC rootSigDesc;
		rootSigDesc.Init(0, nullptr, 0, nullptr, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

		framework::AC_ComPtr<ID3DBlob> rootSignatureBlob;
		framework::AC_ComPtr<ID3DBlob> error;

		framework::ComCheck(D3D12SerializeRootSignature(&rootSigDesc, D3D_ROOT_SIGNATURE_VERSION_1_0, &rootSignatureBlob, &error), "Failed to serialize root signature.");
		m_device->CreateRootSignature(0, rootSignatureBlob, m_rootSignature);
	}
	
	void D3D12Renderer::CompileAllShaders()
	{
		ACScopedTimer("Shader Compilation");
		utils::Logger::LogInfo(utils::Logger::LogCategory::Graphics, "Compiling Shaders Started...");
		
		for (auto& shader : m_shaders)
		{
			shader.CompileShader();
		}

		utils::Logger::LogInfo(utils::Logger::LogCategory::Graphics, "Shader Compilation Done!");
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
		psoDesc.SampleMask = std::numeric_limits<uint32_t>::max(); // Default 0xffff
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
		m_device->CreateCommandList(D3D12_COMMAND_LIST_TYPE_DIRECT, m_commandAllocator.Get(), m_graphicsPSO.Get(), m_commandList);
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
			framework::math::Vec3 position;
			framework::math::Vec4 color;
		};

		Vertex vertexBufferData[] =
		{
			{ {1.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f} },
			{ {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f} },
			{ {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f} }
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
		
		framework::ComCheck(m_vertexBuffer->Map(0, &readRange, reinterpret_cast<void**>(&vertexDataGPUBuffer)), "Failed to map resource");
		memcpy_s(vertexDataGPUBuffer, vertexBufferSize, vertexBufferData, vertexBufferSize);
		m_vertexBuffer->Unmap(NULL, nullptr);

		m_vertexBufferView.BufferLocation = m_vertexBuffer->GetGPUVirtualAddress();
		m_vertexBufferView.StrideInBytes = sizeof(Vertex);
		m_vertexBufferView.SizeInBytes = vertexBufferSize;
	}
}

#endif // AC_D3D12