#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include SERIALIZE_STD_VECTOR_INCLUDE
#include SERIALIZE_STD_ARRAY_INCLUDE
#include SERIALIZE_STD_SHAREDPTR_INCLUDE

#include <Graphics/GraphicObjects/Texture.h>

namespace anarchy
{
    using TextureList = std::array<std::vector<std::shared_ptr<Texture>>, ToUnderlyingType(TextureType)(TextureType::_Count)>;
    class Material
    {
        DECLARE_DEFAULT_CLASSMEMBERS(Material);
        DECLARE_DEFAULT_PROPERTY(uint32, materialIndex, MaterialIndex);
        DECLARE_DEFAULT_PROPERTY(TextureList, textureList, TextureList);

        void LoadMaterialDependencies();
    
    private:
        SERIALIZATION_PRIVATE_IMPL_ENABLE;
        SERIALIZE_IMPL()
        {
            SERIALIZE_PROPERTY(m_materialIndex);
            SERIALIZE_PROPERTY(m_textureList);
        }
    };
}

#endif // !_MATERIAL_H_
