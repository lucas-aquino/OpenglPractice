#version 330 core

struct Material 
{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light 
{
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;
uniform Light light;

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
    //FragColor = mix(texture(texture1, texCoord), texture(texture2, texCoord), abs(sin(time * 2)));
    
    //Ambient 
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCoord));

    //Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDirection = normalize(light.position - FragPosition);

    float diff = max(dot(norm, lightDirection), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, texCoord));
    
    //Specular 
    vec3 viewDirection = normalize(viewPosition - FragPosition);
    vec3 reflectDirection = reflect(-lightDirection, norm);

    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * vec3(texture(material.specular, texCoord)));
    
    
    
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}
