#ifndef SHADER_HPP
#define SHADER_HPP

#include <glm/glm.hpp>

#include <string>

class Shader {
public:
    unsigned int id;

    static Shader Create(const std::string &fsFilePath, const std::string &vsFilePath);
    void Destroy();

    void Activate();

    void UniformSetf(const std::string &name, const float value) const;
    void UniformSeti(const std::string &name, const int value) const;
    void UniformSetmat4(const std::string &name, const glm::mat4 &value) const;
};

#endif