#include "buffer.hpp"

#include <glad/glad.h>

Buffer CreateBufferf(u32 type, f32 *data, i32 data_length) {
    Buffer b = { .id = 0 };
    glGenBuffers(1, &b.id);

    glBindBuffer(type, b.id);
    glBufferData(type, sizeof(f32) * data_length, data, GL_STATIC_DRAW);

    return b;
}

Buffer CreateBufferu(u32 type, u32 *data, i32 data_length) {
    Buffer b = { .id = 0 };
    glGenBuffers(1, &b.id);

    glBindBuffer(type, b.id);
    glBufferData(type, sizeof(u32) * data_length, data, GL_STATIC_DRAW);

    return b;
}