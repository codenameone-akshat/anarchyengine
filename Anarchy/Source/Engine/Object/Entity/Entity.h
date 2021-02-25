#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <vector>

#include <Graphics/GraphicObjects/Mesh.h>
#include <Graphics/RenderBatchInfo.h>

#include SERIALIZE_STD_VECTOR_INCLUDE

#define ENTITY_FILE_EXT             ".acentity"
#define ENTITY_STR(name)            (string(name)+ string(ENTITY_FILE_EXT))
#define ENTITY_LOCATION             AppContext::GetDataDirPath() + string("/Entities/")
#define ENTITY_PATH_STR(name)       ENTITY_LOCATION + ENTITY_STR(name)

namespace anarchy
{
    struct RenderBatchInfo;
    class Entity
    {
        DECLARE_DEFAULT_CLASSMEMBERS(Entity);
        DECLARE_DEFAULT_PROPERTY(std::vector<Mesh>, meshes, Meshes);
        DECLARE_DEFAULT_PROPERTY(std::vector<RenderBatchInfo>, batchInfo, BatchInfo);
        DECLARE_DEFAULT_PROPERTY(uint32, numMaterials, NumMaterials);
    
    public:
        inline void ReserveMeshMemory(uint32 elementCount) { m_meshes.reserve(elementCount); }
        inline void AddMesh(Mesh mesh) { m_meshes.emplace_back(mesh); }
        void BuildBatchInfo();

    private:
        SERIALIZATION_PRIVATE_IMPL_ENABLE;
        SERIALIZE_IMPL()
        {
            SERIALIZE_PROPERTY(m_meshes);
            SERIALIZE_PROPERTY(m_batchInfo);
            SERIALIZE_PROPERTY(m_numMaterials);
        }
    };
}

#endif // !_ENTITY_H_
