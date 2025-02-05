#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "../conf.hpp"
#include <string>

struct Texture {
    u32 id;
    i32 width, height;
    i32 numChannels;
};

Texture LoadTexture(const std::string &path);
void DeleteTexture(Texture &texture);

void BindTexture(Texture &texture);
void UnbindTexture();

#endif
