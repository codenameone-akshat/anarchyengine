#ifndef _D3D12_TEXTURE_H_
#define _D3D12_TEXTURE_H_

#if defined(AC_D3D12) && defined(PLATFORM_WINDOWS)

#include <Framework/SerializationHelpers.h>
#include SERIALIZE_ACCESS_INCLUDE
#include <Graphics/GraphicObjects/TextureCommon.h>

namespace anarchy
{
    class Texture
    {
        DECLARE_DEFAULT_CLASSMEMBERS(Texture);
        
        // Properties
        DECLARE_DEFAULT_PROPERTY_NO_REF(TextureType, textureType, TextureType);
        AC_DEBUGONLY(DECLARE_DEFAULT_PROPERTY(string, texturePath, TexturePath););
        DECLARE_DEFAULT_PROPERTY(string, name, Name);

        // Descriptor
        DECLARE_DEFAULT_PROPERTY(TextureDimensions, dimensions, Dimensions);
        DECLARE_DEFAULT_PROPERTY(uint64, arraySize, ArraySize);
        DECLARE_DEFAULT_PROPERTY(uint64, mipCount, MipCount);
        DECLARE_DEFAULT_PROPERTY(DXGI_FORMAT, format, Format); // TODO: Wrap this up later for other APIs maybe. Not needed but obviously can do that :)
        DECLARE_DEFAULT_PROPERTY(bool, isCubeMap, IsCubeMap);
    
    public:
        void LoadTextureDataFromDisk();

    private:
        SERIALIZATION_PRIVATE_IMPL_ENABLE;
        SERIALIZE_IMPL()
        {
            SERIALIZE_PROPERTY(m_textureType);
            SERIALIZE_PROPERTY(m_name);
            SERIALIZE_PROPERTY(m_dimensions);
            SERIALIZE_PROPERTY(m_arraySize);
            SERIALIZE_PROPERTY(m_mipCount);
            SERIALIZE_PROPERTY(m_format);
            SERIALIZE_PROPERTY(m_isCubeMap);
        }
    };
}

#endif // defined(AC_D3D12) && defined(PLATFORM_WINDOWS)

#endif // !_D3D12_TEXTURE_H_
