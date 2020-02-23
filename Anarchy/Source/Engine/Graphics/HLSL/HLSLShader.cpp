#ifdef AC_D3D12

#include <d3dcompiler.h>

#include "HLSLShader.h"
#include "../../Core/EngineContext.h"
#include "../../../Framework/Includes/FrameworkDefines.h"
#include "../../../Framework/Includes/FrameworkDefines.h"
#include "../../../Utils/StringUtils/StringUtils.h"


namespace anarchy::engine::graphics
{
	HLSLShader::HLSLShader(framework::AC_String fileName, HLSLShaderDesc shaderDesc, bool isInDeaultLocation)
		:m_shaderDesc({})
	{
		if (isInDeaultLocation)
			m_shaderFilePath = core::AppContext::GetSourceDirPath() + AC_STR_LITERAL("Engine\\Graphics\\Shaders\\") + fileName;
		else
			m_shaderFilePath = fileName;

		m_shaderDesc = shaderDesc;
	}
	
	void HLSLShader::CompileShader()
	{
#ifdef AC_DEBUG
		uint32_t shaderCompileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif // AC_DEBUG

		framework::AC_ComPtr<ID3DBlob> error;
		framework::AC_ComPtr<ID3DBlob> shaderBlob;

		framework::AC_String errorMessage = AC_STR_LITERAL("Failed To Compile Shader ") + m_shaderFilePath + AC_STR_LITERAL(".");
		
		std::wstring shaderwstr = utils::string_cast<std::wstring>(m_shaderFilePath);
		framework::AC_String entryPoint = m_shaderDesc.shaderEntryPoint;
		framework::AC_String target = HLSLShaderTarget_GetName(m_shaderDesc.shaderTarget);

		framework::ComCheck(D3DCompileFromFile(shaderwstr.c_str(), NULL, NULL, entryPoint.c_str(), target.c_str(), shaderCompileFlags, NULL, &shaderBlob, &error), errorMessage, error);

		m_shaderByteCode.pShaderBytecode = shaderBlob->GetBufferPointer();
		m_shaderByteCode.BytecodeLength = shaderBlob->GetBufferSize();
	}
}

#endif // AC_D3D12