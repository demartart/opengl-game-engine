#ifndef VERTEXARRAY_HPP
#define VERTEXARRAY_HPP

#include "../conf.hpp"

struct VertexArray {
    u32 id;
    i32 num_elements;
};

VertexArray GenerateVAO(f32 *verts, i32 num_verts, u32 *indices, i32 num_indices);
void DrawVAO(const VertexArray &vao);

#endif