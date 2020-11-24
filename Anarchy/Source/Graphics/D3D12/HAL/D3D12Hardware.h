#ifdef AC_D3D12

#ifndef _D3D12_HARDWARE_H_
#define _D3D12_HARDWARE_H_

#include <d3d12.h>
#include <dxgi1_6.h>

#include "Extern/Graphics/D3D12/D3DX12/d3dx12.h"
#include "Platform/ResultHelper.h"
#include "Utils/StringUtils/StringUtils.h"

namespace anarchy
{
    class D3D12Adapter
    {
    public:
        D3D12Adapter() = default;
        ~D3D12Adapter() = default;

        inline IDXGIAdapter4* GetRawAdapter() { return m_hardwareAdapter.Get(); }
        inline ComPtr<IDXGIAdapter4> GetAdapter() { return m_hardwareAdapter; }
        inline void SetAdapter(ComPtr<IDXGIAdapter4> adapter) { m_hardwareAdapter = adapter; }

    private:
        ComPtr<IDXGIAdapter4> m_hardwareAdapter;
    };


    class D3D12Device
    {
    public:
        D3D12Device() = default;
        ~D3D12Device() = default;

        inline ComPtr<ID3D12Device6>& GetRawDevice() { return m_device; }
        inline void SetRawDevice(ComPtr<ID3D12Device6> device) { m_device = device; }

        inline void CreateCommandQueue(D3D12_COMMAND_QUEUE_DESC desc, ComPtr<ID3D12CommandQueue>& commandQueue)
        {
            CheckResult(m_device->CreateCommandQueue(&desc, IID_PPV_ARGS(&commandQueue)), "Failed to Create Requested Command Queue.");
        }

        inline void CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_DESC desc, ComPtr<ID3D12DescriptorHeap>& heap)
        {
            CheckResult(m_device->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&heap)), "Failed to Create Descriptor Heap.");
        }

        inline uint32 GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE heapType) { return m_device->GetDescriptorHandleIncrementSize(heapType); }

        inline void CreateRenderTargetView(ComPtr<ID3D12Resource>& d3d12Resource, const D3D12_RENDER_TARGET_VIEW_DESC* rtvDesc, CD3DX12_CPU_DESCRIPTOR_HANDLE descriptorHandle)
        {
            m_device->CreateRenderTargetView(d3d12Resource.Get(), rtvDesc, descriptorHandle);
        }

        inline void CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE type, ComPtr<ID3D12CommandAllocator>& commandAllocator)
        {
            CheckResult(m_device->CreateCommandAllocator(type, IID_PPV_ARGS(&commandAllocator)), "Failed to create Command Allocator.");
        }

        inline void CreateRootSignature(uint32 nodeMask, const ComPtr<ID3DBlob> blobWithRootSignature, ComPtr<ID3D12RootSignature>& rootSignature)
        {
            CheckResult(m_device->CreateRootSignature(nodeMask, blobWithRootSignature->GetBufferPointer(), blobWithRootSignature->GetBufferSize(), IID_PPV_ARGS(&rootSignature)), "Failed to Create Root Signature.");
        }

        inline void CreateGraphicsPipelineStateObject(D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc, ComPtr<ID3D12PipelineState>& graphicsPso)
        {
            CheckResult(m_device->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&graphicsPso)), "Failed to Create Graphics Pipeline State Object.");
        }

        inline void CreateCommandList(D3D12_COMMAND_LIST_TYPE type, ID3D12CommandAllocator* commandAllocator, ID3D12PipelineState* pso, ComPtr<ID3D12GraphicsCommandList>& commandList)
        {
            // Sending nodemask as NULL for single GPU operation.
            CheckResult(m_device->CreateCommandList(NULL, type, commandAllocator, pso, IID_PPV_ARGS(&commandList)), "Failed to create Graphics Command List");
        }

        inline void CreateCommittedResource(const D3D12_HEAP_PROPERTIES& heapProperties, D3D12_HEAP_FLAGS heapFlags, const D3D12_RESOURCE_DESC& resourceDesc, D3D12_RESOURCE_STATES initialResourceState,
            const D3D12_CLEAR_VALUE* optimizedClearValue, ComPtr<ID3D12Resource>& resource, string resourceTag)
        {
            CheckResult(m_device->CreateCommittedResource(&heapProperties, heapFlags, &resourceDesc, initialResourceState, optimizedClearValue, IID_PPV_ARGS(&resource)), "Failed to create D3DResource: " + resourceTag);
            resource->SetName(string_cast<std::wstring>(resourceTag).c_str());
        }

        inline void CreateFence(uint16 initialVal, D3D12_FENCE_FLAGS fenceFlags, ComPtr<ID3D12Fence1>& fence)
        {
            CheckResult(m_device->CreateFence(initialVal, fenceFlags, IID_PPV_ARGS(&fence)), "Failed to Create Fence");
        }

    private:
        ComPtr<ID3D12Device6> m_device = nullptr;
    };
}

#endif // _D3D12_HARDWARE_H_

#endif // AC_D3D12