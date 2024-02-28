#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "../conf.hpp"

struct Texture {
    u32 id;
    i32 width, height;
    i32 numChannels;
};

Texture *LoadTexture(const char *path);
void DeleteTexture(Texture *texture);

#endif
