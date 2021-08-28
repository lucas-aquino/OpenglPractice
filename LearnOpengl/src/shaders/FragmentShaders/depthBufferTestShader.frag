#version 330 core


out vec4 FragColor;

in vec3 ourColor;
in vec3 ourPosition;

in vec2 texCoord;

in vec3 FragPosition;
in vec3 Normal;

uniform float time;

uniform vec3 viewPosition;

float near = 0.1;
float far = 100.0;

float linearizeDepth(float depth);

void main()
{
    float depth = linearizeDepth(gl_FragCoord.z) /far;
    FragColor = vec4(vec3(depth), 1.0);
}

float linearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0;
    return (2.0 * near * far) / (far + near - z *(far - near));
}