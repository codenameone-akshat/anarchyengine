#ifndef _MESH_H_
#define _MESH_H_

#include <vector>

#ifdef AC_DEBUG
#include <string>
#endif // AC_DEBUG

#include "Framework/Math/Vector/Vec3.hpp"
#include "Framework/Math/Vector/Vec2.hpp"

#include "Framework/Includes/FrameworkDefines.h"
#include "Framework/Includes/ClassHelpers.h"
#include "Framework/Includes/SerializationHelpers.h"
#include SERIALIZE_STD_VECTOR_INCLUDE
#include SERIALIZE_STD_STRING_INCLUDE

namespace anarchy
{
    class MeshGPUData
    {
        DECLARE_DEFAULT_CLASSMEMBERS(MeshGPUData);

        DECLARE_DEFAULT_PROPERTY(std::vector<math::Vec3>, vertices, Vertices);
        DECLARE_DEFAULT_PROPERTY(std::vector<math::Vec3>, normals, Normals);
        DECLARE_DEFAULT_PROPERTY(std::vector<math::Vec2>, texCoords, TexCoords);
        DECLARE_DEFAULT_PROPERTY(std::vector<math::Vec3>, tangents, Tangents);
        DECLARE_DEFAULT_PROPERTY(std::vector<math::Vec3>, biTangents, BiTangents);
        // TODO: make this Vec3<uint32_t> when Vec3 is templatized
        DECLARE_DEFAULT_PROPERTY(std::vector<uint32_t>, indices, Indices);

    private:
        SERIALIZATION_PRIVATE_IMPL_ENABLE;
        SERIALIZE_IMPL()
        {
            SERIALIZE_PROPERTY(m_vertices);
            SERIALIZE_PROPERTY(m_indices);
            SERIALIZE_PROPERTY(m_normals);
            SERIALIZE_PROPERTY(m_texCoords);
            SERIALIZE_PROPERTY(m_tangents);
            SERIALIZE_PROPERTY(m_biTangents);
            SERIALIZE_PROPERTY(m_biTangents);
        }
    };

    class Mesh
    {
        DECLARE_DEFAULT_CLASSMEMBERS(Mesh);

        DECLARE_DEFAULT_PROPERTY(MeshGPUData, meshGPUData, MeshGPUData);
        DECLARE_DEFAULT_PROPERTY(uint32_t, materialIndex, MaterialIndex);
        AC_DEBUGONLY(DECLARE_PROPERTY(std::string, name, Name, "UnNamed");)
    
    private:
        SERIALIZATION_PRIVATE_IMPL_ENABLE;
        SERIALIZE_IMPL()
        {
            SERIALIZE_PROPERTY(m_meshGPUData);
            AC_DEBUGONLY(SERIALIZE_PROPERTY(m_name);)
        }
    };
}

#endif // _MESH_H_