#include "shader.hpp"

#include <glad/glad.h>

#include <cstdio>
#include <fstream>
#include <sstream>

static inline unsigned int CompileShader(unsigned int type, const std::string &src) {
    const char *cstr = src.c_str();

    unsigned int id = glCreateShader(type);
    glShaderSource(id, 1, &cstr, nullptr);
    glCompileShader(id);

    int success;
    char infoLog[1024];
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success) {
        int len;
        glGetShaderInfoLog(id, 1024, &len, infoLog);
        fprintf(stderr, "[Error] Failed to Compile Shader: %s\n", infoLog);
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

    unsigned int fragment = CompileShader(GL_FRAGMENT_SHADER, fragSrc);
    unsigned int vertex = CompileShader(GL_VERTEX_SHADER, vertSrc);

    unsigned int prog = glCreateProgram();
    glAttachShader(prog, fragment);
    glAttachShader(prog, vertex);

    glLinkProgram(prog);

    int success;
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