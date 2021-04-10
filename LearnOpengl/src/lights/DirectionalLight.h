#pragma once

#include "Light.h"

class DirectionalLight : public Light
{

    glm::vec3 direction;

public:

    DirectionalLight();

    glm::vec3 getDirection() const { return direction; }

    void setDirection(glm::vec3 direction);
    void setDirection(float x, float y, float z);

    virtual void draw(Shader &shader) override;

    virtual void setPosition(glm::vec3 position) override;
    virtual void setPosition(float x, float y, float z) override;

    virtual void setAmbient(glm::vec3 ambient) override;
    virtual void setAmbient(float r, float g, float b) override;

    virtual void setDiffuse(glm::vec3 diffuse) override;
    virtual void setDiffuse(float r, float g, float b) override;

    virtual void setSpecular(glm::vec3 specular) override;
    virtual void setSpecular(float r, float g, float b) override;
};

