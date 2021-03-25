#ifndef _D3D12_TEXTURE_HELPER_H_
#define _D3D12_TEXTURE_HELPER_H_

#if defined(AC_D3D12) && defined(PLATFORM_WINDOWS)
#include <DirectXTex.h>

// DDS
#define EXTENTION_DDS ".dds"

// TGA
#define EXTENTION_TGA ".tga"

// WIC
#define EXTENTION_BMP   ".bmp"
#define EXTENTION_PNG   ".png"
#define EXTENTION_JPEG  ".jpeg"
#define EXTENTION_JPG   ".jpg"

// HDR
#define EXTENTION_HDR   ".hdr"

namespace anarchy
{
    class TextureHelper
    {
    public:
        static void Initialize();
        static void Shutdown();
        static std::unique_ptr<DirectX::ScratchImage> LoadTextureFromFile(string fullFilePath);
    };
}
#endif // defined(AC_D3D12) && defined(PLATFORM_WINDOWS)

#endif // !_D3D12_TEXTURE_HELPER_H_
