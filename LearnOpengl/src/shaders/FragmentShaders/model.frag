#version 330 core

struct Material 
{
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
    float shininess;
};
uniform Material material;

//Directional Light Struct
struct DirectionalLight
{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform DirectionalLight directionalLight;

//Point Light Struct
struct PointLight
{ 
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
#define NR_POINT_LIGHT 4
uniform PointLight pointLight[NR_POINT_LIGHT];

//Spot Light Struct
struct SpotLight
{
    vec3 direction;
    vec3 position;
    float cutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform SpotLight spotlight;

//Function Prototype

vec3 calculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDirection);
vec3 calculatePointLight(PointLight light, vec3 normal, vec3 fragmentPosition, vec3 viewDirection);
vec3 calculateSpotLight(SpotLight light, vec3 normal, vec3 fragmentPosition, vec3 viewDirection);

//------------------

out vec4 FragColor;

in vec3 ourColor;
in vec3 ourPosition;

in vec2 texCoord;

in vec3 FragPosition;
in vec3 Normal;

uniform float time;

uniform vec3 viewPosition;

void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDirection = normalize(viewPosition - FragPosition);

    vec3 result = calculateDirectionalLight(directionalLight, norm, viewDirection);

    for(int i = 0; i < NR_POINT_LIGHT; i++)
        result += calculatePointLight(pointLight[i], norm, FragPosition, viewDirection);
    
    result += calculateSpotLight(spotlight, norm, FragPosition, viewDirection);

    FragColor = vec4(result, 1.0);
}


vec3 calculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDirection)
{
    //Light Direction
    vec3 lightDirection = normalize(-light.direction);

    //Diffuse
    float diff = max(dot(normal, lightDirection), 0.0);

    //Specular 
    vec3 reflectDirection = reflect(-lightDirection, normal);
    float spec = pow(max(dot(viewDirection, reflectDirection),0.0), material.shininess);

    vec3 ambient    = light.ambient  * vec3(texture(material.texture_diffuse1, texCoord));
    vec3 diffuse    = light.diffuse  * diff * vec3(texture(material.texture_diffuse1, texCoord));
    vec3 specular   = light.specular * spec * vec3(texture(material.texture_specular1, texCoord));

    return (ambient + diffuse + specular);
}

vec3 calculatePointLight(PointLight light, vec3 normal, vec3 fragmentPosition, vec3 viewDirection)
{
    //Light Direction
    vec3 lightDirection = normalize(light.position - fragmentPosition);

    //Diffuse
    float diff = max(dot(normal, lightDirection), 0.0);

    //Specular 
    vec3 reflectDirection = reflect(-lightDirection, normal);
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);

    //Attenuation
    float distanceA = length(light.position - fragmentPosition);
    float attenuation = 1.0 / (light.constant + light.linear * distanceA + light.quadratic * (distanceA * distanceA));

    vec3 ambient  = light.ambient  * vec3(texture(material.texture_diffuse1, texCoord));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.texture_diffuse1, texCoord));
    vec3 specular = light.specular * spec * vec3(texture(material.texture_specular1, texCoord));

    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;

    return(ambient + diffuse + specular);
}


vec3 calculateSpotLight(SpotLight light, vec3 normal, vec3 fragmentPosition, vec3 viewDirection)
{
    //Light Direction
    vec3 lightDirection = normalize(light.position - fragmentPosition);

    float theta = dot(lightDirection, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = smoothstep(0.0, 1.0, (theta - light.outerCutOff) / epsilon);

    //Diffuse
    float diff = max(dot(normal, lightDirection), 0.0);

    //Specular
    vec3 reflectDirection = reflect(-lightDirection, normal);
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
    
    //Attenuation
    float distanceA = length(light.position - fragmentPosition);
    float attenuation = 1.0 / (light.constant + light.linear * distanceA + light.quadratic * (distanceA * distanceA));

    vec3 ambient  = light.ambient  * vec3(texture(material.texture_diffuse1, texCoord));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.texture_diffuse1, texCoord));
    vec3 specular = light.specular * spec * vec3(texture(material.texture_specular1, texCoord));

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    diffuse *= intensity;
    specular *= intensity;

    return (ambient + diffuse + specular);
}
