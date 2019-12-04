#ifdef AC_D3D12

#include "HLSLShader.h"
#include "../../../Framework/Includes/FrameworkDefines.h"

namespace anarchy::engine::graphics
{
	HLSLShader::HLSLShader(framework::AC_String fileName, bool isInDeaultLocation)
	{
		if (isInDeaultLocation)
			m_shaderFilePath = AC_STR_LITERAL("../../Source/Engine/Graphics/D3D12/Shaders") + fileName;
		else
			m_shaderFilePath = fileName;
	}
	
	HRESULT HLSLShader::CompileShader()
	{
		return E_NOTIMPL;
	}
}

#endif // AC_D3D12