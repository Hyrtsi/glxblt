#version 330 core

out vec4 FragColor;
in vec3 dynamicColor;

void main()
{
    FragColor = vec4(dynamicColor, 1.0f);
}