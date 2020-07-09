#include <assimp/mesh.h>
#include <assimp/scene.h>

#include "ModelImporter.h"
#include "../../Engine/Graphics/GraphicObjects/Mesh.h"
#include "../../Engine/Core/Entity/Entity.h"
#include "../../Engine/System/Serializer.h"

namespace anarchy::utils
{
	void ModelImporter::ReadFile(framework::AC_String fileName)
	{
		const aiScene* scene = m_importer.ReadFile(fileName, gcx_meshLoaderImportFlags);
		PopulateEntityAndSerialize(scene, scene->GetShortFilename(fileName.c_str()));
	}
	
	void ModelImporter::PopulateEntityAndSerialize(const aiScene* scene, framework::AC_String shortFileName)
	{
		
		auto meshes = scene->mMeshes;
		
		anarchy::engine::core::Entity entity = {};
		entity.ReserveMeshMemory(scene->mNumMeshes);

		auto aiVector3ToVec3 = [](aiVector3D vec)
		{
			return framework::math::Vec3(vec.x, vec.y, vec.z);
		};

		auto aiVector3ToVec2 = [](aiVector3D vec)
		{
			return framework::math::Vec2(vec.x, vec.y);
		};

		for (uint32_t itr = 0; itr < scene->mNumMeshes; ++itr)
		{
			auto mesh = meshes[itr];
			graphics::Mesh engineMesh = {};

			std::vector<framework::math::Vec3> vertices(mesh->mNumVertices);
            std::vector<framework::math::Vec3> normals(mesh->mNumVertices);
            std::vector<framework::math::Vec2> texCoords(mesh->mNumVertices);
            std::vector<framework::math::Vec3> tangents(mesh->mNumVertices);
            std::vector<framework::math::Vec3> biTangents(mesh->mNumVertices);

			for (uint32_t itr = 0; itr < mesh->mNumVertices; ++itr)
			{
                framework::math::Vec3 vec3 = {};
                framework::math::Vec2 vec2 = {};

				vertices.emplace_back(aiVector3ToVec3(mesh->mVertices[itr]));

				normals.emplace_back(aiVector3ToVec3(mesh->mNormals[itr]));

				// lets just hope we are just using the first UV channel :P
				if (mesh->HasTextureCoords(0))
				{
					texCoords.emplace_back(aiVector3ToVec2(mesh->mTextureCoords[0][itr]));
				}
				else
				{
					texCoords.emplace_back(framework::math::Vec2(0.0f, 0.0f));
				}
				

				if (mesh->HasTangentsAndBitangents())
                {
                    tangents.emplace_back(aiVector3ToVec3(mesh->mTangents[itr]));

					biTangents.emplace_back(aiVector3ToVec3(mesh->mBitangents[itr]));
				}
				else
				{
					vec3.x = vec3.y = vec3.z = 0.0f;
                    tangents.emplace_back(framework::math::Vec3(0.0f, 0.0f, 0.0f));
					biTangents.emplace_back(framework::math::Vec3(0.0f, 0.0f, 0.0f));
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

			framework::AC_String name = mesh->mName.C_Str();

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

	void ModelImporter::SerializeEntity(anarchy::engine::core::Entity entity, framework::AC_String filename)
	{
		system::Serializer serializer(framework::AC_String(filename + ENTITY_FILE_EXT));
		serializer.Serialize(entity);
	}
}