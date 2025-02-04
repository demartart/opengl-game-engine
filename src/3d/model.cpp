#include "model.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/common.hpp>
#include <cstdio>

namespace Internal {
    void ProcessNode(Model &mm, aiNode *node, const aiScene *scene) {
        for (u32 i = 0; i < node->mNumMeshes; i++) {
            aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];

        }
        for (u32 i = 0; i < node->mNumChildren; i++) {
            ProcessNode(mm, node->mChildren[i], scene);
        }
    }

    Mesh ProcessMesh(aiMesh *mesh, const aiScene *scene) {
        std::vector<Vertex> vertices;
        std::vector<u32> indices;
        std::vector<Texture> textures;

        for (u32 i = 0; i < mesh->mNumVertices; i++) {
            glm::vec3 position = { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z };
            glm::vec2 textCoords;
            if (mesh->mTextureCoords[0]) {
                textCoords = { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y };
            } else {
                textCoords = { 0.0f, 0.0f };
            }
        }

        for (u32 i = 0; i < mesh->mNumFaces; i++) {
            aiFace face = mesh->mFaces[i];
            for (u32 j = 0; j < face.mNumIndices; j++) {
                indices.push_back(face.mIndices[j]);
            }
        }

        return Mesh {};
    }
}

// This doesn't work yet, still need to finish translating the Assimp data structures into ours
Model Model::Load(const std::string &path) {
    Assimp::Importer import;
    const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        fprintf(stderr, "Assimp Error: %s\n", import.GetErrorString());
        return Model {};
    }

    Model mm = Model{};
    return mm;
}

void Model::Draw(Shader &shader) {
    for (u32 i = 0; i < meshes.size(); i++) {
        meshes[i].Draw(shader);
    }
}