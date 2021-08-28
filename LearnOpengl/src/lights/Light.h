#pragma once

//GLM
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "../shaders/Shader.h"

class Light
{
protected:
    glm::vec3 position;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

public:
    virtual glm::vec3 getPostion()  const { return position; }
    virtual glm::vec3 getAmbient()  const { return ambient;  }
    virtual glm::vec3 getDiffuse()  const { return diffuse;  }
    virtual glm::vec3 getSpecular() const { return specular; }

    virtual void draw(Shader &shader) = 0;

    virtual void setPosition(const glm::vec3& position) = 0;
    virtual void setPosition(float x, float y, float z) = 0;

    virtual void setAmbient(const glm::vec3& ambient)  = 0;
    virtual void setAmbient(float r, float g, float b) = 0;

    virtual void setDiffuse(const glm::vec3& diffuse) = 0;
    virtual void setDiffuse(float r, float g, float b) = 0;

    virtual void setSpecular(const glm::vec3& specular) = 0;
    virtual void setSpecular(float r, float g, float b) = 0;

};