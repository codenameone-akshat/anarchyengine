#ifdef AC_D3D12

#include <d3dcompiler.h>

#include "HLSLShader.h"
#include "Framework/AppContext.h"
#include "Framework/FrameworkHelpers.h"
#include "Platform/ResultHelper.h"
#include "Utils/StringUtils/StringUtils.h"

namespace anarchy
{
    HLSLShader::HLSLShader(string fileName, HLSLShaderDesc shaderDesc, bool isInDeaultLocation)
        :m_shaderDesc({})
    {
        if (isInDeaultLocation)
            m_shaderFilePath = AppContext::GetSourceDirPath() + "Graphics\\Shaders\\" + fileName;
        else
            m_shaderFilePath = fileName;

        m_shaderDesc = shaderDesc;
    }

    void HLSLShader::CompileShader()
    {
#ifdef AC_DEBUG
        uint32_t shaderCompileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif // AC_DEBUG

        ComPtr<ID3DBlob> error;

        string errorMessage = "Failed To Compile Shader " + m_shaderFilePath + ".";

        std::wstring shaderwstr = string_cast<std::wstring>(m_shaderFilePath);
        string entryPoint = m_shaderDesc.shaderEntryPoint;
        string target = HLSLShaderTarget_GetName(m_shaderDesc.shaderTarget);

        CheckResult((D3DCompileFromFile(shaderwstr.c_str(), NULL, NULL, entryPoint.c_str(), target.c_str(), shaderCompileFlags, NULL, &m_shaderBlob, &error)), errorMessage, error);

        m_shaderByteCode.pShaderBytecode = m_shaderBlob->GetBufferPointer();
        m_shaderByteCode.BytecodeLength = m_shaderBlob->GetBufferSize();
    }
}

#endif // AC_D3D12