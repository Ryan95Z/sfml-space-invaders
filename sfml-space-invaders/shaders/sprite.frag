#version 330 core

out vec4 FragColour;

in vec2 texCoord;

uniform sampler2D tex;

void main()
{
	FragColour = texture(tex, texCoord);
}