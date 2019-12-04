#ifdef AC_D3D12

#ifndef _HLSL_SHADER_H_
#define _HLSL_SHADER_H_

#include <d3d12.h>

#include "../../../Framework/Includes/FrameworkAliases.h"

namespace anarchy::engine::graphics
{
	// Shader Read Cache
	struct HLSLShaderCache
	{
		// TODO: Compiled shader goes here. 
		// Maybe store shader_byte_code instead of ID3DBlob to compare and validate if file has really changed and shader compilation is really required.
		// Spawn a new thread and compile shaders on it. Once finished, then only update the shader while actual rendering.
	};

	// TODO: On compile, start the file watcher on the specified file if exists, set the cache, set the cacheValid to true.
	class HLSLShader
	{
	public: 
		HLSLShader() = default;
		~HLSLShader() = default;

		HLSLShader(framework::AC_String fileName, bool isInDeaultLocation = true);
		HRESULT CompileShader();
	private:
		
		framework::AC_String m_shaderFilePath = "";
		//framework::AC_Shader_ByteCode m_shaderByteCode = {};

		// HLSLShaderCache m_cache = {};
	};
}

#endif // _HLSL_SHADER_H_

#endif // AC_D3D12