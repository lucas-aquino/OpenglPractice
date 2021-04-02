#include "ImageTexture.h"

ImageTexture::ImageTexture(const std::string &path)
  : ID(0),
    texPath(path),
    data(nullptr),
    width(0),
    height(0),
    nrComponents(0),
    bindSlot(0)
{
    glGenTextures(1, &ID);

    stbi_set_flip_vertically_on_load(true);

    data = stbi_load(texPath.c_str(), &width, &height, &nrComponents, 0);


    GLenum format;
    
    if (data)
    {
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, ID);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        
        
        stbi_image_free(data);
    }
    else
    { 
        std::cout << "No se puedo Cargar la textura \"" << path << "\"" << std::endl;
        stbi_image_free(data);
    }
}

void ImageTexture::bind(unsigned int slot)
{
    bindSlot = (int)slot;
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, ID);
}