#include "Model.h"

Model::Model(std::string path)
{
    loadModel(path);
}

void Model::loadModel(std::string path)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
    }

    directory = path.substr(0, path.find_last_of('/'));

    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode * node, const aiScene * scene)
{

    //Procesamos todos los nodos de meshes
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];

        meshes.push_back(processMesh(mesh, scene));
    }

    //luego hacemos lo mismo por cada uno de los hijos
    for (unsigned int i = 0; i < node->mNumChildren; i++)
        processNode(node->mChildren[i], scene);
}

Mesh Model::processMesh(aiMesh * mesh, const aiScene * scene)
{

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    //Procesamos los datos de los vertices
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        vertex.position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
        vertex.normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);

        if (mesh->mTextureCoords[0])
        {
            vertex.textureCoordinates = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
        }
        else
            vertex.textureCoordinates = glm::vec2(0.0f);

        
        vertices.push_back(vertex);
    }

    //Procesamos los indices 
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    //Procesamos los materiales 
    if (mesh->mMaterialIndex >= 0)
    {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
        
        std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
            
        std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }
    
    return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial* material, aiTextureType type, std::string typeName)
{
    std::vector<Texture> textures;
    for (unsigned int i = 0; i < material->GetTextureCount(type); i++)
    {
        aiString str;
        material->GetTexture(type, i, &str);
        
        bool skip = false;
        for (unsigned int j = 0; j < texturesLoaded.size(); j++)
        {
            if (std::strcmp(texturesLoaded[j].path.data(), str.C_Str()) == 0)
            {
                textures.push_back(texturesLoaded[j]);
                skip = true; 
                break;
            }
        }
        if (!skip)
        {   
            Texture texture;
            texture.ID = TextureFromFile(str.C_Str(), this->directory);
            texture.type = typeName;
            texture.path = str.C_Str();
            textures.push_back(texture);
            texturesLoaded.push_back(texture);  
        }
    }
    return textures;
}

void Model::draw(Shader& shader)
{
    for (Mesh &mesh : meshes)
        mesh.draw(shader);
}

unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    
    stbi_set_flip_vertically_on_load(true);
    
    int width, height, nrComponents;

    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);

        std::cout << "Textura cargada: \"" << path << "\""<< std::endl;
    }
    else
    {
        std::cout << "NO se pudo cargar la textura: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}
