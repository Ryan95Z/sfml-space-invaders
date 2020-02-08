#version 330 core

out vec4 FragColour;

in vec2 texCoord;

uniform sampler2D trv;

void main()
{
	FragColour = texture(trv, texCoord);
	//FragColour = vec4(1.0, 0.0, 1.0, 1.0);
}