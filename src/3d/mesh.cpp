#include "mesh.hpp"

#include "../rendering/vertex_array.hpp"
#include "../rendering/buffer.hpp"
#include <glad/glad.h>
#include <string>

Mesh Mesh::Create(std::vector<Vertex> verts, std::vector<u32> ind, std::vector<Texture> textures) {
    VertexArray vao = GenerateVAO(verts.data(), verts.size(), ind.data(), ind.size());
    return Mesh {
        verts, ind, textures, vao
    };
}

void Mesh::Draw(Shader &shader) {
    u32 diffuseNum = 1;

    for (u32 i = 0; i < textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);

        std::string number = std::to_string(diffuseNum++);
        shader.UniformSeti(("material.texture_diffuse" + number).c_str(), i);
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }
    glActiveTexture(GL_TEXTURE0);

    DrawVAO(vao);
}
