#include "DirectionalLight.h"

DirectionalLight::DirectionalLight()
:   direction(glm::vec3(5.0f, 0.0f, 10.0f))
{
    ambient = glm::vec3(0.1f);
    diffuse = glm::vec3(0.5f);
    specular = glm::vec3(0.5f);
}

void DirectionalLight::draw(Shader& shader) 
{
    shader.setUniform("directionalLight.direction", direction);
    shader.setUniform("directionalLight.ambient", ambient);
    shader.setUniform("directionalLight.diffuse", diffuse);
    shader.setUniform("directionalLight.specular", specular);
}

void DirectionalLight::setDirection(const glm::vec3& direction)
{
    this->direction = direction;
}

void DirectionalLight::setDirection(float x, float y, float z)
{
    this->direction = glm::vec3(x, y, z);
}

void DirectionalLight::setPosition(const glm::vec3& position) 
{
    this->position = position;
}

void DirectionalLight::setPosition(float x, float y, float z) 
{
    this->position = glm::vec3(x, y, z);
}

void DirectionalLight::setAmbient(const glm::vec3& ambient) 
{
    this->ambient = ambient;
}

void DirectionalLight::setAmbient(float r, float g, float b) 
{
    this->ambient = glm::vec3(r, g, b);
}

void DirectionalLight::setDiffuse(const glm::vec3& diffuse) 
{
    this->diffuse = diffuse;
}

void DirectionalLight::setDiffuse(float r, float g, float b) 
{
    this->diffuse = glm::vec3(r, g, b);
}

void DirectionalLight::setSpecular(const glm::vec3& specular) 
{
    this->specular = specular;
}

void DirectionalLight::setSpecular(float r, float g, float b) 
{
    this->specular = glm::vec3(r, g, b);
}