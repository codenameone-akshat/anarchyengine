#ifndef _MESH_H_
#define _MESH_H_

#include <vector>
#include <Eigen/Dense>

#ifdef AC_DEBUG
#include <string>
#endif // AC_DEBUG

#include SERIALIZE_STD_VECTOR_INCLUDE
#include SERIALIZE_STD_STRING_INCLUDE

namespace anarchy
{
    class MeshGPUData
    {
        DECLARE_DEFAULT_CLASSMEMBERS(MeshGPUData);

        DECLARE_DEFAULT_PROPERTY(std::vector<Vector3f>, vertices, Vertices);
        DECLARE_DEFAULT_PROPERTY(std::vector<Vector3f>, normals, Normals);
        DECLARE_DEFAULT_PROPERTY(std::vector<Vector2f>, texCoords, TexCoords);
        DECLARE_DEFAULT_PROPERTY(std::vector<Vector3f>, tangents, Tangents);
        DECLARE_DEFAULT_PROPERTY(std::vector<Vector3f>, biTangents, BiTangents);
        DECLARE_DEFAULT_PROPERTY(std::vector<uint32>, indices, Indices);

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
        DECLARE_DEFAULT_PROPERTY(uint32, materialIndex, MaterialIndex);
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