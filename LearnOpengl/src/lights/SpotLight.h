#pragma once

#include "Light.h"

class SpotLight : public Light
{
    glm::vec3 direction;
    float cutOff;
    float outerCutOff;

    float constant;    
    float linear;
    float quadratic;

public:
    
    SpotLight();
    
    void setCutOff(float cutOff);
    void setOuterCutoff(float outerCutOff);
    void setConstant(float constant);
    void setLinear(float linear);
    void setQuadratic(float quadratic);

    float getCutOff()       const { return cutOff;      }
    float getOuterCutOff()  const { return outerCutOff; }
    float getConstant()     const { return constant;    }
    float getLinear()       const { return linear;      }
    float getQuadratic()    const { return quadratic;   }

    virtual void draw(Shader& shader) override;

    virtual void setPosition(glm::vec3 position) override;
    virtual void setPosition(float x, float y, float z) override;

    virtual void setAmbient(glm::vec3 ambient) override;
    virtual void setAmbient(float r, float g, float b) override;

    virtual void setDiffuse(glm::vec3 diffuse) override;
    virtual void setDiffuse(float r, float g, float b) override;

    virtual void setSpecular(glm::vec3 specular) override;
    virtual void setSpecular(float r, float g, float b) override;
};

