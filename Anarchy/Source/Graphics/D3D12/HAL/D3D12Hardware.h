#ifdef AC_D3D12

#ifndef _D3D12_HARDWARE_H_
#define _D3D12_HARDWARE_H_

#include <d3d12.h>
#include <dxgi1_6.h>

#include "Extern/Graphics/D3D12/D3DX12/d3dx12.h"
#include "Framework/Includes/FrameworkAliases.h"
#include "Framework/Includes/FrameworkGlobals.h"
#include "Utils/StringUtils/StringUtils.h"

namespace anarchy
{
    class D3D12Adapter
    {
    public:
        D3D12Adapter() = default;
        ~D3D12Adapter() = default;

        inline IDXGIAdapter4* GetRawAdapter() { return m_hardwareAdapter.Get(); }
        inline AC_ComPtr<IDXGIAdapter4> GetAdapter() { return m_hardwareAdapter; }
        inline void SetAdapter(AC_ComPtr<IDXGIAdapter4> adapter) { m_hardwareAdapter = adapter; }

    private:
        AC_ComPtr<IDXGIAdapter4> m_hardwareAdapter;
    };


    class D3D12Device
    {
    public:
        D3D12Device() = default;
        ~D3D12Device() = default;

        inline AC_ComPtr<ID3D12Device6>& GetRawDevice() { return m_device; }
        inline void SetRawDevice(AC_ComPtr<ID3D12Device6> device) { m_device = device; }

        inline void CreateCommandQueue(D3D12_COMMAND_QUEUE_DESC desc, AC_ComPtr<ID3D12CommandQueue>& commandQueue)
        {
            ComCheck(m_device->CreateCommandQueue(&desc, IID_PPV_ARGS(&commandQueue)), "Failed to Create Requested Command Queue.");
        }

        inline void CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_DESC desc, AC_ComPtr<ID3D12DescriptorHeap>& heap)
        {
            ComCheck(m_device->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&heap)), "Failed to Create Descriptor Heap.");
        }

        inline uint32_t GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE heapType) { return m_device->GetDescriptorHandleIncrementSize(heapType); }

        inline void CreateRenderTargetView(AC_ComPtr<ID3D12Resource>& d3d12Resource, const D3D12_RENDER_TARGET_VIEW_DESC* rtvDesc, CD3DX12_CPU_DESCRIPTOR_HANDLE descriptorHandle)
        {
            m_device->CreateRenderTargetView(d3d12Resource.Get(), rtvDesc, descriptorHandle);
        }

        inline void CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE type, AC_ComPtr<ID3D12CommandAllocator>& commandAllocator)
        {
            ComCheck(m_device->CreateCommandAllocator(type, IID_PPV_ARGS(&commandAllocator)), "Failed to create Command Allocator.");
        }

        inline void CreateRootSignature(std::uint32_t nodeMask, const AC_ComPtr<ID3DBlob> blobWithRootSignature, AC_ComPtr<ID3D12RootSignature>& rootSignature)
        {
            ComCheck(m_device->CreateRootSignature(nodeMask, blobWithRootSignature->GetBufferPointer(), blobWithRootSignature->GetBufferSize(), IID_PPV_ARGS(&rootSignature)), "Failed to Create Root Signature.");
        }

        inline void CreateGraphicsPipelineStateObject(D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc, AC_ComPtr<ID3D12PipelineState>& graphicsPso)
        {
            ComCheck(m_device->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&graphicsPso)), "Failed to Create Graphics Pipeline State Object.");
        }

        inline void CreateCommandList(D3D12_COMMAND_LIST_TYPE type, ID3D12CommandAllocator* commandAllocator, ID3D12PipelineState* pso, AC_ComPtr<ID3D12GraphicsCommandList>& commandList)
        {
            // Sending nodemask as NULL for single GPU operation.
            ComCheck(m_device->CreateCommandList(NULL, type, commandAllocator, pso, IID_PPV_ARGS(&commandList)), "Failed to create Graphics Command List");
        }

        inline void CreateCommittedResource(const D3D12_HEAP_PROPERTIES& heapProperties, D3D12_HEAP_FLAGS heapFlags, const D3D12_RESOURCE_DESC& resourceDesc, D3D12_RESOURCE_STATES initialResourceState,
            const D3D12_CLEAR_VALUE* optimizedClearValue, AC_ComPtr<ID3D12Resource>& resource, AC_String resourceTag)
        {
            ComCheck(m_device->CreateCommittedResource(&heapProperties, heapFlags, &resourceDesc, initialResourceState, optimizedClearValue, IID_PPV_ARGS(&resource)), "Failed to create D3DResource: " + resourceTag);
            resource->SetName(string_cast<std::wstring>(resourceTag).c_str());
        }

        inline void CreateFence(uint16_t initialVal, D3D12_FENCE_FLAGS fenceFlags, AC_ComPtr<ID3D12Fence1>& fence)
        {
            ComCheck(m_device->CreateFence(initialVal, fenceFlags, IID_PPV_ARGS(&fence)), "Failed to Create Fence");
        }

    private:
        AC_ComPtr<ID3D12Device6> m_device = nullptr;
    };
}

#endif // _D3D12_HARDWARE_H_

#endif // AC_D3D12