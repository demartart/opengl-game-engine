#include "model.hpp"
#include "assimp/Importer.hpp"
#include "assimp/material.h"
#include "assimp/postprocess.h"
#include "assimp/scene.h"
#include <cstdio>

Model::Model(const std::string &path) {
    LoadModel(path);
}

void Model::Draw(Shader &shader) {
    for (u32 i = 0; i < meshes.size(); i++) {
        meshes[i].Draw(shader);
    }
}

void Model::LoadModel(const std::string &path) {
    Assimp::Importer import;
    const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        fprintf(stderr, "[ASSIMP] Failed to load: %s\n", import.GetErrorString());
        return;
    }

    directory = path.substr(0, path.find_last_of('/'));
    ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode *node, const aiScene *scene) {
    for (u32 i = 0; i < node->mNumMeshes; i++) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(ProcessMesh(mesh, scene));
    }

    for (u32 i = 0; i < node->mNumChildren; i++) {
        ProcessNode(node->mChildren[i], scene);
    }
}

Mesh Model::ProcessMesh(aiMesh *mesh, const aiScene *scene) {
    std::vector<Vertex> vertices;
    std::vector<u32> indices;
    std::vector<Texture> textures;

    for (u32 i = 0; i < mesh->mNumVertices; i++) {
        Vertex vert;
        
        if (mesh->mTextureCoords[0]) {
            vert = Vertex {
                .positions = {
                    mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z
                },
                .normals = {
                    mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z
                },
                .textureCoords = { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y }
            };
        } else {
            vert = Vertex {
                .positions = {
                    mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z
                },
                .normals = {
                    mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z
                },
                .textureCoords = { 0.f, 0.f }
            };
        }

        vertices.push_back(vert);
    }

    for (u32 i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (u32 j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    if (mesh->mMaterialIndex >= 0) {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
        std::vector<Texture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE);
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    }

    return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::LoadMaterialTextures(aiMaterial *mat, aiTextureType type) {
    std::vector<Texture> textures;
    for (u32 i = 0; i < mat->GetTextureCount(type); i++) {
        aiString str;
        mat->GetTexture(type, i, &str);
        Texture t = LoadTexture(str.C_Str());
        textures.push_back(t);
    }

    return textures;
}