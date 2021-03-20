#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTextureCoordinate;

out vec3 ourPosition;
out vec2 texCoord;
out vec3 FragPosition;
out vec3 Normal;

uniform mat4 transform;
uniform float time;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    ourPosition = aPos;
    texCoord = aTextureCoordinate;
    FragPosition = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model)))  * aNormal; 
    gl_Position = projection * view * vec4(FragPosition, 1.0);
}
