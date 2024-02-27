#ifndef BUFFER_HPP
#define BUFFER_HPP

#include "../conf.hpp"
#include "vertex.hpp"

struct Buffer {
    u32 id;
};

Buffer CreateBufferf(u32 type, f32 *data, i32 data_length);
Buffer CreateBufferu(u32 type, u32 *data, i32 data_length);
Buffer CreateBufferVertex(u32 type, Vertex *data, i32 data_length);

#endif