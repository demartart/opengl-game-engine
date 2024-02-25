#ifndef BUFFER_HPP
#define BUFFER_HPP

#include "../conf.hpp"

struct Buffer {
    u32 id;
};

Buffer CreateBufferf(u32 type, f32 *data, i32 data_length);
Buffer CreateBufferu(u32 type, u32 *data, i32 data_length);

#endif