#version 330 core
out vec4 fragColor;

in vec2 textureCoordinates;

uniform sampler2D ourTexture;

void main()
{    
    fragColor = texture(ourTexture, textureCoordinates);
}