#ifdef AC_D3D12

#ifndef _HLSL_SHADER_H_
#define _HLSL_SHADER_H_

#include <d3d12.h>
#include <vector>

#include "Platform/ResultHelper.h"
#include "Utils/MacroHelpers/EnumHelpers.h"

namespace anarchy
{
    // TODO: On compile, start the file watcher on the specified file if exists, set the cache, set the cacheValid to true.

    DECLARE_STATIC_STRING_ENUM(HLSLShaderTarget, (cs_5_0)(ds_5_0)(gs_5_0)(hs_5_0)(ps_5_0)(vs_5_0));

    // Shader Read Cache
    struct HLSLShaderCache
    {
        // TODO: Compiled shader goes here. 
        // Maybe store shader_byte_code instead of ID3DBlob to compare and validate if file has really changed and shader compilation is really required.
        // Spawn a new thread and compile shaders on it. Once finished, then only update the shader while actual rendering.
    };

    class HLSLShaderDesc
    {
    public:
        string shaderEntryPoint = "";
        HLSLShaderTarget shaderTarget;
        uint32_t shaderCompileFlags = NULL;
    };

    class HLSLShader
    {
    public:
        /*HLSL Targets as per MSDN (https://docs.microsoft.com/en-us/windows/win32/direct3dhlsl/specifying-compiler-targets)
        cs_5_0	DirectCompute 5.0 (compute shader)
        ds_5_0	Domain shader
        gs_5_0	Geometry shader
        hs_5_0	Hull shader
        ps_5_0	Pixel shader
        vs_5_0	Vertex shader*/

        HLSLShader() = default;
        HLSLShader(string fileName, HLSLShaderDesc shaderDesc, bool isInDeaultLocation = true);
        ~HLSLShader() = default;

        void CompileShader();
        inline D3D12_SHADER_BYTECODE GetShaderByteCode() { return m_shaderByteCode; }

    private:
        string m_shaderFilePath = "";
        HLSLShaderDesc m_shaderDesc;
        ComPtr<ID3DBlob> m_shaderBlob;

        D3D12_SHADER_BYTECODE m_shaderByteCode = {};

        //HLSLShaderCache m_cache = {};
    };
}

#endif // _HLSL_SHADER_H_

#endif // AC_D3D12