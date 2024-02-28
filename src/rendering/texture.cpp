#include "texture.hpp"

#include <glad/glad.h>
#include <stb_image.h>
#include <cstdio>

Texture *LoadTexture(const char *path) {
    Texture *t = new Texture {0}; 
    glGenTextures(1, &t->id);
    glBindTexture(GL_TEXTURE_2D, t->id);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    stbi_set_flip_vertically_on_load(true); // ogl reads y-val flipped compared to stbi 
    unsigned char *data = stbi_load(path, &t->width, &t->height, &t->numChannels, 0);

    if (!data) {
        fprintf(stderr, "[Error] Could not load %s\n", path);
        return nullptr;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, t->width, t->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    return t;
}

void DeleteTexture(Texture *texture) {
    glDeleteTextures(1, &texture->id);
    delete texture;
}

void BindTexture(Texture *texture) {
    glBindTexture(GL_TEXTURE_2D, texture->id); 
}

void UnbindTexture() {
    glBindTexture(GL_TEXTURE_2D, 0);
}