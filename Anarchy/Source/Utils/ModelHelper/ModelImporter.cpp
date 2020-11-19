#include <assimp/mesh.h>
#include <assimp/scene.h>

#include "ModelImporter.h"
#include "Engine/Object/Entity/Entity.h"
#include "Graphics/GraphicObjects/Mesh.h"
#include "System/Serializer.h"

namespace anarchy
{
    void ModelImporter::ReadFile(AC_String fileName)
    {
        const aiScene* scene = m_importer.ReadFile(fileName, gcx_meshLoaderImportFlags);
        PopulateEntityAndSerialize(scene, scene->GetShortFilename(fileName.c_str()));
    }

    void ModelImporter::PopulateEntityAndSerialize(const aiScene* scene, AC_String shortFileName)
    {

        auto meshes = scene->mMeshes;

        Entity entity = {};
        entity.ReserveMeshMemory(scene->mNumMeshes);

        auto aiVector3ToVec3 = [](aiVector3D vec)
        {
            return math::Vec3<float>(vec.x, vec.y, vec.z);
        };

        auto aiVector3ToVec2 = [](aiVector3D vec)
        {
            return math::Vec2(vec.x, vec.y);
        };

        for (uint32_t itr = 0; itr < scene->mNumMeshes; ++itr)
        {
            auto mesh = meshes[itr];
            Mesh engineMesh = {};

            std::vector<math::Vec3<float>> vertices(mesh->mNumVertices);
            std::vector<math::Vec3<float>> normals(mesh->mNumVertices);
            std::vector<math::Vec2<float>> texCoords(mesh->mNumVertices);
            std::vector<math::Vec3<float>> tangents(mesh->mNumVertices);
            std::vector<math::Vec3<float>> biTangents(mesh->mNumVertices);

            for (uint32_t itr = 0; itr < mesh->mNumVertices; ++itr)
            {
                math::Vec3<float> vec3 = {};
                math::Vec2<float> vec2 = {};

                vertices.emplace_back(aiVector3ToVec3(mesh->mVertices[itr]));

                normals.emplace_back(aiVector3ToVec3(mesh->mNormals[itr]));

                // lets just hope we are just using the first UV channel :P
                if (mesh->HasTextureCoords(0))
                {
                    texCoords.emplace_back(aiVector3ToVec2(mesh->mTextureCoords[0][itr]));
                }
                else
                {
                    texCoords.emplace_back(math::Vec2(0.0f, 0.0f));
                }


                if (mesh->HasTangentsAndBitangents())
                {
                    tangents.emplace_back(aiVector3ToVec3(mesh->mTangents[itr]));

                    biTangents.emplace_back(aiVector3ToVec3(mesh->mBitangents[itr]));
                }
                else
                {
                    vec3.x = vec3.y = vec3.z = 0.0f;
                    tangents.emplace_back(math::Vec3<float>(0.0f, 0.0f, 0.0f));
                    biTangents.emplace_back(math::Vec3<float>(0.0f, 0.0f, 0.0f));
                }
            }

            std::vector<uint32_t> indices(mesh->mNumFaces * 3);
            for (uint32_t itr = 0; itr < mesh->mNumFaces; ++itr)
            {
                // TODO: make this Vec3<uint32_t> when Vec3 is templatized
                const uint32_t vertexA = mesh->mFaces[itr].mIndices[0];
                const uint32_t vertexB = mesh->mFaces[itr].mIndices[1];
                const uint32_t vertexC = mesh->mFaces[itr].mIndices[2];

                indices.push_back(vertexA);
                indices.push_back(vertexB);
                indices.push_back(vertexC);
            }

            AC_String name = mesh->mName.C_Str();

            engineMesh.GetMeshGPUData().SetVertices(vertices);
            engineMesh.GetMeshGPUData().SetNormals(normals);
            engineMesh.GetMeshGPUData().SetTexCoords(texCoords);
            engineMesh.GetMeshGPUData().SetTangents(tangents);
            engineMesh.GetMeshGPUData().SetBiTangents(biTangents);
            engineMesh.GetMeshGPUData().SetIndices(indices);
            engineMesh.SetName(name);
            engineMesh.SetMaterialIndex(mesh->mMaterialIndex);

            entity.AddMesh(engineMesh);
        }

        SerializeEntity(entity, shortFileName);
    }

    void ModelImporter::SerializeEntity(Entity entity, AC_String filename)
    {
        Serializer serializer(AC_String(filename + ENTITY_FILE_EXT));
        serializer.Serialize(entity);
    }
}