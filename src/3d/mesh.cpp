#include "mesh.hpp"
#include <glad/glad.h>
#include <string>

Mesh::Mesh(const std::vector<Vertex> &verts, const std::vector<u32> &inds, const std::vector<Texture> &texts) 
    : vertices(verts), indices(inds), textures(texts) 
{
    Setup();
}

void Mesh::Draw(Shader &shader) {
    u32 diffuseNum = 1;

    for (u32 i = 0; i < textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        std::string num = std::to_string(diffuseNum++);

        shader.UniformSeti("texture_diffuse" + num, i);
        BindTexture(textures[i]);
    }

    glActiveTexture(GL_TEXTURE0);

    DrawVAO(vao);
}

void Mesh::Setup() {
    vao = GenerateVAO(vertices.data(), vertices.size(), indices.data(), indices.size());
}