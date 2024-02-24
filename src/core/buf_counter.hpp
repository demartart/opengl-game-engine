#ifndef BUFCOUNTER_HPP
#define BUFCOUNTER_HPP

#include "../rendering/buffer.hpp"
#include "../rendering/vertex_array.hpp"

#include <vector>

class BufCounter {
public:
    static std::vector<Buffer> buffers;
    static std::vector<VertexArray> vertexArrays;

    static void CleanUp();
};

#endif