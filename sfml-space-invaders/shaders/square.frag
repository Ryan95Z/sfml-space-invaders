#version 330 core

out vec4 FragColour;

uniform vec3 spriteColour;

void main()
{
	FragColour = vec4(spriteColour.xyz, 1.0);
}