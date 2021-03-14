#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTextureCoordinate;

out vec3 ourColor;
out vec3 ourPosition;
out vec2 texCoord;

uniform mat4 transform;
uniform float time;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    //gl_Position = vec4(aPos.x + sin(time * 1.5) * 0.4, aPos.y + cos(time * 1.5) * 0.4,aPos.z, 1.0); 
    //gl_Position = transform * vec4(aPos, 1.0f);
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    ourColor = aColor;
    ourPosition = aPos;
    texCoord = aTextureCoordinate;
}
