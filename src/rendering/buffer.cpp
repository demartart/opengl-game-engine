#include "buffer.hpp"

#include <glad/glad.h>

Buffer CreateBufferf(unsigned int type, float *data, int data_length) {
    Buffer b = { .id = 0 };
    glGenBuffers(1, &b.id);

    glBindBuffer(type, b.id);
    glBufferData(type, sizeof(float) * data_length, data, GL_STATIC_DRAW);

    return b;
}

Buffer CreateBufferu(unsigned int type, unsigned int *data, int data_length) {
    Buffer b = { .id = 0 };
    glGenBuffers(1, &b.id);

    glBindBuffer(type, b.id);
    glBufferData(type, sizeof(unsigned int) * data_length, data, GL_STATIC_DRAW);

    return b;
}