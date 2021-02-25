#ifndef _MESH_H_
#define _MESH_H_

#include <vector>
#ifdef AC_DEBUG
#include <string>
#endif // AC_DEBUG

#include SERIALIZE_STD_VECTOR_INCLUDE
#include SERIALIZE_STD_STRING_INCLUDE
#include <Graphics/VertexLayout.h>

namespace anarchy
{
    struct VertexLayout;
    class MeshGPUData
    {
        DECLARE_DEFAULT_CLASSMEMBERS(MeshGPUData);

        DECLARE_DEFAULT_PROPERTY(std::vector<Vector3f>, vertices, Vertices);
        DECLARE_DEFAULT_PROPERTY(std::vector<Vector3f>, normals, Normals);
        DECLARE_DEFAULT_PROPERTY(std::vector<Vector2f>, texCoords, TexCoords);
        DECLARE_DEFAULT_PROPERTY(std::vector<Vector3f>, tangents, Tangents);
        DECLARE_DEFAULT_PROPERTY(std::vector<Vector3f>, biTangents, BiTangents);
        DECLARE_DEFAULT_PROPERTY(std::vector<uint32>, indices, Indices);
        DECLARE_DEFAULT_PROPERTY(std::vector<VertexLayout>, rawVertexLayoutData, RawVertexLayoutData);

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
            SERIALIZE_PROPERTY(m_rawVertexLayoutData);
        }
    };

    class Mesh
    {
        DECLARE_DEFAULT_CLASSMEMBERS(Mesh);

        DECLARE_DEFAULT_PROPERTY_REFGET(MeshGPUData, meshGPUData, MeshGPUData);
        DECLARE_DEFAULT_PROPERTY(uint32, materialIndex, MaterialIndex);
        DECLARE_DEFAULT_PROPERTY(uint64, vertexCount, VertexCount);
        DECLARE_DEFAULT_PROPERTY(uint64, indexCount, IndexCount);
        AC_DEBUGONLY(DECLARE_PROPERTY(std::string, name, Name, "UnNamed");)
    
    private:
        SERIALIZATION_PRIVATE_IMPL_ENABLE;
        SERIALIZE_IMPL()
        {
            SERIALIZE_PROPERTY(m_meshGPUData);
            SERIALIZE_PROPERTY(m_materialIndex);
            SERIALIZE_PROPERTY(m_vertexCount);
            SERIALIZE_PROPERTY(m_indexCount);
            AC_DEBUGONLY(SERIALIZE_PROPERTY(m_name);)
        }
    };
}

#endif // _MESH_H_