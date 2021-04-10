#version 330 core


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
    FragColor = vec4(vec3(gl_FragCoord.z), 1.0);
}