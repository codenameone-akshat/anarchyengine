#include "acpch.h"

#include "Entity.h"

namespace anarchy
{
    void Entity::BuildBatchInfo()
    {
        ACScopedTimer("Building Batch Info");
        // Meshes need to be sorted (Done in ModelImporter)
        for (auto& mesh : m_meshes)
        {
            auto materialIndex = mesh.GetMaterialIndex();
            if (m_batchInfo.size() <= materialIndex)
            {
                RenderBatchInfo batch; 
                m_batchInfo.push_back(batch);
            }

            m_batchInfo[materialIndex].indexCount += mesh.GetIndexCount();
            m_batchInfo[materialIndex].vertexCount += mesh.GetVertexCount();
        }

        for (uint32 itr = 0; itr < m_batchInfo.size(); ++itr)
        {
            m_batchInfo[itr].startIndex += (itr == 0) ? 0 : (m_batchInfo[itr - 1].startIndex + m_batchInfo[itr - 1].indexCount);
            m_batchInfo[itr].startVertex += (itr == 0) ? 0 : (m_batchInfo[itr - 1].startVertex + m_batchInfo[itr - 1].vertexCount);
        }
    }
}
