#version 330 core

layout (location = 0) in vec4 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 dynamicColor;
out vec2 TexCoord;

uniform mat4 perspective;
uniform mat4 camera;

void main()
{
    gl_Position = perspective * aPos;
    dynamicColor = aColor;
    TexCoord = aTexCoord;
}