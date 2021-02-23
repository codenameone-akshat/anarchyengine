#include "acpch.h"

#include <algorithm>
#include <assimp/mesh.h>
#include <assimp/scene.h>

#include "ModelImporter.h"
#include <Engine/Object/Entity/Entity.h>
#include <Graphics/GraphicObjects/Mesh.h>
#include <Engine/Serialization/Serializer.h>
#include <Graphics/VertexLayout.h>

namespace anarchy
{
    std::shared_ptr<Entity> ModelImporter::ReadEntityFromFile(string fileName)
    {
        const aiScene* scene = m_importer.ReadFile(fileName, gcx_meshLoaderImportFlags);
        Assert(scene, "Failed to load model. Model does not exist. Path: " + fileName);

        std::shared_ptr<Entity> entity = std::make_shared<Entity>();
        PopulateEntityAndSerialize(scene, scene->GetShortFilename(fileName.c_str()), entity);
        
        return entity;
    }

    void ModelImporter::PopulateEntityAndSerialize(const aiScene* scene, string shortFileName, std::shared_ptr<Entity> entity)
    {
        auto meshes = scene->mMeshes;

        entity->ReserveMeshMemory(scene->mNumMeshes);

        auto aiVector3ToVector3f = [](aiVector3D vec)
        {
            return Vector3f(vec.x, vec.y, vec.z);
        };

        auto aiVector3ToVector2f = [](aiVector3D vec)
        {
            return Vector2f(vec.x, vec.y);
        };

        int32 indicesOffset = 0; // index per mesh offset

        for (uint32 itr = 0; itr < scene->mNumMeshes; ++itr)
        {
            ACScopedTimer(fmt::format("Parsing Mesh {} : {} of {} ", meshes[itr]->mName.C_Str(), itr, scene->mNumMeshes));

            auto mesh = meshes[itr];
            Mesh engineMesh = {};

            std::vector<Vector3f> vertices;
            std::vector<Vector3f> normals;
            std::vector<Vector2f> texCoords;
            std::vector<Vector3f> tangents;
            std::vector<Vector3f> biTangents;
            std::vector<VertexLayout> rawVertexLayout;
            rawVertexLayout.reserve(mesh->mNumVertices);

            for (uint32 itr = 0; itr < mesh->mNumVertices; ++itr)
            {
                Vector3f vec3 = {};
                Vector2f vec2 = {};
                VertexLayout rawData = {};

                auto vertex = aiVector3ToVector3f(mesh->mVertices[itr]);
                vertices.emplace_back(vertex);
                rawData.position = vertex;
                
                if (mesh->HasNormals())
                {
                    auto normal = aiVector3ToVector3f(mesh->mNormals[itr]);
                    normals.emplace_back(normal);
                    rawData.normal = normal;
                }

                // lets just hope we are just using the first UV channel :P
                if (mesh->HasTextureCoords(0))
                {
                    texCoords.emplace_back(aiVector3ToVector2f(mesh->mTextureCoords[0][itr]));
                }
                else
                {
                    texCoords.emplace_back(Vector2f(0.0f, 0.0f));
                }

                if (mesh->HasTangentsAndBitangents())
                {
                    tangents.emplace_back(aiVector3ToVector3f(mesh->mTangents[itr]));

                    biTangents.emplace_back(aiVector3ToVector3f(mesh->mBitangents[itr]));
                }
                else
                {
                    vec3.x = vec3.y = vec3.z = 0.0f;
                    tangents.emplace_back(Vector3f(0.0f, 0.0f, 0.0f));
                    biTangents.emplace_back(Vector3f(0.0f, 0.0f, 0.0f));
                }

                rawVertexLayout.push_back(rawData);
            }

            std::vector<uint32> indices;
            for (uint32 itr = 0; itr < mesh->mNumFaces; ++itr)
            {
                // TODO: make this Vec3<uint32_t> when Vec3 is templatized
                const uint32 vertexA = mesh->mFaces[itr].mIndices[0] + indicesOffset;
                const uint32 vertexB = mesh->mFaces[itr].mIndices[1] + indicesOffset;
                const uint32 vertexC = mesh->mFaces[itr].mIndices[2] + indicesOffset;

                indices.push_back(vertexA);
                indices.push_back(vertexB);
                indices.push_back(vertexC);
            }

            // Offset the index buffer to take from the last + 1 indexed vertex to start the next mesh from (STUPID BUG THANKS TO ME :D).... took me 2 days
            indicesOffset += mesh->mNumVertices;

            string name = mesh->mName.C_Str();

            engineMesh.GetMeshGPUData().SetVertices(vertices);
            engineMesh.GetMeshGPUData().SetNormals(normals);
            engineMesh.GetMeshGPUData().SetTexCoords(texCoords);
            engineMesh.GetMeshGPUData().SetTangents(tangents);
            engineMesh.GetMeshGPUData().SetBiTangents(biTangents);
            engineMesh.GetMeshGPUData().SetIndices(indices);
            engineMesh.GetMeshGPUData().SetRawVertexLayoutData(rawVertexLayout);
            engineMesh.SetName(name);
            engineMesh.SetMaterialIndex(mesh->mMaterialIndex);
            engineMesh.SetVertexCount(mesh->mNumVertices);
            engineMesh.SetIndexCount(mesh->mNumFaces * 3);

            entity->AddMesh(engineMesh);
        }

        //SerializeEntity(entity, shortFileName);
    }

    void ModelImporter::SerializeEntity(Entity entity, string filename)
    {
        Serializer serializer(string(filename + ENTITY_FILE_EXT));
        serializer.Serialize(entity);
    }
}