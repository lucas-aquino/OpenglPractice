#pragma once

#ifndef SHADER_H //Esto evita que se declare la clase shader 2 veces
#define SHADER_H

#include <glad/glad.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
    //ID del programa 
    unsigned int ID;

    //Se declara el constructor recibiendo el la direccion del vertex shader y el fragment shader
    Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
    
    //Se usa una funcion para activar el shader program
    void use();
    
    //Funciones para definir uniforms
    void setUniformBool(const std::string &name, bool value) const;
    void setUniformInt(const std::string &name, int value) const;
    void setUniformFloat(const std::string &name, float value) const;
    void setUniformMat4(const std::string &name, glm::mat4 value) const;
    void setUniformVec3(const std::string &name, glm::vec3 value) const;
};

#endif 
