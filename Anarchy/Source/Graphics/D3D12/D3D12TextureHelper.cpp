#include "acpch.h"

#if defined(AC_D3D12) && defined(PLATFORM_WINDOWS)

#include "D3D12TextureHelper.h"
#include <Utils/StringUtils/StringUtils.h>

namespace anarchy
{
    void TextureHelper::Initialize()
    {
        CheckResult(::CoInitializeEx(nullptr, COINITBASE_MULTITHREADED), "Failed to Initialize Windows COM Component");
    }
    
    void TextureHelper::Shutdown()
    {
        ::CoUninitialize();
    }
    
    std::unique_ptr<DirectX::ScratchImage> TextureHelper::LoadTextureFromFile(string fullFilePath)
    {
        using namespace DirectX;
        
        ACScopedTimer(fmt::format("Loading Texture {}", fullFilePath));
        auto image = std::make_unique<ScratchImage>();

        string ext = fullFilePath.substr(fullFilePath.find("."));
        
        if (ext.compare(EXTENTION_BMP) == 0 || ext.compare(EXTENTION_PNG) == 0 || ext.compare(EXTENTION_JPEG) == 0 || ext.compare(EXTENTION_JPG) == 0)
        {
            CheckResult(LoadFromWICFile(string_cast<wstring>(fullFilePath).c_str(), WIC_FLAGS_NONE, nullptr, *image), fmt::format("Failed to load image {}", fullFilePath));
        }
        else if(ext.compare(EXTENTION_TGA) == 0)
        {
            CheckResult(LoadFromTGAFile(string_cast<wstring>(fullFilePath).c_str(), TGA_FLAGS_NONE, nullptr, *image), fmt::format("Failed to load image {}", fullFilePath));
        }
        else if (ext.compare(EXTENTION_DDS) == 0)
        {
            CheckResult(LoadFromDDSFile(string_cast<wstring>(fullFilePath).c_str(), DDS_FLAGS_NONE, nullptr, *image), fmt::format("Failed to load image {}", fullFilePath));
        }
        else if (ext.compare(EXTENTION_HDR) == 0)
        {
            CheckResult(LoadFromHDRFile(string_cast<wstring>(fullFilePath).c_str(), nullptr, *image), fmt::format("Failed to load image {}", fullFilePath));
        }
        else
        {
            NoImplAssert;
        }

        return std::move(image);
    }
}

#endif // defined(AC_D3D12) && defined(PLATFORM_WINDOWS)
