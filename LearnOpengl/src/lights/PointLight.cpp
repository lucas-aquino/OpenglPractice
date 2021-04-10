#include "PointLight.h"

PointLight::PointLight()
:   linear(0.027f),
    constant(1.0f),
    quadratic(0.0028f)
{
    position = glm::vec3(0.0f, 1.0f, 0.0f);

    ambient = glm::vec3(0.1f);
    diffuse = glm::vec3(0.5f);
    specular = glm::vec3(0.5f);
}

void PointLight::draw(Shader& shader)
{
    shader.setUniform("pointLight.position", position);
    shader.setUniform("pointLight.constant", constant);
    shader.setUniform("pointLight.linear", linear);
    shader.setUniform("pointLight.quadratic", quadratic);
    shader.setUniform("pointLight.ambient", ambient);
    shader.setUniform("pointLight.specular", specular);
}

void PointLight::setConstant(float constant)
{
    this->constant = constant;
}

void PointLight::setLinear(float linear)
{
    this->linear = linear;
}


void PointLight::setQuadratic(float quadratic)
{
    this->quadratic = quadratic;
}


void PointLight::setPosition(glm::vec3 position) 
{
    this->position = position;
}

void PointLight::setPosition(float x, float y, float z) 
{
    this->position = glm::vec3(x, y, z);
}

     
void PointLight::setAmbient(glm::vec3 ambient) 
{
    this->ambient = ambient;
}

void PointLight::setAmbient(float r, float g, float b)
{
    this->ambient = glm::vec3(r, g, b);
}
     
void PointLight::setDiffuse(glm::vec3 diffuse) 
{
    this->diffuse = diffuse;
}

void PointLight::setDiffuse(float r, float g, float b) 
{
    this->diffuse = glm::vec3(r, g, b);
}
     
void PointLight::setSpecular(glm::vec3 specular) 
{
    this->specular = specular;
}

void PointLight::setSpecular(float r, float g, float b) 
{
    this->specular = glm::vec3(r, g, b);
}