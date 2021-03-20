#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <glad/glad.h>
#include <glfw3.h>
#include <string.h>


#include <stb_image.h>

class Texture
{
    unsigned int ID;
    int width, height, nrComponents;
    unsigned char* data;
    std::string texPath;
public:

    Texture(const std::string &path);

    void bindTexture(GLenum texture, GLenum target) const;

    int getWidth() const {return width;};
    int getHeight() const {return height;};
};

#endif // !1
