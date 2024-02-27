#ifndef VERTEXARRAY_HPP
#define VERTEXARRAY_HPP

#include "vertex.hpp"
#include "../conf.hpp"

struct VertexArray {
    u32 id;
    i32 num_elements;
};

VertexArray GenerateVAO(Vertex *verts, i32 num_verts, u32 *indices, i32 num_indices);
void DrawVAO(const VertexArray &vao);

#endif