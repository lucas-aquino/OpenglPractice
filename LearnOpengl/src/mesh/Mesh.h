#pragma once
#ifndef MESH_H
#define MESH_H

#include <iostream>
#include <time.h>
#include <glad/glad.h>
#include <glfw3.h>
#include <string.h>
#include <vector>
#include <assimp/scene.h>
#include "../shaders/Shader.h"

//GLM
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 textureCoordinates;
};

struct Texture
{
    unsigned int ID;
    std::string type;
    std::string path;
};

class Mesh
{
    unsigned int VAO, VBO, EBO;

    void setupMesh();

public: 
    //Mesh data
    std::vector<Vertex>         vertices;
    std::vector<unsigned int>   indices;
    std::vector<Texture>    textures;
    
    Mesh(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices, std::vector<Texture> &textures);
    void draw(Shader &shader);
};

#endif // !MESH_H
