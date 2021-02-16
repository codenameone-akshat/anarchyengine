#include <acpch.h>

#include "D3D12GraphicsPSOManager.h"
#include <Engine/Core/EngineContext.h>

namespace anarchy
{
	void D3D12GraphicsPSOManager::Initialize(std::shared_ptr<D3D12Device> device)
	{
		m_device = device;

		// Do something about game specific settings.. its stupid
		{
			auto shaders = EngineContext::GetGameSpecificSettings()->GetAllShaders();
			m_defaultShaderVS = std::make_shared<HLSLShader>(shaders[0]);
			m_defaultShaderPS = std::make_shared<HLSLShader>(shaders[1]);
		}
		CompileShaders();
		CreateRootSignatures();
		SetupPipelineStateObjects();
	}

	ComPtr<ID3D12PipelineState> D3D12GraphicsPSOManager::GetPipelineState(PipelineState state)
	{
		switch (state)
		{
		case PipelineState::Default:
			return m_defaultPipelineState;
			break;
		case PipelineState::Wireframe:
			return m_wireframePipelineState;
			break;
        case PipelineState::WireframeNoCull:
            return m_wireframeNoCullPipelineState;
            break;
		case PipelineState::FontFaceCull:
			return m_frontFaceCullPipelineState;
			break;
		default: 
			return m_defaultPipelineState;
			break;
		}
		
		return nullptr;
	}
	
	void D3D12GraphicsPSOManager::CompileShaders()
	{
		ACScopedTimer("Shader Compilation");

		// Default Shader
		m_defaultShaderVS->CompileShader();
		m_defaultShaderPS->CompileShader();
	}

