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
    vec3 direction;
    float cutOff;
    float outerCutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
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
    
    vec3 lightDirection = normalize(light.position - FragPosition);

    float theta = dot(lightDirection, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    //float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    float intensity = smoothstep(0.0, 1.0, (theta - light.outerCutOff) / epsilon);
    
    //Ambient 
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCoord));

    //Diffuse
    vec3 norm = normalize(Normal);
    //vec3 lightDirection = normalize(-light.direction);


    float diff = max(dot(norm, lightDirection), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, texCoord));
    
    //Specular 
    vec3 viewDirection = normalize(viewPosition - FragPosition);
    vec3 reflectDirection = reflect(-lightDirection, norm);

    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * vec3(texture(material.specular, texCoord)));
    
    float distanceA = length(light.position - FragPosition);
    float attenuation = 1.0 / (light.constant + light.linear * distanceA + light.quadratic * (distanceA * distanceA));
    
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    
    diffuse *= intensity;
    specular *= intensity;

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);

}
