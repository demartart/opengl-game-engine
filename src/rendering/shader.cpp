#include "shader.hpp"

#include <glad/glad.h>

#include <cstdio>
#include <fstream>
#include <sstream>

static inline unsigned int CompileShader(unsigned int type, const std::string &src) {
    const char *cstr = src.c_str();

    u32 id = glCreateShader(type);
    glShaderSource(id, 1, &cstr, nullptr);
    glCompileShader(id);

    i32 success;
    char infoLog[1024];
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success) {
        int len;
        glGetShaderInfoLog(id, 1024, &len, infoLog);
        fprintf(stderr, "[Error] Failed to Compile %s Shader: %s\n", (type == GL_VERTEX_SHADER) ? "Vertex" : "Fragment" , infoLog);
        return -1;
    }

    return id;
}

Shader Shader::Create(const std::string &fsFilePath, const std::string &vsFilePath) {
    std::ifstream fsFile, vsFile;
    fsFile.open(fsFilePath);
    vsFile.open(vsFilePath);

    if (!fsFile.is_open() || !vsFile.is_open()) {
        fprintf(stderr, "[Error] Could not open shader file(s).\n");
        return Shader {};
    }

    std::stringstream fst, vst;
    fst << fsFile.rdbuf();
    vst << vsFile.rdbuf();

    std::string fragSrc = fst.str(), vertSrc = vst.str();

    u32 fragment = CompileShader(GL_FRAGMENT_SHADER, fragSrc);
    u32 vertex = CompileShader(GL_VERTEX_SHADER, vertSrc);

    u32 prog = glCreateProgram();
    glAttachShader(prog, fragment);
    glAttachShader(prog, vertex);

    glLinkProgram(prog);

    i32 success;
    char infoLog[1024];
    glGetProgramiv(prog, GL_LINK_STATUS, &success);
    if (!success) {
        int len;
        glGetProgramInfoLog(prog, 1024, &len, infoLog);
        fprintf(stderr, "[Error] Failed to link shader program: %s\n", infoLog);
        return {};
    }

    glDeleteShader(fragment);
    glDeleteShader(vertex);

    return Shader {
        .id = prog,
    };
}

void Shader::Destroy() {
    glDeleteProgram(id);
}

void Shader::Activate() {
    glUseProgram(id);
}

void Shader::UniformSetf(const std::string &name, const f32 value) const {
    glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::UniformSeti(const std::string &name, const i32 value) const {
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::UniformSetmat4(const std::string &name, const glm::mat4 &value) const {
    glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &value[0][0]);
}