#version 330 core

in vec2 textCoords;

out vec4 fragmentColor;

uniform sampler2D texture_diffuse1;

void main()
{
    fragmentColor = texture(texture_diffuse1, textCoords);
}
