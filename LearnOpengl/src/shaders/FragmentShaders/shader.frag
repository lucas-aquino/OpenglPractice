#version 330 core

out vec4 FragColor;

in vec3 ourColor;
in vec3 ourPosition;

in vec2 texCoord;

uniform float time;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform bool wireframe;
uniform bool fill;
uniform bool vertices;

void main()
{
    FragColor = mix(texture(texture1, texCoord), texture(texture2, texCoord), abs(sin(time * 2)));
}
