#version 330 core

in vec2 textCoords;

out vec4 fragmentColor;

uniform sampler2D uTexture;

void main()
{
    fragmentColor = texture(uTexture, textCoords);
}
