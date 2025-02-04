#ifndef MESH_HPP__
#define MESH_HPP__

#include "../conf.hpp"
#include "../rendering/vertex.hpp"
#include "../rendering/vertex_array.hpp"
#include "../rendering/shader.hpp"
#include "../rendering/texture.hpp"
#include <vector>

class Mesh {
public:
    std::vector<Vertex> vertices;
    std::vector<u32> indices;
    std::vector<Texture> textures;
    
    VertexArray vao;

    static Mesh Create(std::vector<Vertex> verts, std::vector<u32> ind, std::vector<Texture> textures);
    void Draw(Shader &shader);
};

#endif