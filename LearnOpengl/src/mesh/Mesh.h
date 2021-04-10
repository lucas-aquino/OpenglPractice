#pragma once

#include <iostream>
#include <string>
#include <vector>

//GLM
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "../shaders/Shader.h"
#include "../textures/ImageTexture.h"

struct Texture
{
    unsigned int ID;
    std::string type;
    std::string path;
};

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 textureCoordinates;
};

class Mesh
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    unsigned int VBO, VAO, EBO;

public:
    Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<Texture>& textures);

    void setupMesh();
    void draw(Shader& shader);
};
