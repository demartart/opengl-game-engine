#include "vertex_array.hpp"
#include "buffer.hpp"
#include "../core/buf_counter.hpp"

#include <glad/glad.h>

VertexArray GenerateVAO(f32 *verts, i32 num_verts, u32 *indices, i32 num_indices) {
    VertexArray vao = {
        .id = 0,
        .num_elements = num_indices
    };
    glGenVertexArrays(1, &vao.id);
    glBindVertexArray(vao.id);

    Buffer vbo = CreateBufferf(GL_ARRAY_BUFFER, verts, num_verts);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr);
    glEnableVertexAttribArray(0);

    Buffer ebo = CreateBufferu(GL_ELEMENT_ARRAY_BUFFER, indices, num_indices);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    BufCounter::buffers.push_back(vbo);
    BufCounter::buffers.push_back(ebo);
    BufCounter::vertexArrays.push_back(vao);
    return vao;
}

void DrawVAO(const VertexArray &vao) {
    glBindVertexArray(vao.id);
    glDrawElements(GL_TRIANGLES, vao.num_elements, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}