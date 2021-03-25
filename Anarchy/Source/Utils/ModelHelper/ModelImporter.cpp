#include "acpch.h"

#include <algorithm>
#include <assimp/mesh.h>
#include <assimp/scene.h>

#include "ModelImporter.h"
#include <Engine/Object/Entity/Entity.h>
#include <Graphics/GraphicObjects/Mesh.h>
#include <Engine/Serialization/Serializer.h>
#include <Graphics/VertexLayout.h>
#include <Graphics/GraphicObjects/Material.h>
#include <Utils/Time/CPUTimer.h>

namespace anarchy
{
    std::shared_ptr<Entity> ModelImporter::ReadEntityFromFileAndSerialize(string fileName)
    {
        const aiScene* scene = m_importer.ReadFile(fileName, gcx_meshLoaderImportFlags);
        Assert(scene, "Failed to load model. Model does not exist. Path: " + fileName);

        std::shared_ptr<Entity> entity = std::make_shared<Entity>();
        PopulateEntityAndSerialize(scene, scene->GetShortFilename(fileName.c_str()), fileName, entity);

        return entity;
    }

    void ModelImporter::PopulateEntityAndSerialize(const aiScene* scene, string shortFileName, string fullFileName, std::shared_ptr<Entity> entity)
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

        CPUTimer modelParseTimer("ModelParseTimer");
        modelParseTimer.Start();
        for (uint32 itr = 0; itr < scene->mNumMeshes; ++itr)
        {
            ACScopedTimer(fmt::format("Parsing Mesh {} : {} of {} ", meshes[itr]->mName.C_Str(), itr, scene->mNumMeshes));

            auto mesh = meshes[itr];
            std::shared_ptr<Mesh> engineMesh = std::make_shared<Mesh>();

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
            
            engineMesh->GetMeshGPUDataRef().SetVertices(vertices);
            engineMesh->GetMeshGPUDataRef().SetNormals(normals);
            engineMesh->GetMeshGPUDataRef().SetTexCoords(texCoords);
            engineMesh->GetMeshGPUDataRef().SetTangents(tangents);
            engineMesh->GetMeshGPUDataRef().SetBiTangents(biTangents);
            engineMesh->GetMeshGPUDataRef().SetIndices(indices);
            engineMesh->GetMeshGPUDataRef().SetRawVertexLayoutData(rawVertexLayout);
            engineMesh->SetName(name);
            engineMesh->SetMaterialIndex(mesh->mMaterialIndex);
            engineMesh->SetVertexCount(mesh->mNumVertices);
            engineMesh->SetIndexCount(mesh->mNumFaces * 3);

            entity->AddMesh(engineMesh);
        }
        modelParseTimer.Stop();

        {
            ACScopedTimer("Sorting Meshes");
            auto& engineMeshes = entity->GetMeshesRef();
            std::sort(engineMeshes.begin(), engineMeshes.end(), [](auto& meshA, auto& meshB) {
                return meshA->GetMaterialIndex() < meshB->GetMaterialIndex();
                });
        }

        ProcessMaterialInfo(scene, fullFileName, entity);
        
        entity->BuildBatchInfo();
        
        SerializeEntity(entity, shortFileName);
    }

    void ModelImporter::ProcessMaterialInfo(const aiScene* scene, string fullFilePath, std::shared_ptr<Entity> entity)
    {
        auto materials = scene->mMaterials;
        
        // resolve file path: 
        auto filename = scene->GetShortFilename(fullFilePath.c_str());
        fullFilePath = fullFilePath.substr(0, fullFilePath.find(filename));

        MaterialList& materialListRef = entity->GetMaterialsRef();

        for (uint32 itr = 0; itr < scene->mNumMaterials; ++itr)
        {
            auto material = materials[itr];
            std::shared_ptr<Material> engineMaterial = std::make_shared<Material>();

            engineMaterial->SetMaterialIndex(itr);

            TextureList& engineMaterialTextures = engineMaterial->GetTextureListRef();

            auto addTextureToMaterialTextureList = [&](TextureType type, string texturePath, string textureName)
            {
                std::shared_ptr<Texture> engineTexture = std::make_shared<Texture>();
                engineTexture->SetName(textureName.substr(0, textureName.find(".")));
                engineTexture->SetTexturePath(texturePath);
                engineTexture->SetTextureType(type);
                engineMaterialTextures[ToUnderlyingType(TextureType)(type)].push_back(engineTexture);
            };

            // diffuse
            if (uint32 texCount = material->GetTextureCount(aiTextureType_DIFFUSE) > 0)
            {
                for (uint32 subItr = 0; subItr < texCount; ++subItr)
                {
                    aiString filename;
                    material->GetTexture(aiTextureType_DIFFUSE, subItr, &filename);
                    
                    auto texturePath = fullFilePath + string(filename.C_Str());
                    addTextureToMaterialTextureList(TextureType::Diffuse, texturePath, filename.C_Str());
                }
            }
            else
            {
                // default diffuse
            }

            // normal
            if (uint32 texCount = material->GetTextureCount(aiTextureType_HEIGHT) > 0)
            {
                for (uint32 subItr = 0; subItr < texCount; ++subItr)
                {
                    aiString filename;
                    material->GetTexture(aiTextureType_HEIGHT, subItr, &filename);

                    auto texturePath = fullFilePath + string(filename.C_Str());
                    addTextureToMaterialTextureList(TextureType::Normal, texturePath, filename.C_Str());
                }
            }
            else
            {
                // default normal
            }

            // roughness
            if (uint32 texCount = material->GetTextureCount(aiTextureType_SHININESS) > 0)
            {
                for (uint32 subItr = 0; subItr < texCount; ++subItr)
                {
                    aiString filename;
                    material->GetTexture(aiTextureType_SHININESS, subItr, &filename);
                    
                    auto texturePath = fullFilePath + string(filename.C_Str());
                    addTextureToMaterialTextureList(TextureType::Rougheness, texturePath, filename.C_Str());
                }
            }
            else
            {
                // default roughness
            }

            // opacity
            if (uint32 texCount = material->GetTextureCount(aiTextureType_OPACITY) > 0)
            {
                for (uint32 subItr = 0; subItr < texCount; ++subItr)
                {
                    aiString filename;
                    material->GetTexture(aiTextureType_OPACITY, subItr, &filename);

                    auto texturePath = fullFilePath + string(filename.C_Str());
                    addTextureToMaterialTextureList(TextureType::Opacity, texturePath, filename.C_Str());
                }
            }
            else
            {
                // default opacity
            }

            materialListRef.push_back(engineMaterial);
        }

        Assert(materialListRef.size() == scene->mNumMaterials, "Material list size inconsistant");
    }

    void ModelImporter::SerializeEntity(std::shared_ptr<Entity> entity, string filename)
    {
        ACScopedTimer("Serializing " + filename);
        Serializer serializer(string(ENTITY_PATH_STR(filename)));
        serializer.Serialize(entity.get());
    }
}