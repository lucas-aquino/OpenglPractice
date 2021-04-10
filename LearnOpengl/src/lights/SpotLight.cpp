#include "SpotLight.h"

SpotLight::SpotLight()
:   direction(glm::vec3(0.0f, -1.0f, 0.0f)),
    cutOff(glm::cos(glm::radians(12.5f))),
    outerCutOff(glm::cos(glm::radians(17.5f))),
    constant(1.0f),
    linear(0.09f),
    quadratic(0.032f)
{
    position = glm::vec3(0.0f, 1.0f, 0.0f);

    ambient = glm::vec3(0.1f);
    diffuse = glm::vec3(1.0f);
    specular = glm::vec3(1.0f);
}

void SpotLight::draw(Shader& shader) 
{
    shader.setUniform("spotlight.position", position);
    shader.setUniform("spotlight.direction", direction);
    shader.setUniform("spotlight.cutOff", cutOff);
    shader.setUniform("spotlight.outerCutOff", outerCutOff);
    shader.setUniform("spotlight.ambient", ambient);
    shader.setUniform("spotlight.diffuse", diffuse);
    shader.setUniform("spotlight.specular", specular);
    shader.setUniform("spotlight.constant", constant);
    shader.setUniform("spotlight.linear", linear);
    shader.setUniform("spotlight.quadratic", quadratic);
}

void SpotLight::setCutOff(float cutOff)
{
    this->cutOff = glm::cos(glm::radians(cutOff));
}

void SpotLight::setOuterCutoff(float outerCutOff)
{   
    this->outerCutOff = glm::cos(glm::radians(outerCutOff));
}

void SpotLight::setConstant(float constant)
{
    this->constant = constant;
}

void SpotLight::setLinear(float linear)
{
    this->linear = linear;
}

void SpotLight::setQuadratic(float quadratic)
{
    this->quadratic = quadratic;
}

void SpotLight::setPosition(glm::vec3 position) 
{
    this->position = position;
}

void SpotLight::setPosition(float x, float y, float z) 
{
    this->position = glm::vec3(x, y, z);
}

void SpotLight::setAmbient(glm::vec3 ambient) 
{
    this->ambient = ambient;
}

void SpotLight::setAmbient(float r, float g, float b) 
{
    this->ambient = glm::vec3(r, g, b);
}

void SpotLight::setDiffuse(glm::vec3 diffuse) 
{
    this->diffuse = diffuse;
}

void SpotLight::setDiffuse(float r, float g, float b) 
{
    this->diffuse = glm::vec3(r, g, b);
}

void SpotLight::setSpecular(glm::vec3 specular) 
{
    this->specular = specular;
}

void SpotLight::setSpecular(float r, float g, float b) 
{
    this->specular = glm::vec3(r, g, b);
}