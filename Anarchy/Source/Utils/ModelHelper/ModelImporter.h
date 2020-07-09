#ifndef _MODEL_LOADER_H_
#define _MODEL_LOADER_H_

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include "../../Framework/Includes/ClassHelpers.h"
#include "../../Framework/Includes/FrameworkAliases.h"

namespace anarchy::engine::core { class Entity; }

namespace anarchy::utils
{
    using Buffer = framework::AC_CharPtr;

    constexpr int32_t gcx_meshLoaderImportFlags = aiProcess_CalcTangentSpace |
        aiProcess_Triangulate |
        aiProcess_ConvertToLeftHanded |
        aiProcess_JoinIdenticalVertices |
        aiProcess_RemoveRedundantMaterials | aiProcess_ValidateDataStructure |
        aiProcess_FlipUVs | aiProcess_OptimizeMeshes;

    class ModelImporter
    {
        DECLARE_DEFAULT_CLASSMEMBERS(ModelImporter);

        void ReadFile(framework::AC_String fileName);

    private:
        void PopulateEntityAndSerialize(const aiScene* scene, framework::AC_String shortFileName);
        void SerializeEntity(anarchy::engine::core::Entity entity, std::string filename);

        Assimp::Importer m_importer = {}; // Assimp Lib Member
    };
}

#endif // _MODEL_LOADER_H_
