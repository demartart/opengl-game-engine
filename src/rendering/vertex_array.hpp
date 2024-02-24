#ifndef VERTEXARRAY_HPP
#define VERTEXARRAY_HPP

struct VertexArray {
    unsigned int id;
    int num_elements;
};

VertexArray GenerateVAO(float *verts, int num_verts, unsigned int *indices, int num_indices);
void DrawVAO(const VertexArray &vao);

#endif