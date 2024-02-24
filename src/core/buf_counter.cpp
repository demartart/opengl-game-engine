#include "buf_counter.hpp"

#include <glad/glad.h>

std::vector<Buffer> BufCounter::buffers = {};
std::vector<VertexArray> BufCounter::vertexArrays = {};

void BufCounter::CleanUp() {
    for (auto &elt: BufCounter::buffers) {
        glDeleteBuffers(1, &elt.id);
    }

    for (auto &elt: BufCounter::vertexArrays) {
        glDeleteVertexArrays(1, &elt.id);
    }
}