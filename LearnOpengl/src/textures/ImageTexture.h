#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <glad/glad.h>
#include <glfw3.h>

#include <string.h>

#include <stb_image.h>

class ImageTexture
{
    unsigned int ID;
    int width, height, nrComponents;
    unsigned char* data;
    std::string texPath;
    unsigned int bindSlot;
public:

    ImageTexture(const std::string &path);

    void bind(unsigned int slot = 0);
    
    unsigned int getID() const {return ID; };
    int getBindSlot() const { return bindSlot; };
    int getWidth() const { return width; };
    int getHeight() const { return height; };
};

#endif // !1
