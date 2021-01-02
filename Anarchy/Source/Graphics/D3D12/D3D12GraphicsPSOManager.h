#ifndef _D3D12_GRAPHICS_PSO_MANAGER_H_
#define _D3D12_GRAPHICS_PSO_MANAGER_H_

#include <Graphics/D3D12/HAL/D3D12Hardware.h>
#include <Graphics/D3D12/D3D12InputLayout.h>
#include <Graphics/HLSL/HLSLShader.h>

namespace anarchy
{
	enum class PipelineState
	{
		Default,
		Wireframe,
		FontFaceCull,
		_Count
	};

	class D3D12GraphicsPSOManager
	{
		DECLARE_DEFAULT_CLASSMEMBERS(D3D12GraphicsPSOManager);

		// Pipeline States
		DECLARE_PROPERTY_NO_SET(ComPtr<ID3D12PipelineState>, defaultPipelineState, DefaultPipelineState, nullptr);
		DECLARE_PROPERTY_NO_SET(ComPtr<ID3D12PipelineState>, wireframePipelineState, WireframePipelineState, nullptr);
		DECLARE_PROPERTY_NO_SET(ComPtr<ID3D12PipelineState>, frontFaceCullPipelineState, FrontFaceCullPipelineState, nullptr);

		// Root Signatures
		DECLARE_PROPERTY_NO_SET(ComPtr<ID3D12RootSignature>, defaultRootSignature, DefaultRootSignature, nullptr);

		// Shaders
		DECLARE_PROPERTY_NO_SET(std::shared_ptr<HLSLShader>, defaultShaderVS, DefaultShaderVS, nullptr);
		DECLARE_PROPERTY_NO_SET(std::shared_ptr<HLSLShader>, defaultShaderPS, DefaultShaderPS, nullptr);
	
	public:
		void Initialize(std::shared_ptr<D3D12Device> device);
		ComPtr<ID3D12PipelineState> GetPipelineState(PipelineState state);
	
	private:
		void CompileShaders();
		void CreateRootSignatures();
		void SetupPipelineStateObjects();

		std::shared_ptr<D3D12Device> m_device = nullptr;
		InputLayout m_inputLayout = {};
	};
}

#endif // !_D3D12_GRAPHICS_PSO_MANAGER_H_
