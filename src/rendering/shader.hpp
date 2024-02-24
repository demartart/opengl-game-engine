#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>

class Shader {
public:
    unsigned int id;

    static Shader Create(const std::string &fsFilePath, const std::string &vsFilePath);
    void Destroy();

    void Activate();
};

#endif