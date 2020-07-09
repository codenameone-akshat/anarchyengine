#ifndef _ENTITY_H_

#include <vector>

#include "../../../Framework/Includes/ClassHelpers.h"
#include "../../Graphics/GraphicObjects/Mesh.h"
#include "../../../Framework/Includes/SerializationHelpers.h"

#include SERIALIZE_STD_VECTOR_INCLUDE

#define ENTITY_FILE_EXT ".acentity"

namespace anarchy::engine::core
{
    class Entity
    {
        DECLARE_DEFAULT_CLASSMEMBERS(Entity);
        DECLARE_DEFAULT_PROPERTY(std::vector<graphics::Mesh>, meshes, Meshes);
    
    public:
        inline void ReserveMeshMemory(uint32_t elementCount) { m_meshes.reserve(elementCount); }
        inline void AddMesh(graphics::Mesh mesh) { m_meshes.emplace_back(mesh); }

    private:
        SERIALIZATION_PRIVATE_IMPL_ENABLE;
        SERIALIZE_IMPL()
        {
            SERIALIZE_PROPERTY(m_meshes);
        }
    };
}

#endif // !_ENTITY_H_
