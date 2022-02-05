#version 330 core

out vec4 FragColor;
in vec3 dynamicColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;
// uniform vec4 dynamicColor;
uniform float pylly;
void main()
{
    FragColor = texture(ourTexture, TexCoord) * pylly * vec4(dynamicColor, 1.0f);
}