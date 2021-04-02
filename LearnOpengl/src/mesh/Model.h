#pragma once
#ifndef MODEL_H
#define MODEL_H

#include "Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../textures/ImageTexture.h"

unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = false);

class Model
{
    std::vector<Mesh> meshes;
    std::string  directory;

    std::vector<Texture> texturesLoaded;

    void loadModel(std::string path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial *material, aiTextureType type, std::string typeName);  
    
public:
    
    Model(std::string path);

    void draw(Shader &shader);
};


#endif