	void D3D12GraphicsPSOManager::CreateRootSignatures()
	{
		// default root signature
		{
			D3D12_DESCRIPTOR_RANGE ranges[1];
			ranges[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
			ranges[0].NumDescriptors = 1;
			ranges[0].BaseShaderRegister = 0;
			ranges[0].RegisterSpace = 0;
			ranges[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

			D3D12_ROOT_DESCRIPTOR_TABLE descriptorTable;
			descriptorTable.NumDescriptorRanges = CountOf(ranges, D3D12_DESCRIPTOR_RANGE);
			descriptorTable.pDescriptorRanges = &ranges[0];

			D3D12_ROOT_PARAMETER rootParams[1];
			rootParams[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
			rootParams[0].DescriptorTable = descriptorTable;
			rootParams[0].ShaderVisibility = (D3D12_SHADER_VISIBILITY)(D3D12_SHADER_VISIBILITY_ALL);

			uint32 numRootParams = CountOf(rootParams, D3D12_ROOT_PARAMETER);

			CD3DX12_ROOT_SIGNATURE_DESC rootSigDesc;
			rootSigDesc.Init(numRootParams, rootParams, 0, nullptr,
				D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT | // we can deny shader stages here for better performance
				D3D12_ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS |
				D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS |
				D3D12_ROOT_SIGNATURE_FLAG_DENY_GEOMETRY_SHADER_ROOT_ACCESS);

			ComPtr<ID3DBlob> rootSignatureBlob;
			ComPtr<ID3DBlob> error;

			CheckResult(D3D12SerializeRootSignature(&rootSigDesc, D3D_ROOT_SIGNATURE_VERSION_1_0, &rootSignatureBlob, &error), "Failed to serialize root signature.");
			m_device->CreateRootSignature(0, rootSignatureBlob, m_defaultRootSignature);
		}
	}
	
	void D3D12GraphicsPSOManager::SetupPipelineStateObjects()
	{
		ACScopedTimer("PSO Creation");
		
		// Default PSO
		{
			D3D12_RASTERIZER_DESC rasterizerDesc = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);

			D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
			psoDesc.pRootSignature = m_defaultRootSignature.Get();
			psoDesc.VS = m_defaultShaderVS->GetShaderByteCode();
			psoDesc.PS = m_defaultShaderPS->GetShaderByteCode();
			psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
			psoDesc.SampleMask = uint32_max; // Default 0xffff
			psoDesc.RasterizerState = rasterizerDesc;

			psoDesc.DepthStencilState.DepthEnable = false; // Disable for now
			psoDesc.DepthStencilState.StencilEnable = false; // Disable for now

			psoDesc.InputLayout = { m_inputLayout.inputLayoutList.data(), static_cast<uint32_t>(m_inputLayout.inputLayoutList.size()) };
			psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
			psoDesc.NumRenderTargets = 1;
			psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
			psoDesc.SampleDesc.Count = 1;

			m_device->CreateGraphicsPipelineStateObject(psoDesc, m_defaultPipelineState);
		}

		// Wireframe PSO
		{
			D3D12_RASTERIZER_DESC rasterizerDesc = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
			rasterizerDesc.FillMode = D3D12_FILL_MODE_WIREFRAME;

			D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
			psoDesc.pRootSignature = m_defaultRootSignature.Get();
			psoDesc.VS = m_defaultShaderVS->GetShaderByteCode();
			psoDesc.PS = m_defaultShaderPS->GetShaderByteCode();
			psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
			psoDesc.SampleMask = uint32_max; // Default 0xffff
			psoDesc.RasterizerState = rasterizerDesc;

			psoDesc.DepthStencilState.DepthEnable = false; // Disable for now
			psoDesc.DepthStencilState.StencilEnable = false; // Disable for now

			psoDesc.InputLayout = { m_inputLayout.inputLayoutList.data(), static_cast<uint32_t>(m_inputLayout.inputLayoutList.size()) };
			psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
			psoDesc.NumRenderTargets = 1;
			psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
			psoDesc.SampleDesc.Count = 1;

			m_device->CreateGraphicsPipelineStateObject(psoDesc, m_wireframePipelineState);
		}

        // Wireframe No Culling PSO
        {
            D3D12_RASTERIZER_DESC rasterizerDesc = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
            rasterizerDesc.FillMode = D3D12_FILL_MODE_WIREFRAME;
            rasterizerDesc.CullMode = D3D12_CULL_MODE_NONE;

            D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
            psoDesc.pRootSignature = m_defaultRootSignature.Get();
            psoDesc.VS = m_defaultShaderVS->GetShaderByteCode();
            psoDesc.PS = m_defaultShaderPS->GetShaderByteCode();
            psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
            psoDesc.SampleMask = uint32_max; // Default 0xffff
            psoDesc.RasterizerState = rasterizerDesc;

            psoDesc.DepthStencilState.DepthEnable = false; // Disable for now
            psoDesc.DepthStencilState.StencilEnable = false; // Disable for now

            psoDesc.InputLayout = { m_inputLayout.inputLayoutList.data(), static_cast<uint32_t>(m_inputLayout.inputLayoutList.size()) };
            psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
            psoDesc.NumRenderTargets = 1;
            psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
            psoDesc.SampleDesc.Count = 1;

            m_device->CreateGraphicsPipelineStateObject(psoDesc, m_wireframeNoCullPipelineState);
        }

		//Cull Mode Front PSO
		{
			D3D12_RASTERIZER_DESC rasterizerDesc = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
			rasterizerDesc.CullMode = D3D12_CULL_MODE_FRONT;

			D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
			psoDesc.pRootSignature = m_defaultRootSignature.Get();
			psoDesc.VS = m_defaultShaderVS->GetShaderByteCode();
			psoDesc.PS = m_defaultShaderPS->GetShaderByteCode();
			psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
			psoDesc.SampleMask = uint32_max; // Default 0xffff
			psoDesc.RasterizerState = rasterizerDesc;

			psoDesc.DepthStencilState.DepthEnable = false; // Disable for now
			psoDesc.DepthStencilState.StencilEnable = false; // Disable for now

			psoDesc.InputLayout = { m_inputLayout.inputLayoutList.data(), static_cast<uint32_t>(m_inputLayout.inputLayoutList.size()) };
			psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
			psoDesc.NumRenderTargets = 1;
			psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
			psoDesc.SampleDesc.Count = 1;

			m_device->CreateGraphicsPipelineStateObject(psoDesc, m_frontFaceCullPipelineState);
		}

	}
}
