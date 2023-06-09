﻿#include "Rendering/Public/AssimpHelper.h"

#include <iostream>
#include <assimp/mesh.h>
#include <assimp/scene.h>

void AssimpHelper::ParseSingleBone(uint32_t boneIdx, const aiBone* bone)
{
    std::cout << "Bone " << boneIdx << ": '" << bone->mName.C_Str() << "' num vertices affected by this bone: " << bone->mNumWeights << "\n";

    std::cout << bone->mOffsetMatrix.a1 << " " << bone->mOffsetMatrix.a2 << " " << bone->mOffsetMatrix.a3 << " " << bone->mOffsetMatrix.a4 << std::endl;
    std::cout << bone->mOffsetMatrix.b1 << " " << bone->mOffsetMatrix.b2 << " " << bone->mOffsetMatrix.b3 << " " << bone->mOffsetMatrix.b4 << std::endl;
    std::cout << bone->mOffsetMatrix.c1 << " " << bone->mOffsetMatrix.c2 << " " << bone->mOffsetMatrix.c3 << " " << bone->mOffsetMatrix.c4 << std::endl;
    std::cout << bone->mOffsetMatrix.d1 << " " << bone->mOffsetMatrix.d2 << " " << bone->mOffsetMatrix.d3 << " " << bone->mOffsetMatrix.d4 << std::endl;
    
    for (uint32_t i = 0; i < bone->mNumWeights; i++)
    {
        if (i == 0)
        {
            std::cout << "\n";
        }
        const aiVertexWeight& vw = bone->mWeights[i];
  //      std::cout << i << ": vertex id " << vw.mVertexId << " weight " << vw.mWeight;
    }

    std::cout << "\n";
}

void AssimpHelper::ParseMeshBones(const aiMesh* mesh)
{
    for (uint32_t i = 0; i < mesh->mNumBones; i++)
    {
        ParseSingleBone(i, mesh->mBones[i]);
    }
}

void AssimpHelper::ParseMeshes(const aiScene* scene)
{
    std::cout<<"***************************\n";
    std::cout<<"Parsing " << scene->mNumMeshes << " meshes\n\n";

    int sumVertices = 0;
    int sumIndices = 0;
    int sumBones = 0;

    for (uint32_t i = 0; i < scene->mNumMeshes; i++)
    {
        const aiMesh* mesh = scene->mMeshes[i];
        const int nVertices = mesh->mNumVertices;
        const int nIndices = mesh->mNumFaces * 3;
        const int nBones = mesh->mNumBones;
        std::cout << "Mesh: " << i << " '" << mesh->mName.C_Str() << "': vertices " << nVertices << " indices " << nIndices << " bones " << nBones << "\n";

        sumVertices += nVertices;
        sumIndices += nIndices;
        sumBones += nBones;

        if (mesh->HasBones())
        {
            ParseMeshBones(mesh);
        }

        std::cout << "\n";
    }

    std::cout << "\nSum vertices " << sumVertices << " sum indices " << sumIndices << " sum bones " << sumBones;
}

void AssimpHelper::ParseScene(const aiScene* scene)
{
    ParseMeshes(scene);
}
