#ifndef MODEL_HPP__
#define MODEL_HPP__

#include "mesh.hpp"
#include "../rendering/shader.hpp"
#include <string>
#include <vector>

class Model {
public:
    std::vector<Mesh> meshes;

    static Model Load(const std::string &path);
    void Draw(Shader &shader);
};

#endif